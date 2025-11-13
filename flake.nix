{
  description = "My C++ project built with Nix + NVIDIA";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config = {
            allowUnfree = true;               # needed for NVIDIA drivers
            cudaSupport = true;               # enables CUDA toolkit
          };
        };

        # ------------------------------------------------------------------
        # 1. Native build inputs (CMake, gcc/clang, etc.)
        # 2. Runtime libraries (OpenGL, CUDA, etc.)
        # ------------------------------------------------------------------
        nativeBuildInputs = with pkgs; [
          cmake
          ninja
          gcc                       # or clang, maybe later
        ];

        buildInputs = with pkgs; [
          # Core graphics stack
          libGL
          libGLU
          glfw

          # NVIDIA driver runtime (matches what you already have on the host)
          # `linuxPackages.nvidia_x11` works for the *current* kernel
          linuxPackages.nvidia_x11

          # If CUDA libraries are needed in build:
          # cudaPackages.cudatoolkit
          # cudaPackages.cuda_nvcc
        ];

      in {
        # `nix develop` → interactive shell with everything on PATH
        devShells.default = pkgs.mkShell {
          inherit buildInputs nativeBuildInputs;
          # Make sure the driver libraries are found at runtime
          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath buildInputs;
        };

        # `nix build` → reproducible package
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "solitaire_gl";
          version = "0.1.0";

          src = ./.;

          inherit nativeBuildInputs buildInputs;

          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=Release"
          ];

          # For driver libs at *runtime* inside the Nix store:
          postFixup = ''
            patchelf --set-rpath ${
              pkgs.lib.makeLibraryPath buildInputs
            } $out/bin/*
          '';
        };
      });
}