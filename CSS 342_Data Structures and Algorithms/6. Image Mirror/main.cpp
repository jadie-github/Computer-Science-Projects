// Jessica Nguyen
// CSS342, Project 1
// Purpose: This program will read in a gif image ("test1.gif"), then
//          creates a modified image of the input (in terms of RGB levels), flips the image 
//			such that the left side and the right side of the image file are reversed,
//          and outputs the result image file to "output.gif". The program also outputs 
//			the number of pixels that have a different value in red, green, or blue between
//			the modified+flipped image versus the newly read-in image of the same file.

#include "ImageLib.h"
#include <iostream>

// forward declarations
void modify(image&);
void flip(image&);
void isDifferent(image&, image&);

//constants
const int MAX_RGB_VALUE = 255;
const int MIN_RGB_VALUE = 0;


// main()
// Precondition:   test.gif exists and is a valid GIF image
// Postconditions: output.gif will be written and it will contain 
//				   a modified (in RGB levels) and flipped image  
//				   of the original image in test1.gif
int main() {
	// Read test image from file
	image input = ReadGIF("test1.gif");
	if (input.rows == 0) {
		cout << "Unable to open file: test1.gif" << endl;
		return -1;
	}

	// Modifies image in its RGB values
	modify(input);

	// Flips the modified image left to right
	flip(input);

	//Writes the resulting image to the output
	WriteGIF("output.gif", input);

	// Reads output.gif back into a new image variable for comparison
	image newImage = ReadGIF("output.gif");

	//compares each pixel to see if there are differences and
	//calculates the number of pixels that have a different value in red, green, or blue
	isDifferent(input, newImage);

	/*DeallocateImage(input);
	DeallocateImage(newImage);*/
}


// modify()
// Preconditions: the input image (in) has in.rows * in.cols pixels allocated
// Postconditions: the input image is modified such that some of the pixel color components
//				   are changed: the blue component of the pixel are subtracted
//				   by (row mod 7), and the red component of the pixel are added by
//				   (column mod 9), and the green component is kept the same.
//				   If there are overflows (> 255 bytes), the byte value of the pixel is set to 255.
//				   If there are underflows (< 0 byte), the byte value of the pixel is set to 0.
void modify(image& in) {
	//traverses every row and column of the image
	for (int row = 0; row < in.rows; row++) {
		for (int col = 0; col < in.cols; col++) {
			if (in.pixels[row][col].blue - row % 7 > MAX_RGB_VALUE) { //overflow blue
				in.pixels[row][col].blue = MAX_RGB_VALUE;
			}
			else if (in.pixels[row][col].blue - row % 7 < MIN_RGB_VALUE) { // underflow blue
				in.pixels[row][col].blue = MIN_RGB_VALUE;
			}
			else if (in.pixels[row][col].red + col % 9 > MAX_RGB_VALUE) { //overflow red
				in.pixels[row][col].red = MAX_RGB_VALUE;
			}
			else if (in.pixels[row][col].red + col % 9 < MIN_RGB_VALUE) { // underflow red
				in.pixels[row][col].red = MIN_RGB_VALUE;
			}
			else { // not overflow or underflow

				in.pixels[row][col].blue -= row % 7;

				in.pixels[row][col].red += col % 9;
			}
		}
	}
}

//flip()
//preconditions: the input image (in) has in.rows * in.cols pixels allocated
//postconditions: the input image file is mirrored such that the left side 
//				  and the right side pixels are reversed.
//parameters: a reference to an image file created in main()
void flip(image& in) {
	for (int currRow = 0; currRow < in.rows; currRow++) { //go through every row of image
		int start = 0;
		int end = in.cols-1; //CORECTION: -1 TO FIX OFF BY ONE

		//question c) switches left side and right side pixels so the image input file is mirrored
		while (start < end) {
			pixel temp = in.pixels[currRow][start];
			in.pixels[currRow][start] = in.pixels[currRow][end];
			in.pixels[currRow][end] = temp;
			start++;
			end--;
		}
	}
}

//isDifferent()
//preconditions: the input images (input, newImage) have all rows and columns pixels allocated,
//				 and the two image input files must have the same size in terms of rows and columns.
//postconditions: the number of pixels that have a different values in either red, green, or blue 
//				  is output to the console 
//parameters: a reference to an image file created in main() and another reference to a different image file
//			  read in from main() for comparison
void isDifferent(image& input, image& newImage) {
	//fail-safe check. Invalid if user passes different-sized images
	if ((input.cols != newImage.cols) || (input.rows != newImage.rows)) {
		cout << "The two image files don't match in sizes. Please try again." << endl;
	}
	else {

		//counts how many pixels that have a different value in red, green or blue.
		int count = 0;
		for (int row = 0; row < newImage.rows; row++) {
			for (int col = 0; col < newImage.cols; col++) {
				if ((input.pixels[row][col].red != newImage.pixels[row][col].red) ||
					(input.pixels[row][col].blue != newImage.pixels[row][col].blue) ||
					(input.pixels[row][col].green != newImage.pixels[row][col].green)) {
					count++;
				}
			}
		}

		//question f) output if there are any differences between the pixel values of the 2 images
		if (count > 0) {
			cout << "Yes, there are pixel differences between the two images." << endl;
		}
		else {
			cout << "No, there aren't any pixel differences between the two images." << endl;

		}

		//question g) outputs number of pixels that have a different values in red, green, or blue
		cout << "There are " << count << " differences between the RGB values of these two images." << endl;
	}
}