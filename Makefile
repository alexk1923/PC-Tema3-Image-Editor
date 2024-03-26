#Kullman Alexandru, 313CA

build: make
all: image_editor

make : image_editor.c dynamic_allocation.c color.c rotate.c rotate_color.c gray.c
	gcc image_editor.c rotate_color.c rotate.c dynamic_allocation.c gray.c color.c -lm -g -Wextra -Wall -o image_editor
	

clean:
	rm -rf all
