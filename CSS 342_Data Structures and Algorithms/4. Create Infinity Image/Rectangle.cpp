/*Jessica Nguyen
CSS342, Project3
This Rectangle class implementation file provides basic functionality to Rectangle class.
Functionality includes:
constructor for Rectangle objects;
accessors for size, current rowsand columns, previous rowsand columns coordinates in the Rectangle object;
mutators for size, current rowsand columns, previous rowsand columns coordinates in the Rectangle object;
overload operators : == , != , << ;
*/

#include "Rectangle.h"

//constructor method
/*
Rectangle:
Preconditions: int inputs for rows and columns coordinates must be >= 0.
Postconditions: creates a Rectangle object using the input parameters that represent coordinates for rows and columns;
				 rows and columns lengths are also initilized.
				 Previous coordinates for rows and columns are default to (0,0) as the starting point.
				 Row size and column size are default to 0.
*/
Rectangle::Rectangle(int row, int col) {
	this->rowSize = 0;
	this->colSize = 0;
	this->currRow = row;
	this->currCol = col;
	this->prevRow = 0;
	this->prevCol = 0;
}

//overload methods
/*
operator<<
Preconditions: input parameter is a valid Rectangle object type
Postconditions: a statement that outputs the size of the Rectangle object in terms of
				 the rectangle size and current coordinates is displayed to the output console
*/
ostream& operator<<(ostream& output, const Rectangle& input) {

	output << "The rectangle size is " << input.rowSize << " x " << input.colSize << endl;
	output << "Current coordinate: (" << input.currRow << ", " << input.currCol << ")" << endl;
	return output;
}

/*
operator==
Preconditions: input parameter is a valid Rectangle object type
Postconditions: if the two Rectangle objects (this and input) match in terms of
				 rows and columns lengths, current coordinates and previous coordinates, method returns true.
				 If the two don't match in one criteria, method returns false.
*/
bool Rectangle::operator==(const Rectangle& input) const {
	return ((this->rowSize * this->colSize) == (input.rowSize * input.colSize)) &&
		(this->currRow == input.currRow) && (this->currCol == input.currCol) &&
		(this->prevRow == input.prevRow) && (this->prevCol == input.prevCol);
}

/*
operator!=
Preconditions: input parameter is a valid Rectangle object type
Postconditions: opposite to the operator== method, if the two Rectangle objects (this and input) match in terms of
				 rows and columns lengths, current coordinates and previous coordinates, method returns false.
				 If the two don't match in one criteria, method returns true.
*/
bool Rectangle::operator!=(const Rectangle& input) const {
	return !operator==(input);
}

//accessor methods
/*
getSize()
Preconditions: current Rectangle object must exist and is not null
Postconditions: the row size multiplies by the column size is returned
*/
int Rectangle::getSize() const {
	return this->rowSize * this->colSize;
}

/*
getRowSize()
Preconditions: current Rectangle object must exist and is not null
Postconditions: the row size is returned
*/
int Rectangle::getRowSize() const {
	return this->rowSize;
}

/*
getColumnSize()
Preconditions: current Rectangle object must exist and is not null
Postconditions: the column size is returned
*/
int Rectangle::getColSize() const {
	return this->colSize;
}

/*
getCurrRow()
Preconditions: current Rectangle object must exist and is not null
Postconditions: the current row coordinate is returned
*/
int Rectangle::getCurrRow() const {
	return this->currRow;
}

/*
getCurrCol()
Preconditions: current Rectangle object must exist and is not null
Postconditions: the current column coordinate is returned
*/
int Rectangle::getCurrCol() const {
	return this->currCol;
}

/*
getPrevRow()
Preconditions: current Rectangle object must exist and is not null
Postconditions: the previous row coordinate is returned
*/
int Rectangle::getPrevRow() const {
	return this->prevRow;
}

/*
getPrevCol()
Preconditions: current Rectangle object must exist and is not null
Postconditions: the previous column coordinate is returned
*/
int Rectangle::getPrevCol() const {
	return this->prevCol;
}

//mutator methods
/*
changeCurrRow:
Preconditions: current Rectangle object must exist and is not null;
				the int representing the new coordinate to the row is within bounds of Rectangle object.
Postconditions: the current row coordinate is updated and changed to the value specified by input parameter.
*/
void Rectangle::changeCurrRow(int r) {
	this->currRow = r;
}

/*
changeCurrCol:
Preconditions: current Rectangle object must exist and is not null;
				the int representing the new coordinate to the column is within bounds of Rectangle object.
Postconditions: the current column coordinate is updated and changed to the value specified by input parameter.
*/
void Rectangle::changeCurrCol(int c) {
	this->currCol = c;
}

/*
changePrevRow:
Preconditions: current Rectangle object must exist and is not null;
				the int representing the new coordinate to the row is within bounds of Rectangle object.
Postconditions: the previous row coordinate is updated and changed to the value specified by input parameter.
*/
void Rectangle::changePrevRow(int r) {
	this->prevRow = r;
}

/*
changePrevCol:
Preconditions: current Rectangle object must exist and is not null;
				the int representing the new coordinate to the column is within bounds of Rectangle object.
Postconditions: the previous column coordinate is updated and changed to the value specified by input parameter.
*/
void Rectangle::changePrevCol(int c) {
	this->prevCol = c;
}

/*
changeRowSize:
Preconditions: current Rectangle object must exist and is not null;
			   the int representing the new coordinate to the row is within bounds of Rectangle object.
Postconditions: the current row size is updated and changed to the value specified by input parameter.
*/
void Rectangle::changeRowSize(int n) {
	this->rowSize = n;
}

/*
changeColSize:
Preconditions: current Rectangle object must exist and is not null;
			   the int representing the new coordinate to the column is within bounds of Rectangle object.
Postconditions: the current column size is updated and changed to the value specified by input parameter.
*/
void Rectangle::changeColSize(int n) {
	this->colSize = n;
}