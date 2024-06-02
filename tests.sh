#!/bin/bash

clear

gcc -I ./include -o ./tests/tests ./tests/main.c $(find ./src -name '*.c' ! -name 'main.c')

trap 'rm -f ./dsprocess' EXIT INT

./tests/tests

rm ./tests/tests
