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
	Color* decoded_color = (Color*) malloc(sizeof(Color));
	Color* encoded_color = &(image->image[row][col]);
	if (encoded_color->B % 2 == 0)
		decoded_color->R = decoded_color->G = decoded_color->B = 0;
	else 
		decoded_color->R = decoded_color->G = decoded_color->B = 255;
	return decoded_color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image* new_image = (Image*) malloc(sizeof(Image));
	new_image->cols = image->cols;
	new_image->rows = image->rows;
	new_image->image = (Color**) malloc(new_image->rows * sizeof(Color*));
	for (size_t i = 0; i < new_image->rows; ++i)
		new_image->image[i] = (Color*) malloc(new_image->cols * sizeof(Color));

	for (int i = 0; i < new_image->rows; ++i)
		for(int j = 0; j < new_image->cols; ++j)
			new_image->image[i][j] = *(evaluateOnePixel(image, i, j));
	return new_image;
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
	if (argc != 2){
		printf("Usage: %s <colorfile>\n", argv[0]);
		return 1;
	}

	Image* img = readData(argv[1]);
	if(img == NULL) {
		printf("Malloc error or file %s is of wrong format", argv[1]);
		return 1;
	}

	Image* new_img = steganography(img);
	writeData(new_img);
	freeImage(img);
	freeImage(new_img);
	return 0;
}
