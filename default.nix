let
  pkgs = import <nixpkgs> { };
  inherit (pkgs) lib;
  clangTools = (pkgs.llvmPackages_19.clang-tools.override { enableLibcxx = true; });
in
pkgs.llvmPackages_19.stdenv.mkDerivation {
  name = "something";
  src = ./.;

  nativeBuildInputs = [
    pkgs.cmake
    pkgs.ninja
    clangTools
  ];
}
