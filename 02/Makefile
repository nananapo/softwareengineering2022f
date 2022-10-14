CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

BUCKETSIZE=9
DELTA=2

bin:
	$(CC) $(CFLAGS) binarysearch.c -o binary

hash:
	$(CC) $(CFLAGS) hash.c -DBUCKETSIZE=$(BUCKETSIZE) -DDELTA=$(DELTA) -o hash
	
clean:
	rm -rf binary hash

.PHONY: bin hash clean
