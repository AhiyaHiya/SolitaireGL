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
