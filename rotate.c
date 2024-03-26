#include <stdio.h>
#include "functions.h"

void swap_uc(unsigned char *a, unsigned char *b)
{
	unsigned char aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void transpose(unsigned char **a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			swap_uc(&a[i][j], &a[j][i]);
}

void reversecolnegative(unsigned char **a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0, k = n - 1; j < k; j++, k--)
			swap_uc(&a[j][i], &a[k][i]);
}

void reversecolnpositive(unsigned char **a, int n)
{
	for (int i = 0, k = n - 1; i < k; i++, k--)
		for (int j = 0; j < n; j++)
			swap_uc(&a[j][i], &a[j][k]);
}

void rotate90pos(unsigned char **a, int n)
{
	transpose(a, n);
	reversecolnpositive(a, n);
}

void rotate90neg(unsigned char **a, int n)
{
	transpose(a, n);
	reversecolnegative(a, n);
}

void rotate180(unsigned char **a, int n)
{
	for (int i = 0 ; i < n / 2; i++)
		for (int j = 0; j < n; j++)
			swap_uc(&a[i][j], &a[n - 1 - i][n - 1 - j]);

	if (n % 2 != 0)
		for (int j = 0 ; j < n / 2;  j++)
			swap_uc(&a[n / 2][j], &a[n / 2][n - j - 1]);
}

void extract_submat(unsigned char **dest, unsigned char **source, pixel_t s)
{
	int k = 0;
	for (int i = s.y1; i < s.y2; i++, k++) {
		int l = 0;
		for (int j = s.x1; j < s.x2; j++, l++)
			dest[k][l] = source[i][j];
	}
}

void replace_original(unsigned char **dest, unsigned char **source, pixel_t s)
{
	int k = 0;
	for (int i = s.y1; i < s.y2; i++, k++) {
		int l = 0;
		for (int j = s.x1; j < s.x2; j++, l++)
			dest[i][j] = source[k][l];
	}
}

void copy_matrix(unsigned char **dest, unsigned char **source, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dest[i][j] = source[i][j];
}

void rotate_all_90neg(unsigned char **dest, unsigned char **source, int n,
					  int m)
{
	int k, l;
	k = 0;
	for (int i = 0; i < n; i++, k++) {
		l = 0;
		for (int j = m - 1; j >= 0; j--, l++)
			dest[l][k] = source[i][j];
	}
}

void rotate_all_90pos(unsigned char **dest, unsigned char **source, int n,
					  int m)
{
	int k, l;
	k = 0;
	for (int i = n - 1; i >= 0; i--, k++) {
		l = 0;
		for (int j = 0; j < m; j++, l++)
			dest[l][k] = source[i][j];
	}
}

void rotate_all_180(unsigned char **dest, unsigned char **source, int n, int m)
{
	int k, l;
	k = 0;
	for (int i = n - 1; i >= 0; i--, k++) {
		l = 0;
		for (int j = m - 1 ; j >= 0; j--, l++)
			dest[k][l] = source[i][j];
	}
}
