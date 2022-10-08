#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	*bubblesort(void *base, size_t num, size_t width, int (*cmp)(const void *, const void *))
{
	void	*tmp;
	void	*left, *right;
	size_t	i,j;

	tmp = malloc(width);
	if (tmp == NULL)
		return (NULL);
	for (i = 0; i < num; i++)
	{
		for (j = num - 1; i < j; j--)
		{
			left = base + (j - 1) * width;
			right = base + j * width;
			if (cmp(left, right) > 0)
			{
				memcpy(tmp, left, width);
				memcpy(left, right, width);
				memcpy(right, tmp, width);
			}
		}
	}
	return (base);
}

int	cmp(const void *a, const void *b)
{
	int *i, *j;
	i = (int *)a;
	j = (int *)b;
	return (*i - *j);
}

int	main(void)
{
	int	len = 5;
	int	a[] = {5,4,3,2,1};
	bubblesort(a, len, sizeof(int), cmp);
	for (int i = 0; i < len; i++)
	{
		if (i != 0) printf(" ");
		printf("%d", a[i]);
	}
}
