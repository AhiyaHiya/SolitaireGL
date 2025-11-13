## Solitaire

A classic fun card game, written to demonstrate using OpenGL as your renderer, as well as the other mechanisms
needed to handle assets and such.

### Setup

For Linux (Debian based)

```
sudo apt install 
    libglfw3-dev
    libglew-dev
    libglm-dev
```

### NIX

For nix, had to use this command

```
nix-channel --add https://github.com/nix-community/nixGL/archive/main.tar.gz nixgl && nix-channel --update

# Had to use explicit version
nix-env -iA nixgl.auto.nixGLNvidia --argstr nvidiaVersion 580.82.09
```


### Refs

C++ Bindings for OpenGL: https://github.com/cginternals/glbinding/

GLFW: https://www.glfw.org/

Mesa: https://mesa3d.org/
