
# xdump

<img width="1276" height="453" alt="xdmp_kernel32dll" src="https://github.com/user-attachments/assets/54d4d764-2685-48ff-912d-76a9559b6159" />

This is a small hexdump tool written in C.

When working with tools like **GDB**, **Ghidra**, or doing **reverse engineering**, you often need to inspect the raw bytes of a file. This tool allows you to view binary files directly from the terminal, displaying their hexadecimal representation and their ASCII interpretation. You can also specify the number of lines that you want to see.

It is a simple project, but it is useful for studying low-level programming, binary analysis, and understanding how data is stored inside files.

### Requirements

You only need a C compiler.

Linux (GCC):

```bash
sudo apt install gcc
```

Compile the program:

```bash
gcc xdump.c converter.c -o xdmp
```

### Usage

Run the program by passing the file you want to analyze:

```bash
./xdmp <file>
```

You can also limit the number of displayed lines:

```bash
./xdmp <file> <lines>
```

### Example

```bash
./xdmp program.exe
```

Output:

```
Offset  00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F    Decoded Text

0       4d   5a   90   00   03   00   00   00   04   00   00   00   00   00   00   00    MZ..............
```

Limit output:

```bash
./xdmp program.exe 10
```

## Features

* Read binary files.
* Display file bytes in hexadecimal format.
* Show ASCII representation (only readable characters).
* Colored output using ANSI escape sequences (the byte and the ASCII representation).
* You can choose line limit.
* Works with different file types, including executables.

## Notes

* This project was created to practice file handling in C (`FILE`, `fopen`, `fgetc`) and understand how binary data is represented.
* It was developed as a learning tool for low-level programming and reverse engineering (my own tool for studies and reversing).
* The goal is not to replace existing utilities like `hexdump`, but to implement a simple version from scratch.


Enjoy!
