#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

void swap_int(int *a, int *b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void selection(pixel_t *sel, int height, int width, int type)
{
	char *x2_s, *y1_s, *y2_s;

	char str[50];
	fgets(str, 30, stdin);

	char numbers[11] = "-0123456789"; //valid first character

	char *token = strtok(str, " ");
	char *x1_s = token;

	if (strstr(x1_s, "ALL")) {
		if (type == -1) {
			printf("No image loaded\n");
			return;
	}
	//update selection
	sel->x1 = 0;
	sel->x2 = width;
	sel->y1 = 0;
	sel->y2 = height;
	printf("Selected ALL\n");
	} else {
		if (type == -1) {
			printf("No image loaded\n");
			return;
	}

	int nr_param = 0;
	while (token) {
		nr_param++;
		if (nr_param == 2)
			y1_s = token;
		if (nr_param == 3)
			x2_s = token;
		if (nr_param == 4)
			y2_s = token;
		if (!strchr(numbers, token[0])) {
			printf("Invalid command\n");
			return;
		}
		token = strtok(NULL, " ");
	}

	//check valid nr. of parameters
	if (nr_param < 4) {
		printf("Invalid command\n");
		return;
	}

	int x1 = atoi(x1_s);
	int x2 = atoi(x2_s);
	int y1 = atoi(y1_s);
	int y2 = atoi(y2_s);

	//check order of the parameters
	if (x1 > x2)
		swap_int(&x1, &x2);
	if (y1 > y2)
		swap_int(&y1, &y2);
	if (x1 < 0 || x2 > width || y1 < 0 || y2 > height || x2 - x1 == 0 ||
		y2 - y1 == 0) {
		printf("Invalid set of coordinates\n");
		return;
	}

	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);

	sel->x1 = x1;
	sel->y1 = y1;
	sel->x2 = x2;
	sel->y2 = y2;
	}
}

int read_info(char filename[], pixel_t *sel, int *height, int *width,
			  int *max_value, int *poz)
{
	FILE *fin;
	fin = fopen(filename, "r");

	if (!fin) {
		printf("Failed to load %s\n", filename);

	fin = NULL;
	return -1;
	} else {
		printf("Loaded %s\n", filename);
	}

	// read photo's information

	char c;
	int type;
	fscanf(fin, "%c%d", &c, &type);

	fscanf(fin, "%d%d", width, height);
	sel->x1 = 0;
	sel->x2 = *width;
	sel->y1 = 0;
	sel->y2 = *height;
	fscanf(fin, "%d", max_value);

	*poz = ftell(fin);

	fclose(fin);
	return type;
}

void check_type(int type)
{
	if (type == -1)
		printf("No image loaded\n");
}

void exit_free(unsigned char **a, color **clr, int type, int height)
{
	if (type == -1)
		printf("No image loaded\n");
	if (a)
		free_matrix(a, height);
	if (clr)
		free_matrix_clr(clr, height);
}

int main(void)
{
	int height, width, type = -1, max_value, poz, junk, old_height;
	char command[20], filename[20], junkstr[60];
	unsigned char **a = NULL;
	color **clr = NULL;
	pixel_t sel;
	scanf("%s", command);
	while (strcmp("EXIT", command) != 0) {
		if (strcmp("LOAD", command) == 0) {
			scanf("%s", filename);
			old_height = height;
			type = read_info(filename, &sel, &height, &width, &max_value, &poz);
			if (type == 2 || type == 5) { // grayscale img
				if (clr) {
					free_matrix_clr(clr, old_height);
					clr = NULL;
				}
				if (a) {
					free_matrix(a, old_height);
					a = NULL;
				}
				a = load_gray(filename, type, poz, height, width);
			} else if (type == 3 || type == 6) { //color img
				if (a) {
					free_matrix(a, old_height);
					a = NULL;
				}
				if (clr) {
					free_matrix_clr(clr, old_height);
					clr = NULL;
				}
				clr = load_color(filename, type, poz, height, width);
			}
		} else if (strcmp("SELECT", command) == 0) {
			selection(&sel, height, width, type);
		} else if (strcmp("ROTATE", command) == 0) {
			if (type == 2 || type == 5) {
				a = rotate_gray(a, &sel, &height, &width);
			} else if (type == 3 || type == 6) {
				clr = rotate_clr(clr, &sel, &height, &width);
			} else if (type == -1) {
				scanf("%d", &junk);
				printf("No image loaded\n");
				}
			} else if (strcmp("CROP", command) == 0) {
				if (type == 2 || type == 5)
					a = crop_gray(a, sel, &height, &width);
				else if (type == 3 || type == 6)
					clr = crop_color(clr, sel, &height, &width);
				else if (type == -1)
					printf("No image loaded\n");
				} else if (strcmp("GRAYSCALE", command) == 0) {
					check_type(type);
					if (type == 2 || type == 5)
						printf("Grayscale filter not available\n");
					else if (type == 3 || type == 6)
						grayscale(clr, sel);
				} else if (strcmp("SEPIA", command) == 0) {
					check_type(type);
					if (type == 2 || type == 5)
						printf("Sepia filter not available\n");
					else if (type == 3 || type == 6)
						sepia(clr, sel, max_value);
				} else if (strcmp("SAVE", command) == 0) {
					if (type == 2 || type == 5) {
						save_gray(type, width, height, max_value, a);
					} else if (type == 3 || type == 6) {
						save_color(type, width, height, max_value, clr);
					} else if (type == -1) {
						fgets(junkstr, 60, stdin);
						printf("No image loaded\n");
					}
				} else {
					printf("Invalid command\n");
					fgets(junkstr, 60, stdin);
				}
		scanf("%s", command);
	}
	exit_free(a, clr, type, height); //free ponies
	return 0;
}
