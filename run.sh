#!/bin/bash

clear

gcc -I ./include ./src/*.c -o ./dsprocess 

# trap 'rm -f ./dsprocess' EXIT INT

# ./dsprocess 

# rm ./dsprocess
