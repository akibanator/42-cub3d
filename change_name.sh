#!/bin/bash

cd ./src_bonus
find . -type f -name "*.c" -exec sh -c 'file="{}"; mv -- "$file" "${file%.c}_suffix.c"' \;
