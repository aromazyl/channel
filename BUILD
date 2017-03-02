cc_library(
    name = "memory"
    srcs = ["memory/memory_pool.cc",
            "memory/blob.cc"
            ],
    )
cc_library(
    name = "io",
    srcs = ["./memory/fast_io.cc"],
    )

cc_library(
    name = "kvstore",
    srcs = ["./kvstore/kvstore_actor.cc"],
    hdrs = ["./kvstore/kvstore_actor.h",
            "./kvstore/kvstore_base.h",
            "./kvstore/sparse_hash_kvstore.h"],
    deps = ["//lib:memory",
            "//lib:io"]
    )

cc_library(
    name = "net",
    srcs = ["./net/communicator.cc",
            "./net/network.cc",
            "./net/zmq_network.cc"],
    hdrs = ["./net/communicator.h",
            "./net/network.h",
            "./net/zmq_network.h"],
    deps = ["//lib:memory",
            "//lib:io"]
    )

cc_test(
    name = "test_all",
    srcs = ["test/test.cc"],
    deps = ["//lib:memory",
            "//lib:io",
            "@gtest//:main",
            ],
    )

