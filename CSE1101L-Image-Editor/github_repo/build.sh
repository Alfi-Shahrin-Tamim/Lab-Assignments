#!/bin/bash
cd "$(dirname "$0")"
gcc -Wall -Wextra -o editor *.c -I$HOME/include -L$HOME -liup -lcd -lm || exit 1
echo "Build OK. Running..."
LD_LIBRARY_PATH=$HOME ./editor
