#!/bin/bash

# Define the commands to run
commands=(
    "python3 symnmf.py 5 sym input_1.txt"
    "python3 symnmf.py 5 ddg input_1.txt"
    "python3 symnmf.py 5 norm input_1.txt"
    "python3 symnmf.py 5 symnmf input_1.txt"
    "python3 analysis.py 5 input_1.txt"
    "./symnmf sym input_1.txt"
    "./symnmf ddg input_1.txt"
    "./symnmf norm input_1.txt"
    
    "python3 symnmf.py 4 sym input_2.txt"
    "python3 symnmf.py 4 ddg input_2.txt"
    "python3 symnmf.py 4 norm input_2.txt"
    "python3 symnmf.py 4 symnmf input_2.txt"
    "python3 analysis.py 4 input_2.txt"
    "./symnmf sym input_2.txt"
    "./symnmf ddg input_2.txt"
    "./symnmf norm input_2.txt"
    
    "python3 symnmf.py 7 sym input_3.txt"
    "python3 symnmf.py 7 ddg input_3.txt"
    "python3 symnmf.py 7 norm input_3.txt"
    "python3 symnmf.py 7 symnmf input_3.txt"
    "python3 analysis.py 7 input_3.txt"
    "./symnmf sym input_3.txt"
    "./symnmf ddg input_3.txt"
    "./symnmf norm input_3.txt"
)

# Run each command in sequence, with labeled output and separation
run_number=1
for cmd in "${commands[@]}"; do
    echo "Run #$run_number: $cmd"
    eval "$cmd"
    echo "-_-_-_-"
    ((run_number++))
done
