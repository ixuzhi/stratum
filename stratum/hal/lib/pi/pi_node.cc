/* Copyright 2018-present Barefoot Networks, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stratum/hal/lib/pi/pi_node.h"

#include "PI/frontends/proto/device_mgr.h"
#include "stratum/glue/logging.h"
#include "stratum/glue/status/status_macros.h"
#include "stratum/hal/lib/common/writer_interface.h"
#include "stratum/lib/constants.h"
#include "stratum/lib/macros.h"
#include "stratum/glue/integral_types.h"
#include "absl/memory/memory.h"
#include "absl/synchronization/mutex.h"
#include "absl/time/clock.h"
#include "google/rpc/code.pb.h"

using ::pi::fe::proto::DeviceMgr;
using Code = ::google::rpc::Code;

namespace stratum {
namespace hal {
namespace pi {

namespace {

// Utility functions to convert between grpc::Status and Stratum
// Util::Status. This is a bit silly because Util::Status will be converted back
// to grpc::Status in the P4Service.

::util::Status toUtilStatus(const DeviceMgr::Status& from,
                            std::vector<::util::Status>* results,
                            int updates_size = 0) {
  if (from.code() == Code::OK) {
    if (results->size() != 0)
      return MAKE_ERROR(ERR_INTERNAL) << "Expected empty results vector.";
    results->resize(updates_size);
    return ::util::Status();
  }
  ::util::Status status(::util::Status::canonical_space(), from.code(), "");
  for (const auto& detail : from.details()) {
    ::p4::v1::Error error;
    detail.UnpackTo(&error);
    results->emplace_back(::util::Status::canonical_space(),
                          error.code(),
                          error.message());
  }
  return status;
}

::util::Status toUtilStatus(const DeviceMgr::Status& from) {
  if (from.code() == Code::OK) {
    return ::util::Status();
  }
  return ::util::Status(::util::Status::canonical_space(), from.code(), "");
}

}  // namespace

void PacketInCb(uint64_t node_id, p4::v1::PacketIn* packet, void* cookie) {
  (void)node_id;
  auto* pi_node = static_cast<PINode*>(cookie);
  pi_node->SendPacketIn(packet);
}

PINode::PINode(::pi::fe::proto::DeviceMgr* device_mgr,
               int unit,
               uint64 node_id)
    : device_mgr_(device_mgr),
      unit_(unit),
      node_id_(node_id) { }

PINode::~PINode() = default;

::util::Status PINode::PushChassisConfig(const ChassisConfig& config,
                                         uint64 node_id) {
  (void)config;
  (void)node_id;
  return ::util::OkStatus();
}

::util::Status PINode::VerifyChassisConfig(const ChassisConfig& config,
                                           uint64 node_id) {
  (void)config;
  (void)node_id;
  return ::util::OkStatus();
}

::util::Status PINode::PushForwardingPipelineConfig(
    const ::p4::v1::ForwardingPipelineConfig& config) {
  auto status = device_mgr_->pipeline_config_set(
      ::p4::v1::SetForwardingPipelineConfigRequest_Action_VERIFY_AND_COMMIT,
      config);
  // This is required by DeviceMgr in case the device is re-assigned internally
  device_mgr_->packet_in_register_cb(PacketInCb, static_cast<void*>(this));
  return toUtilStatus(status);
}

::util::Status PINode::VerifyForwardingPipelineConfig(
    const ::p4::v1::ForwardingPipelineConfig& config) {
  auto status = device_mgr_->pipeline_config_set(
      ::p4::v1::SetForwardingPipelineConfigRequest_Action_VERIFY,
      config);
  return toUtilStatus(status);
}

::util::Status PINode::Shutdown() {
  return ::util::OkStatus();
}

::util::Status PINode::Freeze() {
  return ::util::OkStatus();
}

::util::Status PINode::Unfreeze() {
  return ::util::OkStatus();
}

::util::Status PINode::WriteForwardingEntries(
    const ::p4::v1::WriteRequest& req, std::vector<::util::Status>* results) {
  if (!req.updates_size()) return ::util::OkStatus();  // nothing to do.
  CHECK_RETURN_IF_FALSE(results != nullptr)
      << "Need to provide non-null results pointer for non-empty updates.";

  auto status = device_mgr_->write(req);
  return toUtilStatus(status, results, req.updates_size());
}

::util::Status PINode::ReadForwardingEntries(
    const ::p4::v1::ReadRequest& req,
    WriterInterface<::p4::v1::ReadResponse>* writer,
    std::vector<::util::Status>* details) {
  CHECK_RETURN_IF_FALSE(writer) << "Channel writer must be non-null.";
  CHECK_RETURN_IF_FALSE(details) << "Details pointer must be non-null.";

  ::p4::v1::ReadResponse response;
  auto status = device_mgr_->read(req, &response);
  RETURN_IF_ERROR(toUtilStatus(status, details));
  if (!writer->Write(response))
    return MAKE_ERROR(ERR_INTERNAL) << "Write to stream channel failed.";
  return ::util::OkStatus();
}

::util::Status PINode::RegisterPacketReceiveWriter(
    const std::shared_ptr<WriterInterface<::p4::v1::PacketIn>>& writer) {
  absl::MutexLock l(&rx_writer_lock_);
  rx_writer_ = writer;
  // TODO(antonin): this may not be required here as we do it in
  // PushForwardingPipelineConfig
  device_mgr_->packet_in_register_cb(PacketInCb, static_cast<void*>(this));
  return ::util::OkStatus();
}

::util::Status PINode::UnregisterPacketReceiveWriter() {
  absl::MutexLock l(&rx_writer_lock_);
  rx_writer_ = nullptr;
  return ::util::OkStatus();
}

::util::Status PINode::TransmitPacket(const ::p4::v1::PacketOut& packet) {
  return toUtilStatus(device_mgr_->packet_out_send(packet));
}

int64 PINode::GetNodeId() const {
  return node_id_;
}

std::unique_ptr<PINode> PINode::CreateInstance(
    ::pi::fe::proto::DeviceMgr* device_mgr,
    int unit,
    uint64 node_id) {
  return absl::WrapUnique(new PINode(device_mgr, unit, node_id));
}

void PINode::SendPacketIn(::p4::v1::PacketIn* packet) {
  // acquire the lock during the Write: SendPacketIn may be called from
  // different threads and Write is not thread-safe.
  absl::MutexLock l(&rx_writer_lock_);
  if (rx_writer_ == nullptr) return;
  rx_writer_->Write(*packet);
}

}  // namespace pi
}  // namespace hal
}  // namespace stratum