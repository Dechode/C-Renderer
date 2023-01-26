#!/usr/bin/bash

set -xe

gcc -Wall -Wextra -o example examples/example.c glad.c io.c -lSDL2main -lSDL2 -lSDL2_image
