{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
    packages = with pkgs; [
        clang-tools
        gcc
        gdb
        nasm
    ];
}
