{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.cmake
    pkgs.libGLU
    pkgs.glew
    pkgs.glbinding # For C++ bindings
    pkgs.glfw2
    pkgs.mesa
    pkgs.apitrace
  ];
}