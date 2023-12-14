#!/bin/bash
# usage: ../cse-101-public-tests/pa3/pa3.sh
# (run within your pa3 directory to test your code)

RELATIVE_PATH="."
EXE_ALL=( pa3-func-check.sh pa3-lunit-check.sh pa3-gunit-check.sh pa3-make-check.sh )
EXE_RANGE=$((${#EXE_ALL[*]} - 1))
echo $EXE_RANGE
for i in $(seq 0 $EXE_RANGE); do
  FULLPATH="$RELATIVE_PATH/${EXE_ALL[i]}"
  chmod +x $FULLPATH
  ./$FULLPATH
done