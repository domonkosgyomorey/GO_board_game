#!/bin/sh
gcc ./src/main.c ./src/go.c ./src/go_renderer.c -o go -lraylib -lm
