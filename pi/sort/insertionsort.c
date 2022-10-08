#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void	*insertionsort(void *base, size_t num, size_t width, int (*cmp)(const void *, const void *))
{
	size_t	i, j, select;
	void	*tmp;

	tmp = malloc(width);
	if (tmp == NULL)
		return (NULL);
	for (i = 0; i < num; i++)
	{
		select = i;
		for (j = i + 1; j < num; j++)
		{
			if (cmp(base + j * width, base + select * width) < 0)
				select = j;
		}
		if (i == select) continue ;
		memcpy(tmp, base + select * width, width);
		memcpy(base + select * width, base + i * width, width);
		memcpy(base + i * width, tmp, width);
	}
	free(tmp);
	return (base);
}

int	cmp(const void *a, const void *b)
{
	int	*i, *j;
	i = (int *)a;
	j = (int *)b;
	return (*i - *j);
}

int	main(void)
{
	int len = 10;
	int a[] = {0,2,4,6,8,1,3,5,7,9};
	insertionsort(a, len, sizeof(int), cmp);
	for (int i = 0; i < len; i++)
	{
		if (i != 0) printf(" ");
		printf("%d", a[i]);
	}
}
