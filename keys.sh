#!/bin/bash

# File path ADD YOUR KEYBIND FILE HERE!
FILE=""

# Process the file to handle multi-line blocks, format bind lines, and remove single-line comments
awk '
BEGIN {
    FS = "\n";
    RS = "";
    OFS = "\n";
    ORS = "\n";
}
{
    if ($1 ~ /^# ┏/ && $2 ~ /^# ┃/ && $3 ~ /^# ┗/) {
        # Print multi-line block as is
        print $0;
    } else {
        # Process other lines
        for (i = 1; i <= NF; i++) {
            if ($i ~ /^bind/) {
                if ($i !~ /^bind = ,/) {
                    sub(/^bind[em]* = /, "", $i);
                    split($i, arr, ",");
                    cmd = "";
                    for (j = 3; j <= length(arr); j++) {
                        cmd = cmd arr[j] (j < length(arr) ? "," : "");
                    }
                    print arr[1] "," arr[2] "," cmd;
                }
            } else if ($i !~ /^#/) {
                # Print non-comment lines
                print $i;
            }
        }
    }
}
' "$FILE"
