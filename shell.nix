{ pkgs ? import <nixpkgs> {} }:

let
  # If you want the same pkgs config as the flake (unfree & CUDA), you would
  # need to import the same pinned channel or use flakes. Here we keep default.
in pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    cmake
    ninja
    gcc
  ];
  shellHook = ''
      echo "Launching VS Code inside Nix shell..."
      exec code "$PWD"
    '';

  buildInputs = with pkgs; [
    libGL
    libGLU
    glfw
    stdenv.cc.cc.lib
    # linuxPackages.nvidia_x11  # kernel-specific; include only if you truly need it
  ];

  # Make sure driver libraries are found at runtime when running inside the shell
  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath buildInputs;
}
