#include <stdio.h>
#include "functions.h"

void swap_clr(color *a, color *b)
{
	color aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void transpose_clr(color **a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			swap_clr(&a[i][j], &a[j][i]);
}

void reversecolnegative_clr(color **a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0, k = n - 1; j < k; j++, k--)
			swap_clr(&a[j][i], &a[k][i]);
}

void reversecolnpositive_clr(color **a, int n)
{
	for (int i = 0, k = n - 1; i < k; i++, k--)
		for (int j = 0; j < n; j++)
			swap_clr(&a[j][i], &a[j][k]);
}

void rotate90pos_clr(color **a, int n)
{
	transpose_clr(a, n);
	reversecolnpositive_clr(a, n);
}

void rotate90neg_clr(color **a, int n)
{
	transpose_clr(a, n);
	reversecolnegative_clr(a, n);
}

void rotate180_clr(color **a, int n)
{
	for (int i = 0 ; i < n / 2; i++)
		for (int j = 0; j < n; j++)
			swap_clr(&a[i][j], &a[n - 1 - i][n - 1 - j]);

	if (n % 2 != 0)
		for (int j = 0 ; j < n / 2; j++)
			swap_clr(&a[n / 2][j], &a[n / 2][n - j - 1]);
}

void extract_submat_clr(color **dest, color **source, pixel_t s)
{
	int k = 0;
	for (int i = s.y1; i < s.y2; i++, k++) {
		int l = 0;
		for (int j = s.x1; j < s.x2; j++, l++)
			dest[k][l] = source[i][j];
	}
}

void replace_original_clr(color **dest, color **source, pixel_t s)
{
	int k = 0;
	for (int i = s.y1; i < s.y2; i++, k++) {
		int l = 0;
		for (int j = s.x1; j < s.x2; j++, l++)
			dest[i][j] = source[k][l];
	}
}

void rotate_all_90neg_clr(color **dest, color **source, int n, int m)
{
	int k, l;
	k = 0;
	for (int i = 0; i < n; i++, k++) {
		l = 0;
		for (int j = m - 1; j >= 0; j--, l++)
			dest[l][k] = source[i][j];
	}
}

void rotate_all_90pos_clr(color **dest, color **source, int n, int m)
{
	int k, l;
	k = 0;
	for (int i = n - 1; i >= 0; i--, k++) {
		l = 0;
		for (int j = 0; j < m; j++, l++)
			dest[l][k] = source[i][j];
	}
}

void rotate_all_180_clr(color **dest, color **source, int n, int m)
{
	int k, l;
	k = 0;
	for (int i = n - 1; i >= 0; i--, k++) {
		l = 0;
		for (int j = m - 1 ; j >= 0; j--, l++)
			dest[k][l] = source[i][j];
	}
}
