
# xdump


<img width="1276" height="453" alt="xdmp_kernel32dll" src="https://github.com/user-attachments/assets/5dbfbe97-d068-490f-9dde-74ff0fb27e4c" />

This is a small hexdump tool written in C.

When working with tools like **GDB**, **Ghidra**, or doing **reverse engineering**, you often need to inspect the raw bytes of a file or extract readable strings to see functions, imports or plain text. This tool allows you to view binary files directly from the terminal, displaying their hexadecimal representation, their offset and their ASCII interpretation and specify the number of lines that you want to see. Or you can also extract strings. Two functions in a single tool.

It is a simple project, but it is useful for studying low-level programming, binary analysis, and understanding how data is stored inside files.

### Requirements

You only need a C compiler.

Linux (GCC):

```bash
sudo apt install gcc
```

Compile the program:

```bash
gcc xdump.c utils.c -o xdmp
```

### Usage

Run the program by passing the file you want to analyze:

```bash
./xdmp <option> <file>
```

At the moment, this tools has two options:
### a) Hexdump 

```bash
./xdmp d <file>
```
You can also limit the number of displayed lines:

```bash
./xdmp d <file> <lines>
```

Output:

```
Offset         00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F    Decoded Text

00000000       4d   5a   90   00   03   00   00   00   04   00   00   00   00   00   00   00    MZ..............
```

### b) Strings
Similar to strings unix tool, you can also extract the strings from the file:


```bash
./xdmp s <file>
```

## Features

* Read binary files.
* Display file bytes in hexadecimal format.
* Show ASCII representation (only readable characters).
* Colored output using ANSI escape sequences (the byte and the ASCII representation).
* You can choose line limit for the hexdump.
* Works with different file types, including executables.
* Extract the strings from the file for a better individual analysis.

## Notes

* This project was created to practice file handling in C (`FILE`, `fopen`, `fgetc`) and understand how binary data is represented.
* It was developed as a learning tool for low-level programming and reverse engineering (my own tool for studies and reversing).
* The goal is NOT to replace existing utilities like `hexdump`, but to implement a simple version from scratch.

Enjoy!
