/*Jessica Nguyen
CSS 342, Project 4
This driver class takes in a GIF input image, creates segments of similar pixels in the image, 
writes the average color to its corresponding segments, merge together separate segments as it scans the image 
in raster order, and output to the console the total number of segments found,
the number of pixels in the merged group, and the average color of the merged group. */

#include "Container.h";
#include "Image.h"
#include <iostream>
using namespace std;

//forward declarations
Image& transform(Image& input, Image& output);
void markVisited(Image& output, PixelInfo& pixelInput);
bool isAMatch(PixelInfo& seed, PixelInfo& cur);
void findNeighbors(Image& input, Image& output, Container& segment, PixelInfo& pixelInput);
void writeAverageColor(Image& output, Container& segment, PixelInfo& avg);
bool isVisited(Image& output, int row, int col);

/*main()
Precondition:   test4.gif exists and is a valid GIF image
Postconditions: output.gif will be written containing a simplified version of the original input image
				where similar pixels are grouped into different segments and written to the same average color.
*/
int main() {
	Image input("test4.gif"); //reads in input GIF file

	Image output(input.getRow(), input.getColumn()); //creates a black image with same dimensions as input
	 
	output = transform(input, output); //create segments out of original image, write average color to segments

	output.outputImage("output.gif"); //outputs new image into "output.gif"

	return 0;
}


/*transform()
Precoditions:	input and output are valid, intilized Image objects
Postconditions: returns an Image object, storing a simplified version of the original input image
				where similar pixels are grouped into different segments and written to the same average color.
*/
Image& transform(Image& input, Image& output) {

	int containerCount = 0;
	Container firstSegment;
	PixelInfo avg = { 0,0,0,0,0 }; //average color at first is preset to 0 -- to be overwritten later
	
	for (int r = 0; r < input.getRow(); r++) {
		for (int c = 0; c < input.getColumn(); c++) {
			
			if (!isVisited(output, r, c)) { // only make a new container if pixel hasn't been visited
				
				pixel p2 = input.getPixel(r, c);
				PixelInfo seed2 = { p2.red,p2.green,p2.blue, r,c };
				//cout << "row: " << r << " col: " << c << endl;
				Container secondSegment(seed2);
				
				findNeighbors(input, output, secondSegment, seed2);

				PixelInfo secondAvg = secondSegment.getAverageColor(); //finds avg color of the second container

				writeAverageColor(output, secondSegment, secondAvg); //writes average color for second container

				firstSegment.merge(secondSegment); //merges the 2 together

				avg = firstSegment.getAverageColor(); //finds the overall average color of the merged container
				
				containerCount++; //increments container count
				
			}
		}
	}

	//output console
	cout << "The total number of segments found is: " << containerCount << endl;
	cout << "The number of pixels in the merged group is: " << firstSegment.getSize() << endl;
	cout << "The average color of this merged group is: red: " << avg.red << ", green: " << avg.green << ", blue: " << avg.blue << endl;

	return output;
}

/*findNeighbors(): find neighboring pixels which have similar RGB color to the current pixel
Precoditions:	input and output are valid, intilized Image objects; 
				segment is an initialized Container object with at least one seed node;
				pixelInput is an initialized PixelInfo object with declard red, green, blue, row and col values.
Postconditions: all neighboring pixels which have similar RGB color to the seed pixel will be added to input Container. 
*/
// all updated segment is stored in container
void findNeighbors(Image& input, Image& output, Container& segment, PixelInfo& pixelInput) {

	// base case: return if out of bounds
	if ((pixelInput.row >= input.getRow() || pixelInput.row < 0) ||
		(pixelInput.col >= input.getColumn() || pixelInput.col < 0)) {
		return;
	}

	//base case: return if marked visited
	if (output.getPixel(pixelInput.row, pixelInput.col).red != 0) {
		return;
	}
	
	//base case: return if this PixelInput is not close enough to the seed pixel's colors
	if (!isAMatch(segment.getSeed(), pixelInput)) {
		return;
	} 
	
	bool isSeed = (pixelInput.row == segment.getSeed().row) && (pixelInput.col == segment.getSeed().col);
	
	// If pixleInput is the seed node, it has already been added to the Container when initialized, 
	// so don't add twice again to the container, check for isSeed
	if (isAMatch(segment.getSeed(), pixelInput) && !isSeed) {
		segment.add(pixelInput);
	}

	//marks the current pixel as visited
	markVisited(output, pixelInput);

	//use recursion to find neighbors left, right, up and down of current PixelInfo
	if ((pixelInput.row - 1) >= 0) {
		pixel p = input.getPixel(pixelInput.row - 1, pixelInput.col);
		PixelInfo up = { p.red, p.green, p.blue, pixelInput.row - 1, pixelInput.col };
		findNeighbors(input, output, segment, up);
	}

	if (pixelInput.row + 1 < input.getRow()) {
		pixel p = input.getPixel(pixelInput.row + 1, pixelInput.col);
		PixelInfo down = { p.red, p.green, p.blue,pixelInput.row + 1, pixelInput.col };
		findNeighbors(input, output, segment, down);
	}
	if (pixelInput.col - 1 >= 0) {
		pixel p = input.getPixel(pixelInput.row, pixelInput.col-1);
		PixelInfo left = { p.red, p.green, p.blue, pixelInput.row, pixelInput.col - 1};
		findNeighbors(input, output, segment, left);
	}
	if (pixelInput.col + 1 < input.getColumn()) {
		pixel p = input.getPixel(pixelInput.row, pixelInput.col + 1);
		PixelInfo right = { p.red, p.green, p.blue, pixelInput.row, pixelInput.col + 1 };
		findNeighbors(input, output, segment, right);
	}
}

/* isVisited()
Precoditions:	output is a valid, intilized Image object;
				input row >= 0 && row < output row size;
				input col >= 0 && col < output col size;
Postconditions: returns true if the pixel location in the output image has already been visited (has a non-black color)
				returns false if the pixel location in the output image has not been visited (has black color: 0,0,0)
*/
bool isVisited(Image& output, int row, int col) {
	if (row < 0 || row >= output.getRow() || col < 0 || col > output.getColumn()) {
		cout << "Trying to access invalid row and col index." << endl;
		exit(-1);
	}

	return output.getPixel(row, col).red != 0 || output.getPixel(row, col).green != 0 || output.getPixel(row, col).blue != 0;
}

/*markVisited()
Precoditions:	output is a valid, intilized Image object; 
				pixelInput is an initialized PixelInfo object with declard red, green, blue, row and col values.
Postconditions: the location of the input PixelInfo in the output Image will be marked visited (has red value 255)
*/
void markVisited(Image& output, PixelInfo& pixelInput) {
	//temporarily mark as red (255,0,0) for later distinction to write average color
	output.changeRed(output.getPixel(pixelInput.row, pixelInput.col), 255);
}

/*isAMatch()
Precoditions:	seed and cur are initialized PixelInfo objects with declard red, green, blue, row and col values.
Postconditions: returns true if cur's RGB values are similar enough to seed's RGB values (under 100 bytes in difference)
				returns false if cur's and seed's RGB values are not similar enough (>= 100 bytes in difference)
*/
bool isAMatch(PixelInfo& seed, PixelInfo& cur) {
	return (abs(seed.red - cur.red) + abs(seed.green - cur.green) + abs(seed.blue - cur.blue) < 100);
}

/*writeAverageColor()
Precoditions:	output is a valid, intilized Image object; 
				segment is an initialized Container object with at least one seed node;
				avg is an initialized PixelInfo object with declard red, green, blue, row and col values.
Postconditions: every PixelInfo object inside the segment Container will be written to the output image with one
				average color specified in PixelInfo avg.
*/
void writeAverageColor(Image& output, Container& segment, PixelInfo& avg) {
	Container temp;
	while (!segment.isEmpty()) {
		PixelInfo toWrite = {0,0,0,0,0};

		// remove pixels from the container until it's empty
		if (segment.remove(toWrite)) {
			temp.add(toWrite); // stores in temp so you can add pixels back once done processing
			
			//set pixel in the output to specified avg color
			output.changeRed(output.getPixel(toWrite.row, toWrite.col), avg.red);
			output.changeGreen(output.getPixel(toWrite.row, toWrite.col), avg.green);
			output.changeBlue(output.getPixel(toWrite.row, toWrite.col), avg.blue);

		}
	}

	//add pixels back to original Container
	while (!temp.isEmpty()) {
		PixelInfo toAdd;
		if (temp.remove(toAdd)) {
			segment.add(toAdd);
		}
	}
}
