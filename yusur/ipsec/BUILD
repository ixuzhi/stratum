load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

load("//bazel:rules.bzl",
    "STRATUM_INTERNAL",
    "stratum_cc_binary",
    "stratum_cc_library"
    )


licenses(["notice"])  # Apache v2

package(
    default_visibility = ["//visibility:public"],
)

stratum_cc_library(
    name = "ipsec_service",
    srcs = [
        "ipsec_service.cc",
    ],
    hdrs = [
        "ipsec_service.h"
    ],
    deps = [
        "//yusur/proto:ipsec_cc_proto",
        "//yusur/proto:ipsec_cc_grpc",
        "@com_github_google_glog//:glog",
        "@com_google_protobuf//:protobuf",
        "@com_github_grpc_grpc//:grpc++"
    ],
)

cc_binary(
    name = "ipsec_cli",
    srcs = [
        "client.cc",
    ],
    deps=[
        "//yusur/proto:ipsec_cc_grpc",
        "//yusur/proto:ipsec_cc_proto",
        "@com_github_google_glog//:glog",
        "@com_google_protobuf//:protobuf",
        "@com_github_grpc_grpc//:grpc++"
    ],
)
