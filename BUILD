cc_library(
    name = "base",
    hdrs = ["base/string_printf.hpp",
            "base/thread_pool/simple_threadpool.hpp",
            "base/thread_pool/thread_safe_queue.hpp"],
    )
cc_library(
    name = "memory",
    hdrs = ["memory/blob.h",
            "memory/memory_pool.h",
            "base/string_printf.hpp",],
    srcs = ["memory/memory_pool.cc",
            "memory/blob.cc",
            ],
    )

cc_library(
    name = "io",
    hdrs = ["io/fast_io.h"],
    srcs = ["io/fast_io.cc"],
    )

cc_library(
    name = "kvstore",
    hdrs = ["kvstore/kvstore_actor.h",
            "kvstore/kvstore_base.h",
            "kvstore/sparse_hash_kvstore.h"],
    srcs = ["kvstore/kvstore_actor.cc"],
    deps = ["//lib:memory",
            "//lib:base",
            "//lib:io"],
    )

cc_library(
    name = "net",
    srcs = ["net/communicator.cc",
            "net/network.cc",
            "net/zmq_network.cc"],
    hdrs = ["net/communicator.h",
            "net/network.h",
            "net/zmq_network.h"],
    deps = ["//lib:memory",
            "//lib:io"]
    )

cc_test(
    name = "test_all",
    srcs = ["test/test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = ["//lib:memory",
            "//lib:io",
            "@gtest//:main",
            ],
    )

