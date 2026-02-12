# Generic Quicksort Library and Sort CLI

A portable C library providing generic in-place quicksort (Lomuto partition) for any element type via function pointers, plus a `sort` executable stub intended to sort lines from a file or stdin.

## Features

- **Generic quicksort**: Works on arbitrary element types using `void*` and a comparator; no code changes required for new types beyond providing a comparison function.
- **Lomuto partitioning**: In-place partitioning with pivot at left index; O(n) space for recursion.
- **Built-in comparators**: `int_cmp`, `dbl_cmp`, and `str_cmp` for integers, doubles, and strings (char*).
- **Reusable library**: `quicksort()` and comparators are in a single translation unit and can be linked into other programs.
- **Sort program**: The `sort` binary is built and linked against the library; see [Limitations](#limitations--future-work) for current behavior.

## Build

Requires a C99-capable compiler (e.g. `gcc` or `clang`).

```bash
make all
```

This produces the `sort` executable in the project root. To clean build artifacts:

```bash
make clean
```

## Usage

### Using the library in your own code

Include `include/quicksort.h` and link with `src/quicksort.c`. Example for an array of integers:

```c
#include "quicksort.h"

int a[] = { 3, 1, 4, 1, 5 };
size_t n = sizeof(a) / sizeof(a[0]);
quicksort(a, n, sizeof(int), int_cmp);
```

### Using the `sort` executable

The `sort` program is built and runnable. **Current behavior**: it exits successfully without reading arguments or input. See [Limitations](#limitations--future-work).

```bash
./sort
./sort -i
./sort -d input.txt
```

Intended (future) interface:

- `./sort [-i|-d] [filename]` — `-i` for integers, `-d` for doubles, no flag for strings; optional filename or stdin.

## Design and architecture

- **Generic interface**: `quicksort(void *array, size_t len, size_t elem_sz, int (*cmp)(const void*, const void*))` sorts `array` in place. `elem_sz` is the size of one element; `cmp` returns negative / zero / positive like `strcmp`.
- **Byte-level swap**: Elements are swapped one byte at a time so the code works for any type without further changes.
- **Lomuto partition**: Pivot is the left element; partition index is computed in one pass; then recursive calls sort the left and right segments.

## Error handling and edge cases

- **Library**: Handles `array == NULL` and `len <= 1` by doing nothing. Comparators assume valid pointers.
- **Sort CLI**: Not implemented yet; see [Limitations](#limitations--future-work).

## Testing

Run the test script (builds and runs the `sort` executable to verify it links and runs):

```bash
make test
```

Or manually:

```bash
./scripts/test.sh
```

The script ensures the project builds and that `./sort` runs and exits with code 0.

## Limitations / Future work

- **Sort CLI is a stub**: The `sort` program currently contains no argument parsing or I/O. It always returns `EXIT_SUCCESS` and does not read from stdin or files. You may see compiler warnings about unused `argc`/`argv` until the CLI is implemented. Planned improvements:
  - Use `getopt` to support `-i` (integers), `-d` (doubles), and optional filename.
  - Read lines from the given file or from stdin, parse by type, sort with the appropriate comparator, and print one element per line.
  - Implement the full set of required error messages (invalid option, cannot open file, too many files/flags, etc.).
- **No randomized pivot**: Current implementation uses the leftmost element as pivot; for better average-case behavior on sorted or nearly sorted data, consider a random or median-of-three pivot.
- **No tests for the library**: Adding a small test program that sorts int/double/string arrays and checks results would improve robustness.

## License

MIT (see [LICENSE](LICENSE)).
