#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

unsigned char **rotate_gray(unsigned char **a, pixel_t *s, int *height,
							int *width)
{
	int degree, n, m;
	scanf("%d", &degree);
	if (s->y2 - s->y1 == *height && s->x2 - s->x1 == *width) {
		switch (degree) {
		unsigned char **b;
		case 90: //same rotation
		case -270:
			n = *height, m = *width;
			b = alloc_matrix(m, n);
			rotate_all_90pos(b, a, n, m);
			free_matrix(a, n);
			a = alloc_matrix(m, n);
			copy_matrix(a, b, m, n);
			swap_int(width, height), swap_int(&s->x2, &s->y2);
			free_matrix(b, m);
			break;
		case -90: //same rotation
		case 270:
			n = *height, m = *width;
			b = alloc_matrix(m, n);
			rotate_all_90neg(b, a, n, m);
			free_matrix(a, n);
			a = alloc_matrix(m, n);
			copy_matrix(a, b, m, n);
			swap_int(width, height), swap_int(&s->x2, &s->y2);
			free_matrix(b, m);
			break;
		case 180: //same rotation
		case -180:
			b = alloc_matrix(*height, *width);
			copy_matrix(b, a, *height, *width);
			rotate_all_180(a, b, *height, *width);
			free_matrix(b, *height);
			break;
		case 360:
		case -360:
		case 0:
			break;
		default:
			printf("Unsupported rotation angle\n");
			return a;
	}
	printf("Rotated %d\n", degree);
	return a;
	} else {
		if (s->x2 - s->x1 != s->y2 - s->y1) { //check if is rectangle
			printf("Unsupported rotation angle\n");
			return a;
		} else if (degree > 360 || degree < -360) {
			printf("Unsupported rotation angle\n");
			return a;
		} else if (degree % 90 != 0) {
			printf("Unsupported rotation angle\n");
			return a;
		}
		n = s->y2 - s->y1;
		unsigned char **b = alloc_matrix(n, n);
		extract_submat(b, a, *s);
		switch (degree) {
		case 90:
		case -270:
			rotate90pos(b, n);
			break;
		case -90:
		case 270:
			rotate90neg(b, n);
			break;
		case 180:
		case -180:
			rotate180(b, n);
			break;
		}
		replace_original(a, b, *s);
		free_matrix(b, n);
		printf("Rotated %d\n", degree);
	}
	return a;
}

int read_binary_gray(char filename[], unsigned char **a, int n, int m, int poz)
{
	FILE *fin;
	int i;

	fin = fopen(filename, "rb");
	if (!fin) {
		printf("Eroare");
		return -1;
	}

	fseek(fin, poz, SEEK_SET);
	for (i = 0; i < n; i++)
		fread(a[i], sizeof(unsigned char), m, fin);
	fclose(fin);
	return 0;
}

unsigned char **crop_gray(unsigned char **a, pixel_t s, int *height, int *width)
{
	printf("Image cropped\n");

	//check if the whole image is selected
	if (s.x2 - s.x1 == *width && s.y2 - s.y1 == *height)
		return a;
	int n = s.y2 - s.y1;
	int m = s.x2 - s.x1;

	unsigned char **b = alloc_matrix(n, m);
	extract_submat(b, a, s);

	free_matrix(a, *height);
	a = realloc_matrix(s.y2 - s.y1, s.x2 - s.x1);

	int new_width = s.x2 - s.x1;
	int new_height = s.y2 - s.y1;
	copy_matrix(a, b, new_height, new_width);

	*height = new_height;
	*width = new_width;
	free_matrix(b, n);

	return a;
}

unsigned char **load_gray(char filename[], int type, int poz, int height,
						  int width)
{
	FILE *fin;
	fin = fopen(filename, "r");
	fseek(fin, poz, SEEK_SET);

	int n = height;
	int m = width;
	unsigned char **a;

	switch (type) {
		int i, j, poz;
	case 2: //ascii
		a = alloc_matrix(n, m);
		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				fscanf(fin, "%hhu", &a[i][j]);
		fclose(fin);
		break;
	case 5: //binary
		a = alloc_matrix(n, m);
		poz = (int)ftell(fin);
		fclose(fin);
		read_binary_gray(filename, a, n, m, poz + 1);
		break;
	}
	return a;
}

void save_gray(int type, int width, int height, int max_value,
			   unsigned char **a)
{
	char str[60];

	fgets(str, 60, stdin);

	char *token = strtok(str, "\n ");
	char *namefile = token;

	int nr_param = 0;
	while (token) {
		nr_param++;

		if (strcmp(token, "\n") == 0) {
			nr_param--;
			break;
		}
		token = strtok(NULL, " ");
	}

	if (nr_param == 2) { //save as ascii
		fflush(stdout);
		FILE *fout = fopen(namefile, "w");
		type = 2;
		fprintf(fout, "P%d\n%d %d\n%d\n", type, width, height, max_value);

		int n = height;
		int m = width;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				fprintf(fout, "%hhu ", a[i][j]);
			fprintf(fout, "\n");
		}
		fclose(fout);
	} else {
		FILE *fout = fopen(namefile, "wb+");
		type = 5;
		fprintf(fout, "P%d\n%d %d\n%d\n", type, width, height, max_value);

		int n = height;
		int m = width;

		for (int i = 0; i < n; i++)
			fwrite(a[i], sizeof(unsigned char), m, fout);
		fclose(fout);
		}
	printf("Saved %s\n", namefile);
}
