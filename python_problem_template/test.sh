#!/bin/bash
# assumes .in files have corresponding .ans files of the same name
for in_file in tests/*.in; do
    name=$(echo "$in_file" | sed "s/\..*//") # remove the file extension
    out_file=$(echo "$name".ans) # get corresponding .ans file
    tmp=$(mktemp) # make temp file for comparing outputs
    python3 main.py < "$in_file" > "$tmp" # read from in file, write to temp file
    if diff --report-identical-files --side-by-side "$tmp" "$out_file" > /dev/null; then # if same, discard output and just write OK
        echo "OK"
    else # if not same, print FAIL and write the difference in outputs.
        echo "FAIL"
        diff --report-identical-files --side-by-side "$tmp" "$out_file" 
    fi
    rm "$tmp" # delete temporary file
done