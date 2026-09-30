# calculator_operators

This project is a low-level calculator written in C. It combines a calculator engine, memory/value-slot helpers, and a console interface to support arithmetic and bitwise operations across integer and floating-point modes.

## Overview

The latest source layout includes:

- `app_10.c` – main application, interactive loop, command parsing, CLI flags, and result output
- `calculator_proc.c` – calculator engine setup, mode switching, operation dispatch, and last-result tracking
- `slot_io.c` – value-slot input/output helpers for reading and writing numeric values
- `memory_view.c` – memory visualization for the computed value
- `add.c`, `subtract.c`, `multiply.c`, `divide.c`, `modulo.c` – arithmetic operations
- `and.c`, `or.c`, `xor.c`, `not.c`, `shift_left.c`, `shift_right.c` – bitwise and shift operations
- `include/` – shared headers for types, status codes, operator definitions, and the calculator API

## Supported modes and operations

The app supports:

- integer mode: 8, 16, 32, and 64-bit values
- signed and unsigned integer input
- floating-point mode: 32-bit and 64-bit values
- arithmetic operators:
  - `add`
  - `sub`
  - `mul`
  - `div`
  - `mod`
- bitwise operators:
  - `xor`
  - `and`
  - `or`
  - `not`
  - `shl`
  - `shr`

The engine tracks the last successful operation and can restore previous operands/results when an error occurs.

## Runtime behavior

The calculator starts with a default configuration stored in `calc_app_config` if the file does not exist:

```text
mode = int
size = 32
unsigned = false
```

At runtime the application prints the selected mode and size, then asks for:

1. `oprand_1`
2. `oprand_2`
3. `operator`

If a runtime error occurs, the app reports it and restores the last valid result.

## Interactive usage

Compile the project and run it:

```bash
gcc -std=c11 -O2 -fno-strict-aliasing *.c -I. -o calculator
./calculator
```

Then enter values in the terminal. Example:

```text
>[mode] int 32 signed
>oprand_1: 12
>oprand_2: 5
>operator: add
oprand_1: 12
oprand_2: 5
result: 17
```

The application also accepts interactive command mode by entering `?` at a prompt.

Example:

```text
>? 
>command: switch int 32
>unsigned?: true
```

Or switch to floating point mode:

```text
>? 
>command: switch float 64
```

Available command actions:

- `switch int 8|16|32|64`
- `switch float 32|64`
- `exit`
- `quit`
- `goback`

In integer mode the app prompts for sign mode after switching, using:

- `true` for unsigned
- `false` for signed

## File input and output

The latest source supports reading input and writing output through command-line arguments:

```bash
./calculator -in input.txt -out output.txt
```

- `-in` loads calculator commands and values from a text file
- `-out` writes printed output to a file
- if no arguments are provided, stdin/stdout are used

## Project structure details

### Core headers

#### `include/workspace.h`
Defines shared types, status codes, operators, and value-slot storage used by the calculator and helper functions.

#### `include/calculator.h`
Defines the calculator engine structure and API for:

- creation
- mode switching
- result tracking
- cleanup

#### `include/operator.h`
Declares the arithmetic and bitwise operator function signatures.

### Runtime engine

`calculator_proc.c` implements:

- `new_calculator()`
- `calculator_switch_mode()`
- `save_Last()` / `get_Last()`
- `calculator_destroy()`

It sets function pointers for all supported operators and stores the current calculation mode and size.

### Main application flow

`app_10.c` implements:

- app creation and teardown
- operand assignment and validation
- calculation dispatch
- shift overflow checks
- result display
- interactive command parsing
- CLI processing for file input/output

This is the entry point for the console interface and is the file that drives the actual user experience.

## Compile notes

Important: compile with the following flag because the project performs low-level value casting and byte reinterpretation:

```bash
-fno-strict-aliasing
```

Recommended build command:

```bash
gcc -std=c11 -O2 -fno-strict-aliasing *.c -I. -o calculator
```

If you want to compile only the main sources explicitly:

```bash
gcc -std=c11 -O2 -fno-strict-aliasing app_10.c calculator_proc.c slot_io.c memory_view.c add.c subtract.c multiply.c divide.c modulo.c and.c or.c xor.c not.c shift_left.c shift_right.c -I. -o calculator
```

## Error handling

The current implementation checks for common runtime conditions, including:

- invalid size selection
- invalid operator input
- division by zero in integer mode
- shift count overflow
- integer division overflow conditions
- null pointer errors

These errors are reported to the console and the app can continue using the last valid calculation state.

## Example commands

Integer example:

```text
>oprand_1: 10
>oprand_2: 3
>operator: mod
```

Output:

```text
oprand_1: 10
oprand_2: 3
result: 1
```

Bitwise example:

```text
>oprand_1: 12
>oprand_2: 10
>operator: and
```

Output:

```text
oprand_1: 12
oprand_2: 10
result: 8
```

## Notes

This project is designed for experimentation with low-level numeric representation and bit manipulation. It is useful for observing:

- integer overflow behavior
- bitwise transformations
- floating-point storage and display
- memory layout at the binary level

This makes the project suitable for learning how values are stored and processed in C at a very low level.
