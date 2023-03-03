#ifndef STRATUM_HAL_LIB_COMMON_YUSUR_IPSEC_SERVICE_H_
#define STRATUM_HAL_LIB_COMMON_YUSUR_IPSEC_SERVICE_H_

#include <csignal>
#include <string>

#include "grpcpp/grpcpp.h"
#include "yusur/proto/ipsec.grpc.pb.h"

namespace yusur {
class IPSecService final : public opi_api::security::v1::IPsec::Service {
 public:
  IPSecService();
  ~IPSecService() override{};
  ::grpc::Status IPsecVersion(
      ::grpc::ServerContext* context,
      const ::opi_api::security::v1::IPsecVersionReq* request,
      ::opi_api::security::v1::IPsecVersionResp* response);
};
}  // namespace yusur
#endif