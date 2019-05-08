package(default_visibility = ['//visitbility:public'])

filegroup(
  name = 'gcc',
  srcs = [
    'bin/x86_64-unknown-linux-gnu-gcc'
  ],
)

filegroup(
  name = 'compiler_components',
  srcs = [
    ':gcc',
  ],
)

cc_toolchain_suite(
    name = "toolchain",
    # target_cpu | compiler
    toolchains = {
        "@freedesktop-sdk-toolchain//:compiler_components",
    },
    visibility = ["//visibility:public"],
)
