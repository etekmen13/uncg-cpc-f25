#!/bin/bash

src="$1"
out="${src%.cpp}.out"
g++ "$src" -std=gnu++20 -o "$out" -I ./

./"$out" 