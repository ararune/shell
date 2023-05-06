## Linux Shell

This is a simple shell program written in C. It supports basic shell commands such as `cd`, `ls`, `touch`, `rm`, `rmdir`, `mkdir`, `find`, `fetch`, and `exit`.

## Table of Contents

- [Getting Started](#getting-started)
- [Usage](#usage)


## Getting Started

To compile and run the shell program, you need to have a C compiler installed on your system, such as `gcc`.
Navigate to the root directory of the project in your terminal and run the following command : 

```bash
gcc -o shell *.c
```

Then, to start the shell, run the following command:
```bash
./shell
```

Alternatively, simply run the pre-built script to compile and run the shell :

```bash
./run.sh
```

## Usage

The shell supports the following commands:

-   `cd <directory>` - Change the current working directory to `directory`
-   `ls` - List the contents of the current working directory
-   `touch <file>` - Create a new empty file with the name `file`
-   `rm <file>` - Delete the file with the name `file`
-   `rmdir <directory>` - Delete the directory with the name `directory`
-   `mkdir <directory>` - Create a new empty directory with the name `directory`
-   `cdir <directory>` - Create a new empty `directory` and change the current working `directory`
-   `find <file|directory>` - List full path of `file` or `directory`,  searching from the home directory
-   `fetch` - Display system information
