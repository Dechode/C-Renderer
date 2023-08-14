#!/usr/bin/bash

set -xe

gcc -Wall -Wextra -o example_3d examples/example_3d.c renderer/renderer.c renderer/3d/renderer_3d.c glad.c io.c renderer/shader.c renderer/texture.c window.c renderer/3d/mesh.c renderer/camera.c -lSDL2main -lSDL2 -lSDL2_image -lm

