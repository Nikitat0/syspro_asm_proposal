{ pkgs ? import <nixpkgs> { }
, pkgsCrossArm64 ? import <nixpkgs> { crossSystem.config = "aarch64-linux-gnu"; }
}:

pkgs.mkShell {
  packages = with pkgs; [
    clang-tools
    gcc
    gdb
    nasm
    qemu
    pkgsCrossArm64.buildPackages.gcc
  ];
}
