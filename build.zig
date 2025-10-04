const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const mod = b.addModule("ceigen", .{
        .target = target,
        .optimize = optimize,
        .link_libcpp = true,
    });

    const lib = b.addLibrary(.{
        .name = "ceigen",
        .linkage = .static,
        .root_module = mod,
    });

    lib.addIncludePath(b.path("eigen-master"));
    lib.addIncludePath(b.path("include"));
    lib.addCSourceFiles(.{
        .root = b.path("src"),
        .files = &.{
            "mat4.cpp",
            "sparse.cpp",
        },
    });
    lib.installHeadersDirectory(
        b.path("include"),
        "ceigen",
        .{},
    );

    b.installArtifact(lib);
}
