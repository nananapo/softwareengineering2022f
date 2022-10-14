## binarysearch
file: binarysearch.c

#### build
```sh
$ make bin
```

#### Usage
```sh
$ ./binary 1 2 3 4 5 7 8 9 10
Key? 10
Found (Position = 8, Step = 4)
Key? 1
Found (Position = 0, Step = 3)
Key? -1
Not found (Step = 3)
Key? 11
Not found (Step = 4)
```

## hash
file: hash.c

#### build
```sh
$ make hash
```

#### change option

```makefile
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

BUCKETSIZE=9 <- change here
DELTA=2
...
```

### Usage
```sh
$ ./hash 15 13 14 1 7 0 9 2 3
Key? 1
Found (Position = 1, Step = 1)
Key? 2
Found (Position = 8, Step = 4)  
Key? 100
Not found (Step = 10) 
```
