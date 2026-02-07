#!/bin/bash
# Run clang-tidy on the project source files

set -e

echo "Running clang-tidy on source files..."
clang-tidy src/c/main.c

echo ""
echo "Done!"
