#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void free_matrix(unsigned char **a, int n)
{
	for (int i = 0; i < n; i++)
		free(a[i]);
	free(a);
}

void free_matrix_clr(color **a, int n)
{
	for (int i = 0; i < n; i++)
		free(a[i]);
	free(a);
}

unsigned char **realloc_matrix(int n, int m)
{
	unsigned char **tmp = (unsigned char **)malloc(n * sizeof
							(unsigned char *));

	if (!tmp)
		return NULL;

	for (int i = 0; i < n; i++) {
		tmp[i] = (unsigned char *)malloc(m * sizeof(int));
		if (!tmp[i])
			return NULL;
	}

	return tmp;
}

color **realloc_matrix_struct(int n, int m)
{
	color **tmp = (color **)malloc(n * sizeof
							(color *));

	if (!tmp)
		return NULL;

	for (int i = 0; i < n; i++) {
		tmp[i] = (color *)malloc(m * sizeof(int));
		if (!tmp[i])
			return NULL;
	}
	return tmp;
}

unsigned char **alloc_matrix(int n, int m)
{
	unsigned char **a = (unsigned char **)malloc(n * sizeof(unsigned char *));

	if (!a)
		return NULL;

	for (int i = 0; i < n; i++) {
		a[i] = (unsigned char *)malloc(m * sizeof(int));
		if (!a[i])
			return NULL;
	}
	return a;
}

color **alloc_struct_matrix(int n, int m)
{
	color **a = malloc(n * sizeof(color *));

	if (!a)
		return NULL;

	for (int i = 0; i < n; i++) {
		a[i] = malloc(m * sizeof(color));
		if (!a[i])
			return NULL;
	}
	return a;
}
