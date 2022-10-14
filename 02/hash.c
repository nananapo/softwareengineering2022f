#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int	table[BUCKETSIZE];
int	g_step;

// fill hashtable with -1
void	hash_init(void)
{
	for (int i=0; i < BUCKETSIZE; i++)
		table[i] = -1;
}

// add value(>=0) to hashtable
void	hash_add(int value)
{
	int	pos;
	int	count;

	// value is valid?
	if (value < 0)
	{
		printf("You can't add negative value. (value = %d)\n", value);
		return ;
	}

	// open addressing
	count = 0;
	pos = value % BUCKETSIZE;
	while (count++ < BUCKETSIZE && table[pos] != -1)
		pos = (pos + DELTA) % BUCKETSIZE;

	// overflow check
	if (count >= BUCKETSIZE)
	{
		printf("overflow\n");
		return ;
	}

	// set value
	table[pos] = value;
}

// search value(>0) and return position of value.
// or return -1
int	hash_search(int value)
{
	int	pos;

	// value is valid?
	if (value < 0)
	{
		printf("You can't search negative value. (value = %d)\n", value);
		return (-1);
	}

	// open addressing 
	pos = value % BUCKETSIZE;
	g_step = 0;
	while (g_step++ < BUCKETSIZE && table[pos] != value && table[pos] != -1)
		pos = (pos + DELTA) % BUCKETSIZE;

	return (table[pos] == value) ? pos : -1;
}

int	main(int argc, char **argv)
{
	int	key;
	int	result;

	// init
	hash_init();

	// check argument
	if (argc <= 1)
	{
		printf("Usage: %s numbers...\n", argv[0]);
		return (1);
	}

	// read int & add to hash table
	for (int i = 1; i < argc; i++)
		hash_add(atoi(argv[i]));

	// loop
	while (1)
	{
		printf("Key? ");
		scanf("%d", &key);
		result = hash_search(key);

		if (result == -1)
			printf("Not found (Step = %d)\n", g_step);
		else
			printf("Found (Position = %d, Step = %d)\n", result, g_step);
	}
}
