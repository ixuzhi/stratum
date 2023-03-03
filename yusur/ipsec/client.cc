#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>

#include <array>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

// #include "yusur/ipsec.grpc.pb.h"
#include "yusur/proto/ipsec.grpc.pb.h"
#include "yusur/proto/ipsec.pb.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::Status;

int main(int argc, char** argv) {
  auto stubs = opi_api::security::v1::IPsec::NewStub(grpc::CreateChannel(
      "localhost:9339", grpc::InsecureChannelCredentials()));

  ::opi_api::security::v1::IPsecVersionReq request;

  ::opi_api::security::v1::IPsecVersionResp resp;
  ClientContext context;

  Status status = stubs->IPsecVersion(&context, request, &resp);
  std::cout << "status.ok()=" << status.ok() << std::endl;
  if (!status.ok()) {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return 1;
  }
  std::cout << "response data: " << resp.DebugString() << std::endl;
  return 0;
}