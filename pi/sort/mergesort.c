#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static void	*mergesort_rec(void *base, size_t num, size_t width, int (*cmp)(const void *, const void *))
{
	void	*tmp;
	void	*left, *right;
	int		lsize, rsize;
	size_t	li, ri;

	if (num == 0)
		return (NULL);

	tmp = malloc(width * num);
	if (tmp == NULL)
		return (NULL);

	if (num == 1)
	{
		memcpy(tmp, base, width);
		return (tmp);
	}

	lsize = num / 2;
	rsize = num - lsize;
	left = mergesort_rec(base, lsize, width, cmp);
	right = mergesort_rec(base + lsize * width, rsize, width, cmp);
	if ((lsize != 0 && left == NULL)
	|| (rsize != 0 && right == NULL))
	{
		if (left != NULL) free(left);
		if (right != NULL) free(right);
		return (NULL);
	}

	li = 0;
	ri = 0;
	while (li < lsize || ri < rsize)
	{
		if (li < lsize && (ri == lsize || cmp(left + width * li, right + width * ri) < 0))
		{
			memcpy(tmp + (li+ri) * width, left + width * li, width);
			li += 1;
		}
		else
		{
			memcpy(tmp + (li+ri) * width, right + width * ri, width);
			ri += 1;
		}
	}

	if (left == NULL) free(left);
	if (right == NULL) free(right);
	return (tmp);
}

void	*my_mergesort(void *base, size_t num, size_t width, int (*cmp)(const void *, const void *))
{
	void	*tmp;
	size_t	i;

	if (num == 0)
		return (base);

	tmp = mergesort_rec(base, num, width, cmp);
	if (tmp == NULL)
		return (NULL);
	memcpy(base, tmp, num * width);
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
	int	len = 10;
	int	a[] = {1,3,5,9,7,0,2,4,6,8};
	my_mergesort(a, len, sizeof(int), cmp);

	for (int i=0; i < len; i++)
	{
		if (i != 0)	printf(" ");
		printf("%d", a[i]);
	}
}
