#pragma once

typedef struct{
	int x1, x2, y1, y2;
} pixel_t;

typedef struct{
	unsigned char r, g, b;
} color;

void free_matrix(unsigned char **a, int n);
void free_matrix_clr(color **a, int n);
void free_image(unsigned char **a, color **clr, int old_height);

unsigned char **alloc_matrix(int n, int m);

color **alloc_struct_matrix(int n, int m);

unsigned char **realloc_matrix(int n, int m);
color **realloc_matrix_struct(int n, int m);

unsigned char **rotate_gray(unsigned char **a, pixel_t *s, int *height,
							int *width);
int read_binary_gray(char filename[], unsigned char **a, int n, int m, int poz);
unsigned char **crop_gray(unsigned char **a, pixel_t s, int *height,
						  int *width);
unsigned char **load_gray(char filename[], int type, int poz, int height,
						  int width);
void save_gray(int type, int width, int height, int max_value,
			   unsigned char **a);

void swap_int(int *a, int *b);
void swap_clr(color *a, color *b);
void transpose_clr(color **a, int n);
void reversecolnegative_clr(color **a, int n);
void reversecolnpositive_clr(color **a, int n);
void rotate90pos_clr(color **a, int n);
void rotate90neg_clr(color **a, int n);
void rotate180_clr(color **a, int n);
void extract_submat_clr(color **dest, color **source, pixel_t s);
void replace_original_clr(color **dest, color **source, pixel_t s);
void rotate_all_90neg_clr(color **dest, color **source, int n, int m);
void rotate_all_90pos_clr(color **dest, color **source, int n, int m);
void rotate_all_180_clr(color **dest, color **source, int n, int m);

void swap_uc(unsigned char *a, unsigned char *b);
void transpose(unsigned char **a, int n);
void reversecolnegative(unsigned char **a, int n);
void reversecolnpositive(unsigned char **a, int n);
void rotate90pos(unsigned char **a, int n);
void rotate90neg(unsigned char **a, int n);
void rotate180(unsigned char **a, int n);
void extract_submat(unsigned char **dest, unsigned char **source, pixel_t s);
void replace_original(unsigned char **dest, unsigned char **source, pixel_t s);
void copy_matrix(unsigned char **dest, unsigned char **source, int n, int m);
void rotate_all_90neg(unsigned char **dest, unsigned char **source,
					  int n, int m);
void rotate_all_90pos(unsigned char **dest, unsigned char **source,
					  int n, int m);
void rotate_all_180(unsigned char **dest, unsigned char **source, int n, int m);

void grayscale(color **clr, pixel_t s);
void sepia(color **clr, pixel_t s, int max);
color **load_color(char filename[], int type, int poz, int height, int width);
void copy_color(color *dest, color *source);
void read_struct(color *x, FILE *fin);
void print_struct(color x);
void fprintf_struct(color x, FILE *fout);
void copy_matrix_clr(color **dest, color **source, int n, int m);
int read_binary_color(char filename[], color **a, int n, int m, int poz);
void change_rgb_gray(color *x);
void change_rgb_sepia(color *x, int max);
color **crop_color(color **a, pixel_t s, int *height, int *width);
color **rotate_clr(color **a, pixel_t *s, int *height, int *width);
void save_color(int type, int width, int height, int max_value, color **a);
