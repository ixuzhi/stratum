load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

# load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_compile")

licenses(["notice"])  # Apache v2

package(
    default_visibility = ["//visibility:public"],
)

proto_library(
    name = "ipsec_proto",
    srcs = ["ipsec.proto"],
)

cc_proto_library(
    name = "ipsec_cc_proto",
    deps = [":ipsec_proto"],
)

cc_grpc_library(
    name = "ipsec_cc_grpc",
    srcs = [":ipsec_proto"],
    grpc_only = True,
    deps = [":ipsec_cc_proto"],
)
