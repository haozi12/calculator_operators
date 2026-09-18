# calculator_operators

This project contains a console calculator app built around `app_10.c`. It supports both integer and floating-point calculations, variable operand sizes, bitwise operators, and interactive mode switching.

## What the app does

`app_10.c` creates a `calc_app_t` object that wraps a low-level calculator engine. The app can:

- work in `int` mode or `float` mode
- use operand sizes `8`, `16`, `32`, or `64` bits
- use signed or unsigned integer mode
- perform arithmetic and bitwise operations
- print the result and memory view of the value
- accept input from stdin or from a file via command-line arguments

Supported operators:

- Bitwise: `xor`, `and`, `or`, `not`, `shl`, `shr`
- Arithmetic: `add`, `sub`, `mul`, `div`, `mod`

The app also checks for common runtime issues, such as:

- invalid size selection
- division by zero in integer mode
- shift count overflow
- null pointer errors

## How the program works

When the program starts, it creates a default calculator in:

- mode: integer
- size: 32-bit
- sign: signed

Then it asks for:

1. `oprand_1`
2. `oprand_2`
3. `operator`

After calculation it prints the result and memory representation.

You can also enter a command at the prompt by typing `?`, then switching mode or exiting the app.

## Interactive usage

The app works in a terminal session. Example flow:

```text
>[mode] int 32 signed
>oprand_1: 12
>oprand_2: 5
>operator: add
oprand_1: 12
oprand_2: 5
result: 17
```

To switch modes:

```text
>? 
>command: switch int 32
>unsigned?: true
```

or

```text
>? 
>command: switch float 64
```

Available command options:

- `switch int 8|16|32|64`
- `switch float 32|64`
- `exit`
- `quit`

## File input and output

You can run the app with files instead of interactive console input:

```bash
./calculator -in input.txt -out output.txt
```

- `-in` reads commands and values from a text file
- `-out` writes the app output to a file
- if no arguments are given, it uses `stdin` and `stdout`

## Compile instructions

Important: compile with the `-fno-strict-aliasing` option. This project does low-level value casting and pointer reinterpretation, and GCC/Clang can otherwise optimize in a way that changes behavior.

### GCC

```bash
gcc -std=c11 -O2 -fno-strict-aliasing *.c -I. -o calculator
```

### Clang

```bash
clang -std=c11 -O2 -fno-strict-aliasing *.c -I. -o calculator
```

If you prefer to compile only the main app source with all helper files explicitly listed, use:

```bash
gcc -std=c11 -O2 -fno-strict-aliasing app_10.c calculator_proc.c slot_io.c memory_view.c add.c subtract.c multiply.c divide.c modulo.c and.c or.c xor.c not.c shift_left.c shift_right.c -I. -o calculator
```

### Notes

- `-I.` tells the compiler to include the project root and header directory structure.
- The `-fno-strict-aliasing` flag is intentionally required for this project.
- If you get compiler warnings about `strtoull`, `strtoll`, or `atof`, they are usually harmless for this app, but using a modern C standard is recommended.

## Example commands

```text
>oprand_1: 10
>oprand_2: 3
>operator: mod
```

Result:

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

Result:

```text
oprand_1: 12
oprand_2: 10
result: 8
```

## Notes about the implementation

The project is designed as a bit-level calculator using custom `value_slot` memory blocks and function pointers. This is useful for experimenting with:

- integer overflow behavior
- bitwise transformations
- floating-point value printing
- low-level memory representation

This makes it a good tool for studying how data is stored and manipulated at the binary level.

## Quick start

```bash
gcc -std=c11 -O2 -fno-strict-aliasing *.c -I. -o calculator
./calculator
```

Then type values and operators in the terminal.

## Troubleshooting

- If the compiled app exits immediately, make sure you are compiling all source files, not just `app_10.c`.
- If you see incorrect results, confirm the `-fno-strict-aliasing` flag is present.
- If you enter a shift count larger than the selected bit width, the app will report `SHIFT_OVERFLOWED`.
- If you divide by zero in integer mode, the app reports `INTEGER_ZERO_DIVISION`.


