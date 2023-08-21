#!/bin/sh
gcc -O3 ./src/main.c ./src/go.c ./src/go_renderer.c -o go -lraylib -lm
