#include <stdio.h>
#include <stdlib.h>

static int g_step;

int	binarysearch_int(int *A, int K, int leftInclusive, int rightInclusive)
{
	int	i,j,mid;

	g_step = 0;
	i = leftInclusive;
	j = rightInclusive;
	while (i <= j)
	{
		g_step += 1;
		mid = i + (j - i) / 2;
		if (A[mid] == K)
			return (mid);
		if (A[mid] < K)
			i = mid + 1;
		else
			j = mid - 1;
	}
	return (-1);
}

static int cmpint(const void *a, const void *b)
{
	int *i, *j;

	i = (int *)a;
	j = (int *)b;
	return (*i - *j);
}

int	main(int argc, char **argv)
{
	int	*A;
	int	key;
	int	result;

	if (argc <= 1)
	{
		printf("Usage: %s numbers...\n", argv[0]);
		return (1);
	}

	// malloc
	A = malloc(sizeof(int) * (argc - 1));
	if (A == NULL) return (1);

	// read int
	for (int i = 1; i < argc; i++)
		A[i-1] = atoi(argv[i]);
	// sort
	qsort(A, argc - 1, sizeof(int), cmpint);

	// loop
	while (1)
	{
		printf("Key? ");
		scanf("%d", &key);
		result = binarysearch_int(A, key, 0, argc - 2);
		if (result == -1)
			printf("Not found (Step = %d)\n", g_step);
		else
			printf("Found (Position = %d, Step = %d)\n", result, g_step);
	}
}
