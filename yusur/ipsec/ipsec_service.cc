#include "yusur/ipsec/ipsec_service.h"

#include <csignal>
#include <string>

#include "iostream"

namespace yusur {

IPSecService::IPSecService() { std::cout << "Yusur IPsecService init ... \n"; }

::grpc::Status IPSecService::IPsecVersion(
    ::grpc::ServerContext* context,
    const ::opi_api::security::v1::IPsecVersionReq* request,
    ::opi_api::security::v1::IPsecVersionResp* response) {
  std::cout << "Remote call IPsecVersion function" << std::endl;
  std::cout << "IPsecVersion function for test ..." << std::endl;
  response->set_version("yusur ipsec v1.0");
  return ::grpc::Status::OK;
}

}  // namespace yusur
