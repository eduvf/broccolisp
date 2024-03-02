#!/bin/bash

cc *.c -o broccolisp -lraylib -lm -lreadline
./broccolisp
rm broccolisp