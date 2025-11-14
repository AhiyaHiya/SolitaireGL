{
  description = "Solitaire C++ project built with Nix + NVIDIA";
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
            allowUnfree = true; # needed for NVIDIA drivers
            cudaSupport = true; # enables CUDA toolkit
          };
        };

        # ------------------------------------------------------------------
        # 1. Native build inputs (CMake, gcc/clang, etc.)
        # 2. Runtime libraries (OpenGL, CUDA, etc.)
        # ------------------------------------------------------------------
        nativeBuildInputs = with pkgs; [
          cmake
          ninja
          gcc # or clang
          gdb
          lldb
        ];

        buildInputs = with pkgs; [
          # Core graphics stack
          libGL
          libGLU
          glfw
          # Ensure C++ runtime (libstdc++) is available at runtime
          gcc
          stdenv.cc.cc.lib
          # NVIDIA driver runtime
          linuxPackages.nvidia_x11
          # Add CUDA runtime if needed:
          # cudaPackages.cudatoolkit
        ];

        # Common derivation settings
        baseDerivation = {
          pname = "solitaire";
          version = "0.1.0";
          src = ./.;
          inherit nativeBuildInputs buildInputs;

          # --- DEBUG SYMBOLS ---
          separateDebugInfo = true;  # Creates $debug output with .debug files
          dontStrip = true;          # Keep symbols in the main binary

          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=Debug"  # Critical for source-level debugging
            "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
          ];

          # Fix rpath so binary finds libs at runtime (outside nix develop)
          postFixup = ''
            for bin in $out/bin/*; do
              if [ -f "$bin" ] && [ -x "$bin" ]; then
                patchelf --set-rpath "${
                  pkgs.lib.makeLibraryPath buildInputs
                }" "$bin" || true
              fi
            done
          '';

          postInstall = ''
          ln -s $out/share/compile_commands.json ${placeholder "out"}/compile_commands.json || true
          # or simply copy it to $out for a dev link
        '';
        };

      in {
        # `nix develop` → interactive shell
        devShells.default = pkgs.mkShell {
          inherit buildInputs nativeBuildInputs;
          # Optional: help runtime inside shell
          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath buildInputs;

          shellHook = ''
            echo "Nix devShell ready!"
            echo "Run: nix build .#"
            echo "     code ."
          '';
        };

        # `nix build .#` → reproducible package
        packages.default = pkgs.stdenv.mkDerivation baseDerivation;
      });
}
