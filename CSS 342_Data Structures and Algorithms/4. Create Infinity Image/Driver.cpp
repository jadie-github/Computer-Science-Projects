/*Jessica Nguyen
CSS342, Project3
This class utilizes the methods defined in header classes "Image.h" and "Rectangle.h" to perform a recursive
fractal operation on an input GIF image. This driver class reads in a GIF image file and creates a new GIF image
that consists of a smaller-sized version of the original image on the upper left orner, a smaller-sized flipped version
of the original image on the bottom right corner, and uses the same pattern to draw to the remaining upper right and lower left
corners of the image until there is no more space (pixels) to be allocated.
*/

#include "Image.h"
#include "Rectangle.h"
using namespace std;

//forward declarations
Image makeFractal(Image&);
void writePixels(Image&, Image&);
void writeUpperLeft(Rectangle input, Image& inputImage, Image& outputImage);
void writeLowerRight(Rectangle input, Image& inputImage, Image& outputImage);
void writeExtra(Rectangle input, Image& inputImage, Image& outputImage);

/* main()
Precondition:   test3.gif exists and is a valid GIF image
Postconditions: output.gif will be written and it will contain
				a recursive fractal image version
				of the original image in test3.gif
*/
int main() {
	//reads in image file
	Image test("test3.gif");

	//makes fractal image based off of original image
	Image output = makeFractal(test);

	//outputs fractal image to file
	output.outputImage("output.gif");

}

/* makeFractal()
Precondition: input parameter is a valid Image object type
Postcondition: returns a newly created Image object that is the fractal image of the original Image object
*/
Image makeFractal(Image& inputImage) {
	//creates a new blank image to write output into
	Image fractal(inputImage.getRow(), inputImage.getColumn());

	//creates a Rectangle object for bookeeping the location of the upper left corner to write images
	Rectangle input(0, 0);

	input.changeRowSize(inputImage.getRow());
	input.changeColSize(inputImage.getColumn());

	//performing fractal recursion on upper left shrinked image
	writeUpperLeft(input, inputImage, fractal);

	//performing fractal recursion on lower right shrinked and flipped image
	writeLowerRight(input, inputImage, fractal);

	return fractal;
}

/* writeUpperLeft()
Precondition: input Rectangle object is already initilized with values
			  inputImage is a valid reference to an Image object type
			  outputImage is a valid reference to an Image object type
Postcondition: the upper left portion of the fractal image with continuously shrinking
			   images will be written to the outputImage from the original inputImage
*/
void writeUpperLeft(Rectangle input, Image& inputImage, Image& outputImage) {

	if (input.getRowSize() != 0 && input.getColSize() != 0) {

		int redValue;
		int blueValue;
		int greenValue;

		//traversing the rows and columns of inputImage in order to average RGB values from pixels
		for (int r = 0; r < input.getRowSize() / 2; r++) {

			for (int c = 0; c < input.getColSize() / 2; c++) {

				//averaging RGB values from 4 specific coordinate from inputImage at a time
				redValue = (inputImage.getRed(r * 2 + input.getPrevRow(), c * 2 + input.getPrevCol()) +
					inputImage.getRed(r * 2 + 1 + input.getPrevRow(), c * 2 + input.getPrevCol()) +
					inputImage.getRed(r * 2 + input.getPrevRow(), c * 2 + 1 + input.getPrevCol()) +
					inputImage.getRed(r * 2 + 1 + input.getPrevRow(), c * 2 + 1 + input.getPrevCol())) / 4;

				blueValue = (inputImage.getBlue(r * 2 + input.getPrevRow(), c * 2 + input.getPrevCol()) +
					inputImage.getBlue(r * 2 + 1 + input.getPrevRow(), c * 2 + input.getPrevCol()) +
					inputImage.getBlue(r * 2 + input.getPrevRow(), c * 2 + 1 + input.getPrevCol()) +
					inputImage.getBlue(r * 2 + 1 + input.getPrevRow(), c * 2 + 1 + input.getPrevCol())) / 4;

				greenValue = (inputImage.getGreen(r * 2 + input.getPrevRow(), c * 2 + input.getPrevCol()) +
					inputImage.getGreen(r * 2 + 1 + input.getPrevRow(), c * 2 + input.getPrevCol()) +
					inputImage.getGreen(r * 2 + input.getPrevRow(), c * 2 + 1 + input.getPrevCol()) +
					inputImage.getGreen(r * 2 + 1 + input.getPrevRow(), c * 2 + 1 + input.getPrevCol())) / 4;

				//write the average pixel values to a specified coordinate in the new outputImage
				outputImage.changeRed(outputImage.getPixel(r + input.getCurrRow(), c + input.getCurrCol()), redValue);
				outputImage.changeBlue(outputImage.getPixel(r + input.getCurrRow(), c + input.getCurrCol()), blueValue);
				outputImage.changeGreen(outputImage.getPixel(r + input.getCurrRow(), c + input.getCurrCol()), greenValue);
			}
		}


		//write in extra rows and columns if input has odd rows or columns
		writeExtra(input, outputImage, outputImage);

		//updates new row and column lengths for every time the image recurses
		int newRowLength = input.getRowSize() / 2;
		int newColLength = input.getColSize() / 2;

		//creates new Rectangle object to bookeep new coordinates for recursion algorithm on upper left corner
		Rectangle upper(input.getCurrRow(), input.getCurrCol() + newColLength);
		upper.changeRowSize(newRowLength);
		upper.changeColSize(newColLength);

		//bookeeps previous upper left corner of the previous image so the current image knows where to refer to when it starts writing pixels
		upper.changePrevRow(input.getCurrRow());
		upper.changePrevCol(input.getCurrCol());

		//performs recursion to keep on writing smaller images to the upper left corner on the upper half of the image
		writeUpperLeft(upper, outputImage, outputImage);

		//creates new Rectangle object to bookeep new coordinates for recursion algorithm on upper left corner
		Rectangle lower(input.getCurrRow() + newRowLength, input.getCurrCol());
		lower.changeRowSize(newRowLength);
		lower.changeColSize(newColLength);

		//bookeeps previous upper left corner of the previous image so the current image knows where to refer to when it starts writing pixels
		lower.changePrevRow(input.getCurrRow());
		lower.changePrevCol(input.getCurrCol());

		//performs recursion to keep on writing smaller images to the upper left corner on the bottom half of the image
		writeUpperLeft(lower, outputImage, outputImage);

	}
}

/* writeLowerRight()
Precondition:input Rectangle object is already initilized with values
			 inputImage is a valid reference to an Image object type
			 outputImage is a valid reference to an Image object type
Postcondition: the lower right portion of the fractal image with continuously shrinking
			   and flipped images will be written to the outputImage from the original inputImage
*/
void writeLowerRight(Rectangle input, Image& inputImage, Image& outputImage) {
	if (input.getRowSize() != 0 && input.getColSize() != 0) {

		int maxR = input.getRowSize() - 1;
		int maxC = input.getColSize() - 1;

		int redValue;
		int blueValue;
		int greenValue;

		//traversing the rows and columns of inputImage in order to average RGB values from pixels
		for (int r = 0; r < input.getRowSize() / 2; r++) {

			for (int c = 0; c < input.getColSize() / 2; c++) {
				redValue = (inputImage.getRed(maxR - r * 2 + input.getPrevRow(), maxC - c * 2 + input.getPrevCol()) +
					inputImage.getRed(maxR - r * 2 - 1 + input.getPrevRow(), maxC - c * 2 + input.getPrevCol()) +
					inputImage.getRed(maxR - r * 2 + input.getPrevRow(), maxC - c * 2 - 1 + input.getPrevCol()) +
					inputImage.getRed(maxR - r * 2 - 1 + input.getPrevRow(), maxC - c * 2 - 1 + input.getPrevCol())) / 4;

				blueValue = (inputImage.getBlue(maxR - r * 2 + input.getPrevRow(), maxC - c * 2 + input.getPrevCol()) +
					inputImage.getBlue(maxR - r * 2 - 1 + input.getPrevRow(), maxC - c * 2 + input.getPrevCol()) +
					inputImage.getBlue(maxR - r * 2 + input.getPrevRow(), maxC - c * 2 - 1 + input.getPrevCol()) +
					inputImage.getBlue(maxR - r * 2 - 1 + input.getPrevRow(), maxC - c * 2 - 1 + input.getPrevCol())) / 4;

				greenValue = (inputImage.getGreen(maxR - r * 2 + input.getPrevRow(), maxC - c * 2 + input.getPrevCol()) +
					inputImage.getGreen(maxR - r * 2 - 1 + input.getPrevRow(), maxC - c * 2 + input.getPrevCol()) +
					inputImage.getGreen(maxR - r * 2 + input.getPrevRow(), maxC - c * 2 - 1 + input.getPrevCol()) +
					inputImage.getGreen(maxR - r * 2 - 1 + input.getPrevRow(), maxC - c * 2 - 1 + input.getPrevCol())) / 4;

				int lengthRow = input.getRowSize() / 2;
				int lengthCol = input.getColSize() / 2;

				//write the average pixel values to a specified coordinate in the new outputImage
				if (input.getRowSize() % 2 == 1) {
					lengthRow++;
				}
				if (input.getColSize() % 2 == 1) {
					lengthCol++;
				}

				outputImage.changeRed(outputImage.getPixel(r + input.getCurrRow() + lengthRow, c + input.getCurrCol() + lengthCol), redValue);
				outputImage.changeBlue(outputImage.getPixel(r + input.getCurrRow() + lengthRow, c + input.getCurrCol() + lengthCol), blueValue);
				outputImage.changeGreen(outputImage.getPixel(r + input.getCurrRow() + lengthRow, c + input.getCurrCol() + lengthCol), greenValue);
			}
		}

		//updates new row and column lengths for every time the image recurses
		int newRowLength = input.getRowSize() / 2;
		int newColLength = input.getColSize() / 2;

		//creates new Rectangle object to bookeep new coordinates for recursion algorithm on bottom right corner
		Rectangle upper(input.getCurrRow(), input.getCurrCol() + newColLength);
		upper.changeRowSize(newRowLength);
		upper.changeColSize(newColLength);

		upper.changePrevRow(input.getCurrRow());
		upper.changePrevCol(input.getCurrCol());

		//performs recursion to keep on writing smaller images to the bottom right corner on the upper half of the image
		writeLowerRight(upper, outputImage, outputImage);

		//creates new Rectangle object to bookeep new coordinates for recursion algorithm on bottom right corner
		Rectangle lower(input.getCurrRow() + newRowLength, input.getCurrCol());
		lower.changeRowSize(newRowLength);
		lower.changeColSize(newColLength);

		lower.changePrevRow(input.getCurrRow());
		lower.changePrevCol(input.getCurrCol());
		//performs recursion to keep on writing smaller images to the bottom right corner on the lower half of the image
		writeLowerRight(lower, outputImage, outputImage);

	}
}

/* writeExtra(): to write extra rows and columns to output if the input image has odd rows or columns
Preconditions: input Rectangle object is already initilized with values
			   inputImage is a valid reference to an Image object type
			   outputImage is a valid reference to an Image object type
Postconditions: pixels from extra rows and columns from the input image are written to the output image
*/
void writeExtra(Rectangle input, Image& inputImage, Image& outputImage) {
	int redValue;
	int blueValue;
	int greenValue;
	int row = (input.getRowSize() - 1) / 2; //traverses the last row only
	int col = (input.getColSize() - 1) / 2; //traverses the last column only


	//if input has odd row, average only the values from upper 2 pixels
	if (input.getRowSize() % 2 == 1) {

		for (int col = 0; col < input.getColSize() / 2; col++) {

			redValue = (inputImage.getRed(row * 2 + input.getPrevRow(), col * 2 + input.getPrevCol()) + inputImage.getRed(row * 2 + input.getPrevRow(), col * 2 + 1 + input.getPrevCol())) / 2;
			blueValue = (inputImage.getBlue(row * 2 + input.getPrevRow(), col * 2 + input.getPrevCol()) + inputImage.getBlue(row * 2 + input.getPrevRow(), col * 2 + 1 + input.getPrevCol())) / 2;
			greenValue = (inputImage.getGreen(row * 2 + input.getPrevRow(), col * 2 + input.getPrevCol()) + inputImage.getGreen(row * 2 + input.getPrevRow(), col * 2 + 1 + input.getPrevCol())) / 2;

			outputImage.changeRed(outputImage.getPixel(row + input.getCurrRow(), col + input.getCurrCol()), redValue);
			outputImage.changeBlue(outputImage.getPixel(row + input.getCurrRow(), col + input.getCurrCol()), blueValue);
			outputImage.changeGreen(outputImage.getPixel(row + input.getCurrRow(), col + input.getCurrCol()), greenValue);
		}
	}

	//if input has odd column, average only the values from upper 2 pixels
	if (input.getColSize() % 2 == 1) {

		for (int row = 0; row < input.getRowSize() / 2; row++) {

			redValue = (inputImage.getRed(row * 2 + input.getPrevRow(), col * 2 + input.getPrevCol()) + inputImage.getRed(row * 2 + 1 + input.getPrevRow(), col * 2 + input.getPrevCol())) / 2;
			blueValue = (inputImage.getBlue(row * 2 + input.getPrevRow(), col * 2 + input.getPrevCol()) + inputImage.getBlue(row * 2 + 1 + input.getPrevRow(), col * 2 + input.getPrevCol())) / 2;
			greenValue = (inputImage.getGreen(row * 2 + input.getPrevRow(), col * 2 + input.getPrevCol()) + inputImage.getGreen(row * 2 + 1 + input.getPrevRow(), col * 2 + input.getPrevCol())) / 2;

			outputImage.changeRed(outputImage.getPixel(row + input.getCurrRow(), col + input.getCurrCol()), redValue);
			outputImage.changeBlue(outputImage.getPixel(row + input.getCurrRow(), col + input.getCurrCol()), blueValue);
			outputImage.changeGreen(outputImage.getPixel(row + input.getCurrRow(), col + input.getCurrCol()), greenValue);
		}
	}

	// if both rows and columns are odd, a direct copy of the last pixel of inputImage is written to outputImage
	if (input.getRowSize() % 2 == 1 && input.getColSize() % 2 == 1) {

		redValue = inputImage.getRed(row * 2 + input.getPrevRow(), col * 2 + input.getPrevCol());
		blueValue = inputImage.getBlue(row * 2 + input.getPrevRow(), col * 2 + input.getPrevCol());
		greenValue = inputImage.getGreen(row * 2 + input.getPrevRow(), col * 2 + input.getPrevCol());

		outputImage.changeRed(outputImage.getPixel(row + input.getCurrRow(), col + input.getCurrCol()), redValue);
		outputImage.changeBlue(outputImage.getPixel(row + input.getCurrRow(), col + input.getCurrCol()), blueValue);
		outputImage.changeGreen(outputImage.getPixel(row + input.getCurrRow(), col + input.getCurrCol()), greenValue);
	}
}