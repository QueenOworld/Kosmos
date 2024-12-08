#!/bin/bash
args=$(echo $(cat ./compile_flags_debug.txt) | tr '\n' ' ')
clang++ ${args[@]}
