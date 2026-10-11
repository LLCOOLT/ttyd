#!/bin/sh
# fnasm.sh <module>/<asm path without .s>... : print the functions of REL asm files without address columns
for p in "$@"; do
    echo "=== $p"
    m=${p%%/*}; f=${p#*/}
    awk '/^\.fn/,/^\.endfn/' build/G8MJ01/$m/asm/$f.s | sed 's/^\/\* [0-9A-F]* [0-9A-F]*  [0-9A-F ]* \*\/\t//'
done
