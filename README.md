*This project has been created as part of the 42 curriculum by rkosa*

---
# Project: Get next line
`get_next_line()` is a function that returns a line read from a file descriptor.

## Description
The goal of this project is to implement a highly useful function while learning about one of C's most important concept: **`static variables`**.

### Prototype:
```c 
char    *get_next_line(int fd);
```
### Parameters: 
- *`fd`: The file descriptor to read from*

### Return Value:
- *Read line:  correct behavior*
- *NULL: end of file reached, or an error occurred*

### External Functions used:
`read()` `malloc()` `free()`

## How it works:
The function uses a static variable called `stash` to store data that has been read but not yet returned.

Whenever `get_next_line()` is called:

1. It starts reading from the given file descriptor if the stash does not have a newline. 
2. It keeps reading until a newline is found or EOF is reached appending the new data to the stash.
3. It extracts the next line from the stash.
4. It updates the stash with the remaining unread data.
5. It returns the extracted line.
6. The next call continues using the data that is saved in the stash.

## Notes:
If the file descriptor is invalid, or the `BUFFER_SIZE` is less than or equal to zero, the function returns `NULL`.

If `read()` or `malloc()` fails, the function also returns `NULL`.

The `BUFFER_SIZE` is defined in the header file and can be manually modified there, or through compilation.
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
```

## Known issues:
The current implementation allocates only the required amount of memory every time additional data is read.

Using a very small `BUFFER_SIZE` with a giant line may result in poor performance because the entire stash is copied on every read.

A possible improvement would be to grow the allocatation exponentially instead of allocating just enough memory after every read.

## Instructions

No Makefile has been created...

1. Clone the repo to your project folder 
```bash
git clone git@github.com:Hattyuh/gnl.git projectfolder
```

2. Include the header file in your program
```c
#include "get_next_line.h"
```

3. Call the function in your file with a valid file descriptor
```c
int		fd;
char	*line;
	
fd = open("filename", O_RDONLY);
line = get_next_line(fd);
close(fd);
```


## Resources

To better understand static variables and for basic programming related issues I found answers:
- https://www.geeksforgeeks.org/c/c-programming-language/
- https://www.w3schools.com/c/index.php

Special thanks to my peer **`Thomas Eder`** for motivating me while I was working on this project.

## AI usage

Sometimes I used AI to simulate peer discussions and help me better understand concepts. It also helped me to create this README.

Chatgpt:
- https://chatgpt.com/

## Author

Richard Kosa

GitHub:
https://github.com/Hattyuh