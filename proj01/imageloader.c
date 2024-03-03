/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *in = fopen(filename, "r");
	if (in == NULL){
		printf("Error opening\n");
		return NULL;
	}

	Image *res = (Image *)malloc(sizeof(Image));
	if (res == NULL){
		printf("Error allocating memory\n");
        return NULL;
	}

	char P3[3];
	int scale;
	fscanf(in, "%s", P3);
	fscanf(in, "%d %d", &res->cols, &res->rows);
	fscanf(in, "%d", &scale);

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
	}
	for (int i = 0; i < res->rows; ++i){
        for (int j = 0; j < res->cols; ++j){
            fscanf(in, "%hhu %hhu %hhu ", &(res->image[i][j].R), &(res->image[i][j].G), &(res->image[i][j].B));
        }
    }
	return res;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n%d %d\n255\n", image->cols, image->rows);

	for (int i = 0; i < image->rows; ++i){
		int j;
		for (j = 0; j < image->cols - 1; ++j)
		{
			printf("%3hhu %3hhu %3hhu   ", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
		}
		printf("%3hhu %3hhu %3hhu\n", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for (int i = 0; i < image->rows; ++i)
		free(image->image[i]);
	free(image->image);
	free(image);
}
