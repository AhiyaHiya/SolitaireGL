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
    libimgui-dev
```

### Preflight

For preflighting build in a Docker image

```
sudo docker build -t demo-solitaire-gl -f ./Docker/Dockerfile.pop_os .
```


### NIX

For nix, had to use this command


```
nix-channel --add https://github.com/nix-community/nixGL/archive/main.tar.gz nixgl && nix-channel --update

# Had to use explicit version
nix-env -iA nixgl.auto.nixGLNvidia --argstr nvidiaVersion 580.82.09
```
