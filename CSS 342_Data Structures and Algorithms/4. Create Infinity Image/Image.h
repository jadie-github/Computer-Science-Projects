//Jessica Nguyen
//CSS342, Project2
//This file describes the interface to the Image class. 
//Functionality includes: 
// constructor for image files using filename or size;
// constructor, destructor, operator= methods for dynamic memory;
// accessors for rows and columns in the image;
// accessors and mutators for individual image pixels and RGB bytes;
// output to file;
// overload operators: ==, !=, >, <, <<;
// and mirror the image.

#pragma once

#ifndef IMAGE_H
#define IMAGE_H
#include "ImageLib.h"

#include <iostream>
using namespace std;

class Image {

private:
	//private field: image that represents image object 
	image pic;

// Function prototypes: 
public:

	//constructor methods:
	/*
	  Image:
	  Preconditions: filename refers to a file that stores a GIF image.
	  Postconditions: creates an Image object using the image file contained in input string parameter.
 					  If the load is unsuccessful, image is deallocated.
	 */
	Image(string); //creates an image by reading in from the input file

	/*
	 Image:
	 Preconditions: int inputs for rows and columns must be >= 0.
	 Postconditions: creates a blank, black Image object using the input parameters that represent sizes for rows and columns.
 					 If input parameters are invalid (<=0), an error message is displayed.
					 If input parameters are not specified, the default size is 360 x 360.
	*/
	Image(int = 360, int = 360); 


	//dynamic memory methods

	/*
	 Image copy constructor
	 Preconditions: reference to the Image object to be copied must exist.
	 Postconditions: if sufficient memory is available, a copy of the input file
					 is returned using newly allocated memory.
					 Otherwise, the returned image has:
		   			 rows = 0, cols =0 , pixels = nullptr.
	*/
	Image(const Image&);

	/*
	 Image destructor
	 Preconditions: Image object must exist and is not null
	 Postconditions: the memory allocated to the pixels of input Image object has
		 			 been deallocated.  Also, the image values are set to:
					 rows = 0, cols = 0, pixels = nullptr.
	*/
	~Image();

	/*
	 operator=
	 Preconditions: Image object must exist and is not null
	 Postconditions: the calling Image object is assigned to the current Image object
					 and both objects share the same memory address to the Image object.
	*/
	const Image& operator=(const Image&);

	//accessor methods

	/*
	 getRow:
	 Preconditions: current Image object must exist and is not null
	 Postconditions: the int number of rows this Image object has is returned 
	*/
	int getRow() const;

	/*
	 getColumn:
	 Preconditions: current Image object must exist and is not null
	 Postconditions: the int number of columns this Image object has is returned

	*/
	int getColumn() const;

	/*
	 getPixel:
	 Preconditions: current Image object must exist and is not null; 
					the two int parameters representing the location (row, column) of the pixel
					are within bounds and valid.
	 Postconditions: the reference to the pixel object specified within this Image object is returned.
	*/
	pixel& getPixel(int, int) const;

	/*
	 getRed:
	 Preconditions: current Image object must exist and is not null; 
					the two int parameters representing the location (row, column) of the pixel
					are within bounds and valid.
	 Postconditions: the red byte value of the pixel being specified by row and column is returned.
	*/
	byte getRed(int, int) const;

	/*

	 getGreen:
	 Preconditions: current Image object must exist and is not null; 
					the two int parameters representing the location (row, column) of the pixel
					are within bounds and valid.
	 Postconditions: the green byte value of the pixel being specified by row and column is returned.
	*/
	byte getGreen(int, int) const;

	/*
	 getBlue:
	 Preconditions: current Image object must exist and is not null;
					the two int parameters representing the location (row, column) of the pixel
					are within bounds and valid.
	 Postconditions: the blue byte value of the pixel being specified by row and column is returned.
	*/
	byte getBlue(int, int) const;

	//mutator methods
	/*
	 changeRed:
	 Preconditions: current Image object must exist and is not null;
					the reference to the pixel input is valid; 
					the byte input value must be between 0 and 255
	 Postconditions: the red byte value of the referenced pixel is changed to the specified input value
					If there are overflows (> 255 bytes), the byte value of the pixel is set to 255.
				    If there are underflows (< 0 byte), the byte value of the pixel is set to 0.
	*/
	void changeRed(pixel&, int);

	/*
	 changeGreen:
	 Preconditions: current Image object must exist and is not null;
					the reference to the pixel input is valid; 
					the byte input value must be between 0 and 255
	 Postconditions: the green byte value of the referenced pixel is changed to the specified input value
					If there are overflows (> 255 bytes), the byte value of the pixel is set to 255.
				    If there are underflows (< 0 byte), the byte value of the pixel is set to 0.
	*/
	void changeGreen(pixel&, int);

	/*
	 changeBlue
	 Preconditions: current Image object must exist and is not null;
					the reference to the pixel input is valid;
					the byte input value must be between 0 and 255
	 Postconditions: the blue byte value of the referenced pixel is changed to the specified input value
					If there are overflows (> 255 bytes), the byte value of the pixel is set to 255.
					If there are underflows (< 0 byte), the byte value of the pixel is set to 0.
	*/
	void changeBlue(pixel&, int);

	/*
	 outputImage:
	 Preconditions: input string for file name is valid file name to store a GIF image.
					current Image object must exist and is not null;
	 Postconditions: inputImage is saved as a GIF image at the location
				     specified by filename.
	*/
	void outputImage(string) const;

	//operator methods
	/*
	 operator==
	 Preconditions: input parameter is an Image object type
	 Postconditions: if the two Image objects (this and input) match in terms of 
					 every single RGB levels in each pixel, method returns true.
					 If the two don't match in every RGB level, method returns false;
					 If images are different sizes, method returns false;
					 If an input image is null and the current image is not, method returns false.
	*/
	bool operator==(const Image&) const;

	/*
	 operator!=
	 Preconditions: input parameter is an Image object type
	 Postconditions: opposite to the operator== overload:
					 if the two Image objects (this and input) don't match in terms of 
					 every single RGB levels in each pixel, method returns true.
					 If the two don't match in every RGB level, method returns true;
					 If images are not the same sizes, method returns true;
					 If an input image is null and the current image is not, method returns true.
	*/
	bool operator!=(const Image&) const;

	/*
	 operator>
	 Preconditions: input parameter is an Image object type
	 Postconditions: if left hand side Image object contains more pixels than right hand Image object, 
					 method returns true.
					 if left hand side Image object contains less pixels than right hand Image object, 
					 method returns false.
	*/
	bool operator>(const Image&) const;

	/*
	 operator<
	 Preconditions: input parameter is an Image object type
	 Postconditions: if left hand side Image object contains less pixels than right hand Image object, 
					 method returns true.
					 if left hand side Image object contains more pixels than right hand Image object, 
					 method returns false.
	*/
	bool operator<(const Image&) const;

	/*
	 operator<<  
	 Preconditions: input parameter is a valid Image object type
	 Postconditions: a statement that outputs the size of the Image object in terms of
					 rows and columns is displayed to the output console
	*/
	friend ostream& operator<<(ostream&, const Image&);

	/*
	 mirrorImage: 
	 Preconditions: the calling Image object has rows and columns pixels allocated
	 Postconditions: a copy of the input Image object is created and mirrored such that the left side 
				     and the right side pixels are reversed
	*/
	Image mirrorImage() const;
};

#endif
