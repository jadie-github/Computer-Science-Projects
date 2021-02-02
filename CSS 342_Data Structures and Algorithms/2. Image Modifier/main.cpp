//Jessica Nguyen
//CSS342, Program2
//Purpose: This program will read in a gif image ("test2.gif"), then
//          creates a modified image of the input (in terms of RGB levels), flips the image 
//			such that the left side and the right side of the image file are reversed,
//          and outputs the result image file to "output.gif". The program also outputs 
//			the number of pixels that have a different value in red, green, or blue between
//			the modified+flipped image versus the newly read-in image of the same file.

#include "Image.h"

//forward declarations
void modify(Image&);
void compare(Image&, Image&);

/*
main()
Precondition:   test2.gif exists and is a valid GIF image
Postconditions: output.gif will be written and it will contain 
				a modified (in RGB levels) and flipped image  
				of the original image in test2.gif
*/
int main() {
	//reads image
	Image test("test2.gif");

	//outputs size to console
	cout << test << endl;

	//mirrors image and store into an Image variable 
	Image mirrored = test.mirrorImage();

	//modifies the RGB values of mirrored
	modify(mirrored); 

	//writes mirrored out into the output
	mirrored.outputImage("output.gif");

	//reads mirrored back in from the output file
	Image newImage("output.gif");
	
	//compares the original mirrored versus the newly read-in mirrored images
	compare(mirrored, newImage);
}

/*
modify()
Preconditions: the input image has rows and pixels allocated.
Postconditions: the input image is modified such that some of the pixel color components
				are changed: the blue component of the pixel are subtracted
				by (row mod 7), and the red component of the pixel are added by
			    (column mod 9), and the green component is kept the same.
				If there are overflows (> 255 bytes), the byte value of the pixel is set to 255.
				If there are underflows (< 0 byte), the byte value of the pixel is set to 0.
*/
void modify(Image& image) {
	for (int row = 0; row < image.getRow(); row++) {
		for (int col = 0; col < image.getColumn(); col++) {
			//goes through each pixel in the image and uses mutator methods to change RGB values 
			image.changeBlue(image.getPixel(row, col), image.getPixel(row,col).blue - row % 7);
			image.changeRed(image.getPixel(row, col), image.getPixel(row, col).red + col % 9);
		}
	}
}


/*
compare()
preconditions: the input images (original, modified) have all rows and columns pixels allocated,
			   and the two image input files must have the same size in terms of rows and columns.
postconditions: the number of pixels that have a different values in either red, green, or blue 
				is output to the console 
parameters: a reference to an image file created in main() and another reference to a different image file
			read in from main() for comparison
*/
void compare(Image& original, Image& modified) {
	if (original == modified) { 
		//uses operator== overloads to compare
		cout << "There are no differences between the two images." << endl;
	} else {
		//counts how many pixels that have a different value in red, green or blue.
		int count = 0;

		for (int row = 0; row < original.getRow(); row++) {
			for (int col = 0; col < original.getColumn(); col++) {
				if (original.getRed(row, col) != modified.getRed(row, col) ||
					original.getBlue(row, col) != modified.getBlue(row, col) ||
					original.getGreen(row, col) != modified.getGreen(row, col)) {
					count++;
				}
			}
		}
		// outputs number of pixels that have a different values in red, green, or blue
		cout << "There are " << count << " differences between the RGB pixel values between the two images." << endl;
	}
}
