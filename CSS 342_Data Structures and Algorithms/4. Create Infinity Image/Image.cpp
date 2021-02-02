//Jessica Nguyen
//CSS342, Project2
//This image class implementation file provides basic functionality to Image class.
//Functionality includes: 
// constructor for image files using filename or size;
// constructor, destructor, operator= methods for dynamic memory;
// accessors for rows and columns in the image;
// accessors and mutators for individual image pixels and RGB bytes;
// output to file;
// overload operators: ==, !=, >, <, <<;
// and mirror the image.


#include "Image.h"
#include "ImageLib.h"

//constant
const int MAX_RGB_VALUE = 255;
const int MIN_RGB_VALUE = 0;



//constructor methods:
/*
Image:
Preconditions: filename refers to a file that stores a GIF image.
Postconditions: creates an Image object using the image file contained in input string parameter.
				If the load is unsuccessful, image is deallocated.
*/
Image::Image(string fileName) {
	pic = ReadGIF(fileName);
}

/*
Image:
Preconditions: int inputs for rows and columns must be >= 0.
Postconditions: creates a blank, black Image object using the input parameters that represent sizes for rows and columns.
				If input parameters are invalid (<=0), an error message is displayed.
				If input parameters are not specified, the default size is 360 x 360.
*/
Image::Image(int r, int c) {
	pic = CreateImage(r, c);
}

//dynamic memory methods

/*
Image copy constructor
Preconditions: reference to the Image object to be copied must exist.
Postconditions: if sufficient memory is available, a copy of the input file
				is returned using newly allocated memory.
				Otherwise, the returned image has:
				rows = 0, cols =0 , pixels = nullptr.
*/
Image::Image(const Image& image) : pic(CopyImage(image.pic)) {}

/*
Image destructor
Preconditions: Image object must exist and is not null
Postconditions: the memory allocated to the pixels of input Image object has
				been deallocated.  Also, the image values are set to:
				rows = 0, cols = 0, pixels = nullptr.
*/
Image::~Image() {
	DeallocateImage(this->pic);
}

/*
operator=
Preconditions: Image object must exist and is not null
Postconditions: the calling Image object is assigned to the current Image object
				and both objects share the same memory address to the Image object.
*/
const Image& Image::operator=(const Image& image) {
	if (this != &image) {
		// necessary: deallocation will destroy input if they are the same so no memory leaks occur
		DeallocateImage(this->pic);
		this->pic = CopyImage(image.pic);
	}
	return *this;
}

//accessor methods
/*
getRow:
Preconditions: current Image object must exist and is not null
Postconditions: the int number of rows this Image object has is returned
*/
int Image::getRow() const {
	return this->pic.rows;
}

/*
getColumn:
Preconditions: current Image object must exist and is not null
Postconditions: the int number of columns this Image object has is returned
*/
int Image::getColumn() const {
	return this->pic.cols;
}

/*
getPixel:
Preconditions: current Image object must exist and is not null;
			   the two int parameters representing the location (row, column) of the pixel
			   are within bounds and valid.
Postconditions: the reference to the pixel object specified within this Image object is returned.
*/
pixel& Image::getPixel(int row, int col) const {
	if (row < 0 || row > (this->pic.rows-1) || col < 0 || col > (this->pic.cols-1)) {
		cout << "Invalid get pixel index." << endl;
		exit(-1); // invalid, exit program
	}
	else {
		return this->pic.pixels[row][col];
	}
}

/*
getRed:
Preconditions: current Image object must exist and is not null;
			   the two int parameters representing the location (row, column) of the pixel
			   are within bounds and valid.
Postconditions: the red byte value of the pixel being specified by row and column is returned.
*/
byte Image::getRed(int row, int col) const {
	if (row < 0 || row >(this->pic.rows - 1) || col < 0 || col >(this->pic.cols - 1)) {
		cout << "Invalid get red index." << endl;
		exit(-1); // invalid, exit program
	}
	else {
		return getPixel(row, col).red;
	}
}

/*
getGreen:
Preconditions: current Image object must exist and is not null;
			   the two int parameters representing the location (row, column) of the pixel
			   are within bounds and valid.
Postconditions: the green byte value of the pixel being specified by row and column is returned.
*/
byte Image::getGreen(int row, int col) const {
	if (row < 0 || row >(this->pic.rows - 1) || col < 0 || col >(this->pic.cols - 1)) {
		cout << "Invalid  get green index." << endl;
		exit(-1); // invalid, exit program
	}
	else {
		return getPixel(row, col).green;
	}
}

/*
getBlue:
Preconditions: current Image object must exist and is not null;
			   the two int parameters representing the location (row, column) of the pixel
			   are within bounds and valid.
Postconditions: the blue byte value of the pixel being specified by row and column is returned.
*/
byte Image::getBlue(int row, int col) const {
	if (row < 0 || row >(this->pic.rows - 1) || col < 0 || col >(this->pic.cols - 1)) {
		cout << "Invalid get blue index." << endl;
		exit(-1); // invalid, exit program
	}
	else {
		return getPixel(row, col).blue;
	}
}

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
void Image::changeRed(pixel& input, int value) {
	if (value > MAX_RGB_VALUE) {
		input.red = MAX_RGB_VALUE;
	}
	else if (value < MIN_RGB_VALUE) {
		input.red = MIN_RGB_VALUE;
	}
	else {
		input.red = value;
	}
}

/*
changeGreen:
Preconditions: current Image object must exist and is not null;
				the reference to the pixel input is valid;
				the byte input value must be between 0 and 255
Postconditions: the green byte value of the referenced pixel is changed to the specified input value
				If there are overflows (> 255 bytes), the byte value of the pixel is set to 255.
				If there are underflows (< 0 byte), the byte value of the pixel is set to 0.
*/
void Image::changeGreen(pixel& input, int value) {
	if (value > MAX_RGB_VALUE) {
		input.green = MAX_RGB_VALUE;
	}
	else if (value < MIN_RGB_VALUE) {
		input.green = MIN_RGB_VALUE;
	}
	else {
		input.green = value;
	}
}

/*
changeBlue
Preconditions: current Image object must exist and is not null;
				the reference to the pixel input is valid;
				the byte input value must be between 0 and 255
Postconditions: the blue byte value of the referenced pixel is changed to the specified input value
				If there are overflows (> 255 bytes), the byte value of the pixel is set to 255.
				If there are underflows (< 0 byte), the byte value of the pixel is set to 0.
*/
void Image::changeBlue(pixel& input, int value) {
	if (value > MAX_RGB_VALUE) {
		input.blue = MAX_RGB_VALUE;
	}
	else if (value < MIN_RGB_VALUE) {
		input.blue = MIN_RGB_VALUE;
	}
	else {
		input.blue = value;
	}
}

/*
outputImage:
Preconditions: input string for file name is valid file name to store a GIF image.
				current Image object must exist and is not null;
Postconditions: inputImage is saved as a GIF image at the location
				specified by filename.
*/
void Image::outputImage(string filename) const {
	WriteGIF(filename, this->pic);
}

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
bool Image::operator==(const Image& image) const {
	bool isEqual = true;
	if ((this->pic.rows * this->pic.cols) != (image.pic.rows * image.pic.cols)) {
		//check if both images are the same size, if not, they are not equal
		isEqual = false;
	}
	else {
		//traverse the rows and columns to check every pixel RGB levels
		for (int row = 0; row < image.pic.rows; row++) {
			for (int col = 0; col < image.pic.cols; col++) {
				if ((this->pic.pixels[row][col].red != image.pic.pixels[row][col].red) ||
					(this->pic.pixels[row][col].blue != image.pic.pixels[row][col].blue) ||
					(this->pic.pixels[row][col].green != image.pic.pixels[row][col].green)) {
					//if one pixel value doesn't match the other's pixel value, they are unequal
					isEqual = false;
					break;
				}
			}
		}
	}
	return isEqual;
}

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
bool Image::operator!=(const Image& image) const {
	
	//returns opposite value that of operator==
	return !operator==(image);
}

/*
operator>
Preconditions: input parameter is an Image object type
Postconditions: if left hand side Image object contains more pixels than right hand Image object,
				method returns true.
				if left hand side Image object contains less pixels than right hand Image object,
				method returns false.
*/
bool Image::operator>(const Image& image) const {
	return (this->pic.rows * this->pic.cols) > (image.pic.rows * image.pic.cols);
}

/*
operator<
Preconditions: input parameter is an Image object type
Postconditions: if left hand side Image object contains less pixels than right hand Image object,
				method returns true.
				if left hand side Image object contains more pixels than right hand Image object,
				method returns false.
*/
bool Image::operator<(const Image& image) const {
	return (this->pic.rows * this->pic.cols) < (image.pic.rows * image.pic.cols);
}

/*
operator<<
Preconditions: input parameter is a valid Image object type
Postconditions: a statement that outputs the size of the Image object in terms of
				rows and columns is displayed to the output console
*/
ostream& operator<<(ostream& output, const Image& image) {
	output << "The picture size is " << image.pic.rows << " x " << image.pic.cols;
	return output;
}

/*
mirrorImage:
Preconditions: the calling Image object has rows and columns pixels allocated
Postconditions: a copy of the input Image object is created and mirrored such that the left side
				 and the right side pixels are reversed
*/
Image Image::mirrorImage() const {
	//make a new Image object for copying
	Image copy(*this);

	for (int row = 0; row < copy.getRow(); row++) {
		//traverses the rows of image
		int start = 0;
		int end = copy.getColumn() - 1;

		//switches left side and right side pixels so the image input file is mirrored
		while (start < end) {
			pixel temp = copy.getPixel(row, start);
			copy.getPixel(row, start) = copy.getPixel(row, end);
			copy.getPixel(row, end) = temp;
			start++;
			end--;
		}
	}

	return copy;
}