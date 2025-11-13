{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.apitrace
    pkgs.cmake
    pkgs.gcc
    pkgs.glbinding # For C++ bindings
    pkgs.glew
    pkgs.glfw2
    pkgs.libGLU
    pkgs.mesa
  ];
}