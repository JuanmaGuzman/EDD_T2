#!/usr/bin/bash

# Tests passed:
# easy: 0, 1, 2, 3
# medium: 0, 1, 2
# hard: 1, 2


# Tests: pending
# hard: 0

for level in 'easy' 'medium' 'hard'; do
    for part in '0' '1' '2' '3'; do
            echo "Running test for $level $part"
            filename=$(printf "%s/test_%s.txt" $level $part)
            solutions=$(printf "%s/test_%s.txt" $level $part)

            ./matechess "tests/backtracking/tests/$filename" out.txt
            cp out.txt "tests/backtracking/student_outputs/$filename"

            diff -bq "tests/backtracking/solutions/$solutions" "tests/backtracking/student_outputs/$filename"
            if [ $? -ne 0 ]; then
                echo "Test failed\n"
            else
                echo "Test passed\n"
            fi
    done
done