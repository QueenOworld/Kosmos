#!/bin/bash
args=$(echo $(cat ./compile_flags.txt) | tr '\n' ' ')
clang++ ${args[@]}
