#!/bin/bash

file="main.cpp"
output=$(echo "$file" | sed "s/\..*//")
ARGS=" $* "

# g++ -g -O2 -o "$output" -std=gnu++23 -static -lrt -Wl,--whole-archive -lpthread -Wl,--no-whole-archive "$file"
g++ -o "$output" "$file" -std=gnu++20 -Wall -fsanitize=address

for in_file in tests/*.in; do
    if [[ "$ARGS" == *" --debug "* ]]; then
        ./$output < "$in_file"
        exit
    fi
    
    name=$(echo "$in_file" | sed "s/\..*//")
    out_file=$(echo "$name".ans)
    tmp=$(mktemp)
    ./$output < "$in_file" > "$tmp"
    
    if diff --report-identical-files --side-by-side "$tmp" "$out_file" > /dev/null; then
        echo "OK"
    else
        echo "FAIL"
        diff --report-identical-files --side-by-side "$tmp" "$out_file" 
    fi
    rm "$tmp"
done