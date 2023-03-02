# Copyright 2018 Google LLC
# Copyright 2018-present Open Networking Foundation
# SPDX-License-Identifier: Apache-2.0


load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

licenses(["notice"])  # Apache v2

package(
    default_visibility = ["//visibility:public"],
)

proto_library(
    name = "ipsec_proto",
    srcs = ["ipsec.proto"],
)

cc_proto_library(
    name = "cc_ipsec_proto",
    deps = [":ipsec_proto"],
)

cc_grpc_library(
    name = "ipsec_cc_grpc",
    srcs = [":ipsec_proto"],
    grpc_only = True,
    deps = [":cc_ipsec_proto"],
)