#!/bin/bash
mkfifo fronta;
time ./$1 < fronta | tee logs/solver.log | ./bin/Debug/Text_adventure_problem | tee logs/checker.log > fronta;
echo $?
rm fronta;
