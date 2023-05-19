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
	//open file
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("fail to open %s\n",filename);
		return NULL;
	}
    char mode[20];
    Image* image_node = (Image*) malloc(sizeof(Image));
    uint32_t tmp;
    fscanf(fp, "%s %u %u %u", mode, &image_node->rows, &image_node->cols, &tmp);
    if (mode[0] != 'P' && mode[1] != 3) {
        printf("wrong file form\n");
        return NULL;
    }
	//allocate memory for image
	image_node->image = (Color**) malloc(image_node->rows * sizeof(Color*));
	for (size_t i = 0; i < image_node->rows; i++)
		image_node->image[i] = (Color*) malloc(image_node->cols * sizeof(Color));

	//read in colors
	Color* cp;
	for (size_t i = 0; i < image_node->rows; i++)
		for(size_t j = 0; j < image_node->cols; j++) {
			cp = &image_node->image[i][j];
			fscanf(fp, "%hhd %hhd %hhd", &cp->R, &cp->G, &cp->B);
		}
	
	//close file
	fclose(fp);

	return image_node;
}

// fixed length print
void print(uint8_t a) 
{
	if (a >= 0 && a <=9) printf("  %hhu" , a);
	else if(a >= 10 && a <= 99) printf(" %hhu", a);
	else if(a >= 100 && a <= 255) printf("%hhu", a);
} 

//print Color
void print_color(Color* cp) 
{
	for(int k = 0; k < 3; ++k){
		switch (k)
		{
		case 0:
			print(cp->R);
			printf(" ");
			break;
		case 1:
			print(cp->G);
			printf(" ");
			break;
		case 2:
			print(cp->B);
			break;
		}
	}
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	Color* cp;
	printf("P3\n%u %u\n255\n", image->rows, image->cols);

	//print image
	for(int i = 0; i < image->rows; ++i) {
		for (int j = 0; j < image->cols - 1; ++j) {
			cp = &image->image[i][j];
			print_color(cp);
			printf("   ");
		}
		cp = &image->image[i][image->cols - 1];
		print_color(cp);
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	for(int i = 0; i < image->rows; ++i) {
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}