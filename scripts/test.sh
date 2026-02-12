#!/usr/bin/env bash
# Build and run basic tests for generic-quicksort.
# - Builds the project and runs the sort executable (stub) to verify it links and runs.
set -e
cd "$(dirname "$0")/.."
echo "Building..."
make clean
make all
echo "Running sort (stub; should exit 0)..."
./sort
echo "OK: build and run passed."
