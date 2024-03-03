/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *res = (Color *)malloc(sizeof(Color));
	if (res == NULL){
		printf("Error Allocating");
	}
	Color color = image->image[row][col];
	uint8_t B = color.B;
	uint8_t b = B & 0x01;
	if (b == 1){
		res->R = 255;
        res->G = 255;
        res->B = 255;
	}
	else{
		res->R = 0;
        res->G = 0;
        res->B = 0;
	}
	return res;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
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
			Color *tmp = evaluateOnePixel(image, i, j);
			res->image[i][j] = *tmp;
			free(tmp);
		}
	}

	return res;
}

void processCLI(int argc, char **argv, char **filename) 
{
	if (argc != 2) {
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		exit(-1);
	}
	*filename = argv[1];
}
/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	Image *image;
	char *filename;
	processCLI(argc,argv,&filename);
	image = readData(filename);
	if (image == NULL)
		return -1;
	Image *hiddenite = steganography(image);
	if (hiddenite == NULL)
		return -1;
	writeData(hiddenite);
	freeImage(image);
	freeImage(hiddenite);
}
