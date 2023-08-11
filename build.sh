#!/usr/bin/bash

set -xe

gcc -Wall -Wextra -o example examples/example.c renderer.c renderer_2d.c renderer_3d.c primitives_3d.c glad.c io.c shader.c texture.c sprite.c window.c mesh.c camera.c -lSDL2main -lSDL2 -lSDL2_image -lm

