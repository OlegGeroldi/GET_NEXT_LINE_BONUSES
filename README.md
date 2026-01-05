*This project has been created as part of the 42 curriculum by OlegGeroldi.*

# get_next_line

## Description

**get_next_line** is a C programming project that implements a function to read a line from a file descriptor. The goal of this project is to develop a deeper understanding of:

- Static variables in C
- File descriptor operations
- Dynamic memory allocation and management
- Buffer manipulation
- Reading from files and standard input

The project includes both a mandatory implementation and a bonus version. The bonus implementation handles multiple file descriptors simultaneously using an array of static pointers, allowing the function to maintain separate reading states for different file descriptors without losing track of where each file was last read.

## Instructions

### Compilation

The project consists of the following files:

**Mandatory version:**
- `get_next_line.c` - Main function implementation
- `get_next_line_utils.c` - Utility functions
- `get_next_line.h` - Header file

**Bonus version:**
- `get_next_line_bonus.c` - Main function with multiple fd support
- `get_next_line_utils_bonus.c` - Utility functions for bonus
- `get_next_line_bonus.h` - Header file for bonus

To compile the project:

```bash
# Compile mandatory version
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# Compile bonus version (multiple file descriptors)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

You can adjust the `BUFFER_SIZE` by changing the `-D BUFFER_SIZE=42` flag to any positive value.

### Execution

```bash
# Run the program
./gnl

# The main.c file contains a test that reads from text.txt
# You can modify main.c to test with different files or stdin
```

### Function Prototype

```c
char *get_next_line(int fd);
```

The function returns:
- The next line read from the file descriptor (including the newline character `\n` if present)
- `NULL` if there's nothing more to read or an error occurred

## Resources

### Documentation and References

- [GNU C Library - Low-Level I/O](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-I_002dO.html) - Documentation on file descriptor operations and the `read()` system call
- [C Static Variables](https://www.geeksforgeeks.org/static-variables-in-c/) - Understanding static variables and their scope
- [Dynamic Memory Allocation in C](https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm) - Reference for `malloc()` and memory management
- [File Descriptors in Unix](https://en.wikipedia.org/wiki/File_descriptor) - Overview of file descriptor concepts
- [42 School Documentation](https://42.fr/) - Official 42 curriculum resources

### AI Usage

AI tools were used during the development of this project for the following purposes:

- **Code Review and Debugging**: AI was used to review code logic and identify potential memory leaks or edge cases
- **Documentation**: AI assisted in generating clear explanations of the algorithm and structuring this README
- **Algorithm Optimization**: AI provided suggestions for improving buffer management and reducing redundant memory operations
- **Best Practices**: AI was consulted for C programming best practices regarding memory management and static variables

The core algorithm implementation and logic were developed independently, with AI serving as a supportive tool for refinement and documentation.

## Algorithm Explanation and Justification

### Selected Algorithm: Static Buffer with Dynamic Line Extraction

The implementation uses a **static remainder buffer** approach combined with dynamic memory allocation for efficient line-by-line reading.

#### Algorithm Overview

1. **Static Remainder Array**: A static array of character pointers (`static char *remainder[OPEN_MAX]`) maintains the state between function calls. Each index corresponds to a file descriptor, allowing multiple files to be read simultaneously without interference (bonus feature).

2. **Read-Ahead Strategy**: The function reads data from the file descriptor in chunks of `BUFFER_SIZE` bytes and accumulates it in the remainder buffer until a newline character (`\n`) is found or end-of-file is reached.

3. **Line Extraction**: Once sufficient data is available (up to and including a newline), the function extracts exactly one line, allocates memory for it, and returns it to the caller.

4. **Remainder Management**: After extracting a line, any leftover data (after the newline) is preserved in the static buffer for the next function call.

#### Key Functions

- `read_to_remainder()`: Reads from file descriptor until a newline is found or EOF
- `extract_line()`: Allocates and fills a new string with one complete line
- `update_remainder()`: Updates the static buffer by removing the returned line
- `fill_line()`: Helper function to copy characters from remainder to the new line

#### Justification

This algorithm was chosen for several reasons:

1. **Memory Efficiency**: By using a static buffer, we avoid re-reading data from the file system. Data read beyond the newline is preserved for subsequent calls, minimizing system calls.

2. **Flexibility**: The `BUFFER_SIZE` can be adjusted at compile time to optimize for different scenarios (small files vs. large files, memory constraints vs. performance).

3. **Multiple File Descriptor Support**: Using an array of static pointers indexed by file descriptor allows handling multiple files simultaneously, which is essential for the bonus requirements. Each file descriptor maintains its own independent state.

4. **Simplicity and Robustness**: The algorithm has a clear separation of concerns - reading, extracting, and updating are handled by separate functions, making the code more maintainable and easier to debug.

5. **Edge Case Handling**: The implementation handles various edge cases:
   - Empty files
   - Files without newlines at the end
   - Large lines exceeding `BUFFER_SIZE`
   - Invalid file descriptors
   - Memory allocation failures

6. **Performance**: By reading in larger chunks (`BUFFER_SIZE` bytes) rather than byte-by-byte, the number of expensive `read()` system calls is minimized, improving overall performance.

#### Trade-offs

- **Memory Usage**: The static array uses `OPEN_MAX * sizeof(char *)` bytes continuously, even when not all file descriptors are in use. This is acceptable given that `OPEN_MAX` is typically 1024 on most systems, resulting in only 8KB on 64-bit systems.

- **Complexity**: The bonus version with multiple file descriptors adds complexity compared to a single static pointer, but this is necessary to meet the project requirements and provides valuable real-world functionality.

The algorithm strikes an optimal balance between performance, memory efficiency, and code clarity, making it well-suited for the get_next_line project requirements.
