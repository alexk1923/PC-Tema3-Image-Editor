#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

void copy_color(color *dest, color *source)
{
	dest->r = source->r;
	dest->g = source->g;
	dest->b = source->b;
}

void read_struct(color *x, FILE *fin)
{
	fscanf(fin, "%hhu %hhu %hhu", &x->r, &x->g, &x->b);
}

void print_struct(color x)
{
	printf("%hhu %hhu %hhu\n", x.r, x.g, x.b);
}

void fprintf_struct(color x, FILE *fout)
{
	fprintf(fout, "%hhu %hhu %hhu ", x.r, x.g, x.b);
}

void copy_matrix_clr(color **dest, color **source, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dest[i][j] = source[i][j];
}

int read_binary_color(char filename[], color **a, int n, int m, int poz)
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
		fread(a[i], sizeof(color), m, fin);
	fclose(fin);
	return 0;
}

void change_rgb_gray(color *x)
{
	int new_value = x->r + x->g + x->b;
	x->r = new_value / 3;
	x->g = new_value / 3;
	x->b = new_value / 3;
}

void change_rgb_sepia(color *x, int max)
{
	double new_red = 0.393 * x->r + 0.769 * x->g + 0.189 * x->b;
	double new_green = 0.349 * x->r + 0.686 * x->g + 0.169 * x->b;
	double new_blue = 0.272 * x->r + 0.534 * x->g + 0.131 * x->b;

	if (new_red > max)
		new_red = max;
	if (new_green > max)
		new_green = max;
	if (new_blue > max)
		new_blue = max;

	//make approximation

	x->r = round(new_red);
	x->g = round(new_green);
	x->b = round(new_blue);
}

color **crop_color(color **a, pixel_t s, int *height, int *width)
{
	printf("Image cropped\n");
	if (s.x2 - s.x1 == *width && s.y2 - s.y1 == *height)
		return a;
	int n = s.y2 - s.y1;
	int m = s.x2 - s.x1;

	color **b = alloc_struct_matrix(n, m);

	extract_submat_clr(b, a, s);

	free_matrix_clr(a, *height);
	a = realloc_matrix_struct(s.y2 - s.y1, s.x2 - s.x1);

	int new_width = s.x2 - s.x1;
	int new_height = s.y2 - s.y1;
	copy_matrix_clr(a, b, new_height, new_width);

	*height = new_height;
	*width = new_width;
	free_matrix_clr(b, n);

	return a;
}

color **rotate_clr(color **a, pixel_t *s, int *height, int *width)
{
	int degree, n, m;
	scanf("%d", &degree);
	if (s->y2 - s->y1 == *height && s->x2 - s->x1 == *width) {
		switch (degree) {
		color **b;
		case 90: //same rotation
		case -270:
			n = *height, m = *width;
			b = alloc_struct_matrix(m, n);
			rotate_all_90pos_clr(b, a, n, m);
			free_matrix_clr(a, n);
			a = alloc_struct_matrix(m, n);
			copy_matrix_clr(a, b, m, n);
			swap_int(width, height);
			swap_int(&s->x2, &s->y2);
			free_matrix_clr(b, m);
			break;
		case -90: //same rotation
		case 270:
			n = *height, m = *width;
			b = alloc_struct_matrix(m, n);
			rotate_all_90neg_clr(b, a, n, m);
			free_matrix_clr(a, n);
			a = alloc_struct_matrix(m, n);
			copy_matrix_clr(a, b, m, n);
			swap_int(width, height);
			swap_int(&s->x2, &s->y2);
			free_matrix_clr(b, m);
			break;
		case 180: //same rotation
		case -180:
			b = alloc_struct_matrix(*height, *width);
			copy_matrix_clr(b, a, *height, *width);
			rotate_all_180_clr(a, b, *height, *width);
			free_matrix_clr(b, *height);
			break;
		case 360: //same rotation
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
		if (s->x2 - s->x1 != s->y2 - s->y1) {
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
			color **b = alloc_struct_matrix(n, n);
			extract_submat_clr(b, a, *s);
			switch (degree) {
			case 90:
			case -270:
				rotate90pos_clr(b, n);
				break;
			case -90:
			case 270:
				rotate90neg_clr(b, n);
				break;
			case 180:
			case -180:
				rotate180_clr(b, n);
				break;
			}
			replace_original_clr(a, b, *s);
			free_matrix_clr(b, n);
			printf("Rotated %d\n", degree);
	}
	return a;
}

void save_color(int type, int width, int height, int max_value, color **a)
{
	char str[60];

	fgets(str, 60, stdin);

	if (type == -1)
		return;

	char *token = strtok(str, " ");

	char *namefile = token;

	int nr_param = 0;
	while (token) {
		nr_param++;
		token = strtok(NULL, " ");
	}

	if (nr_param == 2) { //save as ascii
		FILE *fout = fopen(namefile, "w");
		type = 3;
		fprintf(fout, "P%d\n%d %d\n%d\n", type, width, height, max_value);

		int n = height;
		int m = width;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				fprintf_struct(a[i][j], fout);
		fclose(fout);
	} else {
		namefile[strlen(namefile) - 1] = 0;
		FILE *fout = fopen(namefile, "wb+");
		type = 6;
		fprintf(fout, "P%d\n%d %d\n%d\n", type, width, height, max_value);

		int n = height;
		int m = width;

		for (int i = 0; i < n; i++)
			fwrite(a[i], sizeof(color), m, fout);
		fclose(fout);
	}
	printf("Saved %s\n", namefile);
}

color **load_color(char filename[], int type, int poz, int height, int width)
{
	FILE *fin;
	fin = fopen(filename, "r");
	fseek(fin, poz, SEEK_SET);

	int n = height;
	int m = width;
	color **clr = NULL;
	switch (type) {
		int i, j, poz;
	case 3: //ascii
		clr = alloc_struct_matrix(n, m);
		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				read_struct(&clr[i][j], fin);
		fclose(fin);
		break;

	case 6: //binary
		clr = alloc_struct_matrix(n, m);
		poz = (int)ftell(fin);
		fclose(fin);
		read_binary_color(filename, clr, n, m, poz + 1);
		break;
	}
	return clr;
}

void grayscale(color **clr, pixel_t s)
{
	for (int i = s.y1; i < s.y2; i++)
		for (int j = s.x1; j < s.x2; j++)
			change_rgb_gray(&clr[i][j]);

	printf("Grayscale filter applied\n");
}

void sepia(color **clr, pixel_t s, int max)
{
	for (int i = s.y1; i < s.y2; i++)
		for (int j = s.x1; j < s.x2; j++)
			change_rgb_sepia(&clr[i][j], max);

	printf("Sepia filter applied\n");
}
