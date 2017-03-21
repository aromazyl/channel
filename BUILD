package(default_visibility = ["//visibility:public"])

cc_library(
    name = "zmq",
    srcs = glob(["third_party/zmq/include/*.h"]),
    copts = ["-L./third_party/zmq/lib/", "-lzmq"],
    )

cc_library(
    name = "sparse_hash",
    srcs = glob(["third_party/sparsehash/include/google/sparsehash/*.h",
                 "third_party/sparsehash/include/sparsehash/internal/*.h"]),
    includes = ["third_party/sparsehash/include/google/*",
                "third_party/sparsehash/include/sparsehash/sparse_hash_map"]
    )

cc_library(
    name = "headers",
    srcs = glob(["*.h",
                 "net/*.h",
                 "base/*.hpp",
                 "base/thread_pool/*.hpp",
                 "net/*.h",
                 "io/*.h",
                 "kvstore/*.h",
                 "conf/*.h"]),
    )
cc_library(
    name = "memory",
    hdrs = ["memory/blob.h",
            "memory/memory_pool.h",
            "base/string_printf.hpp",],
    srcs = ["memory/memory_pool.cc",
            "memory/blob.cc",
            ],
    deps = [":headers"],
    )

cc_library(
    name = "io",
    # hdrs = ["io/fast_io.h"],
    srcs = ["io/fast_io.cc"],
    deps = [":headers"],
    )

cc_library(
    name = "kvstore",
    # hdrs = ["kvstore/kvstore_actor.h",
    #         "kvstore/kvstore_base.h",
    #         "kvstore/sparse_hash_kvstore.h"],
    srcs = ["kvstore/kvstore_actor.cc"],
    deps = [":memory",
            ":io",
            ":headers",
            ":sparse_hash"],
    )

cc_library(
    name = "net",
    srcs = ["net/communicator.cc",
            "net/network.cc",
            "net/zmq_network.cc"],
    hdrs = ["net/communicator.h",
            "net/network.h",
            "net/zmq_network.h",
            "conf/configure.h",
            "message.h",
            ],
    # includes = ["third_party/sparsehash/include/"],
    copts = ["-Ithird_party/sparsehash/include/"],
    deps = [":memory",
            ":io",
            ":zmq",
            ":headers",
            ":sparse_hash"],
    )

cc_test(
    name = "test_all",
    srcs = ["test/test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [":memory",
            ":io",
            "@gtest//:main",
            ":headers",
            ],
    )

