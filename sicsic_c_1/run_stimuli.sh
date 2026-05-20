#!/bin/bash

STIMULI_DIR="stimuli"
MAIN="./code/main"
WIN_EXE="./assignment_details/win.exe"

# Check if wine is available
if command -v wine &> /dev/null; then
    USE_REF=1
    echo "Wine detected - generating expected output from win.exe"
else
    USE_REF=0
    echo "Wine not found - using pre-generated expected.txt files (if available)"
fi

# Compile main
echo "Compiling main.c..."
gcc -o code/main code/main.c
if [ $? -ne 0 ]; then
    echo "ERROR: Compilation failed"
    exit 1
fi
echo "Compilation successful."
echo ""

TOTAL=0
PASSED=0
FAILED=0

for test_dir in "$STIMULI_DIR"/*/; do
    test_name=$(basename "$test_dir")
    input_file="$test_dir/input.txt"
    actual_file="$test_dir/actual.txt"
    expected_file="$test_dir/expected.txt"
    diff_file="$test_dir/diff.txt"

    if [ ! -f "$input_file" ]; then
        continue
    fi

    # Use pre-generated expected.txt if available, otherwise fall back to wine
    if [ ! -f "$expected_file" ]; then
        if [ $USE_REF -eq 1 ]; then
            sed 's/\r//' "$input_file" | wine "$WIN_EXE" 2>/dev/null | tr -d '\r' > "$expected_file"
        else
            echo "[$test_name] SKIP - no pre-generated expected.txt and wine not found"
            continue
        fi
    fi

    # Run main
    "$MAIN" < "$input_file" > "$actual_file" 2>/dev/null

    TOTAL=$((TOTAL + 1))

    # Compare (strip \r from expected in case of Windows CRLF line endings)
    if diff <(tr -d '\r' < "$expected_file") "$actual_file" > "$diff_file" 2>&1; then
        echo "[$test_name] PASS"
        PASSED=$((PASSED + 1))
        rm -f "$diff_file"
    else
        echo "[$test_name] FAIL - see $test_dir/diff.txt"
        FAILED=$((FAILED + 1))
        head -20 "$diff_file"
        echo "..."
    fi
    echo ""
done

echo "==============================="
echo "Results: $PASSED/$TOTAL passed"
if [ $FAILED -gt 0 ]; then
    echo "FAILED: $FAILED test(s)"
else
    echo "All tests passed!"
fi
echo "==============================="
