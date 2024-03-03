/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

const int alive[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0}, dead[9] = {0, 0, 0, 1, 0, 0, 0, 0, 0};

unsigned get_bit(uint8_t Byte, int n){
	return (Byte >> n) & 1;
}

void set_bit(uint8_t *Byte, int n, int value){
	if(value){
        *Byte |= 1 << n;
    }
    else{
        *Byte &= ~(1 << n);
    }
}

int real_row(int row, int add, int rows){
	int tmp = row + add;
	while (tmp < 0)
		tmp += rows;
	return tmp % rows;
}

int real_col(int col, int add, int cols){
	int tmp = col + add;
    while (tmp < 0)
        tmp += cols;
    return tmp % cols;
}

void next_R(uint8_t *R, Image *image, int row, int col){
	for (int i = 0; i < 8; i++){
		int neighbors = 0;
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				if (dx == 0 && dy == 0) continue;
				int newRow = real_row(row, dy, image->rows);
				int newCol = real_col(col, dx, image->cols);
				if (get_bit(image->image[newRow][newCol].R, i) == 1)
					neighbors++;
			}
		}
		if (get_bit(*R, i) == 1)
			set_bit(R, i, alive[neighbors]);
		else
			set_bit(R, i, dead[neighbors]);
	}
}

void next_G(uint8_t *G, Image *image, int row, int col) {
    for (int i = 0; i < 8; i++) {
        int neighbors = 0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int newRow = real_row(row, dy, image->rows);
                int newCol = real_col(col, dx, image->cols);
                if (get_bit(image->image[newRow][newCol].G, i) == 1)
                    neighbors++;
            }
        }
        if (get_bit(*G, i) == 1)
            set_bit(G, i, alive[neighbors]);
        else
            set_bit(G, i, dead[neighbors]);
    }
}

void next_B(uint8_t *B, Image *image, int row, int col) {
    for (int i = 0; i < 8; i++) {
        int neighbors = 0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int newRow = real_row(row, dy, image->rows);
                int newCol = real_col(col, dx, image->cols);
                if (get_bit(image->image[newRow][newCol].B, i) == 1)
                    neighbors++;
            }
        }
        if (get_bit(*B, i) == 1)
            set_bit(B, i, alive[neighbors]);
        else
            set_bit(B, i, dead[neighbors]);
    }
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color *res = (Color *)malloc(sizeof(Color));
	if (res == NULL){
		printf("Error Allocating");
	}
	uint8_t *R = &(image->image[row][col].R), *G = &(image->image[row][col].G), *B = &(image->image[row][col].B);
	next_R(R, image, row, col);
	next_G(G, image, row, col);
	next_B(B, image, row, col);
	res->R = *R;
	res->G = *G;
	res->B = *B;
	return res;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *res = (Image *)malloc(sizeof(Image));
	if (res == NULL){
		printf("Error allocating memory\n");
        return NULL;
	}

	res->cols = image->cols;
	res->rows = image->rows;
	res->image = (Color**)calloc(res->rows, sizeof(Color*));
	if (res->image == NULL){
		printf("Error allocating");
		return NULL;
	}

	for (int i = 0; i < res->rows; ++i){
		res->image[i] = (Color*)calloc(res->cols, sizeof(Color));
		if (res->image[i] == NULL){
			printf("Error allocating");
            return NULL;
		}
		for (int j = 0; j < res->cols; ++j){
			Color *tmp = evaluateOneCell(image, i, j, rule);
			res->image[i][j] = *tmp;
			free(tmp);
		}
	}

	return res;
}

void processCLI(int argc, char **argv, char **filename, uint32_t *rule) 
{
	if (argc != 3) {
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
		exit(-1);
	}
	*filename = argv[1];
	char *endPtr;
	unsigned long hexValue = strtoul(argv[2], &endPtr, 16);
	*rule = (uint32_t)hexValue;
	if (!(*rule <= 0x3FFFF && *rule >= 0x00000)){
		printf("rule is out of range\n");
		exit(-1);
	}
}
/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	Image *image;
	char *filename;
	uint32_t rule;
	processCLI(argc,argv,&filename, &rule);
	image = readData(filename);
	if (image == NULL)
		return -1;
	Image *newimage = life(image, rule);
	if (newimage == NULL)
		return -1;
	writeData(newimage);
	freeImage(image);
	freeImage(newimage);
}
