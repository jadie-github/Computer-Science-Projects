/*Jessica Nguyen
CSS342, Project3
This file describes the interface to the Rectangle class.
Functionality includes:
constructor for Rectangle objects;
accessors for size, current rows and columns, previous rows and columns coordinates in the Rectangle object;
mutators for size, current rows and columns, previous rows and columns coordinates in the Rectangle object;
overload operators: ==, !=, <<;
*/
#pragma once


#ifndef R_H
#define R_H

#include <iostream>
using namespace std;

class Rectangle {
private:
	int rowSize;
	int colSize;
	int currRow;
	int currCol;
	int prevRow;
	int prevCol;

public:

	//constructor method
	/*
	 Rectangle: bookkeeps upper left coordinate for current image 
	 Preconditions: int inputs for rows and columns coordinates must be >= 0.
	 Postconditions: creates a Rectangle object using the input parameters that represent coordinates for rows and columns; 
					 rows and columns lengths are also initilized.
					 Previous coordinates for rows and columns are default to (0,0) as the starting point.
					 Row size and column size are default to 0.
	*/
	Rectangle(int, int);

	//overload methods
	/*
	 operator<<
	 Preconditions: input parameter is a valid Rectangle object type
	 Postconditions: a statement that outputs the size of the Rectangle object in terms of
					 the rectangle size and current coordinates is displayed to the output console
	*/
	friend ostream& operator<<(ostream&, const Rectangle&);

	/*
	 operator==
	 Preconditions: input parameter is a valid Rectangle object type
	 Postconditions: if the two Rectangle objects (this and input) match in terms of
					 rows and columns lengths, current coordinates and previous coordinates, method returns true.
					 If the two don't match in one criteria, method returns false.
	*/
	bool operator==(const Rectangle&) const;

	/*
	 operator!=
	 Preconditions: input parameter is a valid Rectangle object type
	 Postconditions: opposite to the operator== method, if the two Rectangle objects (this and input) match in terms of
					 rows and columns lengths, current coordinates and previous coordinates, method returns false.
					 If the two don't match in one criteria, method returns true.
	*/
	bool operator!=(const Rectangle&) const;


	//accessor methods
	/*
	 getSize()
	 Preconditions: current Rectangle object must exist and is not null
	 Postconditions: the row size multiplies by the column size is returned

	*/
	int getSize() const;

	/*
	 getRowSize()
	 Preconditions: current Rectangle object must exist and is not null
	 Postconditions: the row size is returned

	*/
	int getRowSize() const;

	/*
	 getColumnSize()
	 Preconditions: current Rectangle object must exist and is not null
	 Postconditions: the column size is returned

	*/
	int getColSize() const;

	/*
	 getCurrRow()
	 Preconditions: current Rectangle object must exist and is not null
	 Postconditions: the current row coordinate is returned

	*/
	int getCurrRow() const;

	/*
	 getCurrCol()
	 Preconditions: current Rectangle object must exist and is not null
	 Postconditions: the current column coordinate is returned

	*/
	int getCurrCol() const;

	/*
	 getPrevRow()
	 Preconditions: current Rectangle object must exist and is not null
	 Postconditions: the previous row coordinate is returned

	*/
	int getPrevRow() const;

	/*
	 getPrevCol()
	 Preconditions: current Rectangle object must exist and is not null
	 Postconditions: the previous column coordinate is returned

	*/
	int getPrevCol() const;

	//mutator methods
	/*
	 changeCurrRow:
	 Preconditions: current Rectangle object must exist and is not null;
					the int representing the new coordinate to the row is within bounds of Rectangle object.
	 Postconditions: the current row coordinate is updated and changed to the value specified by input parameter.
	*/
	void changeCurrRow(int);

	/*
	 changeCurrCol:
	 Preconditions: current Rectangle object must exist and is not null;
					the int representing the new coordinate to the column is within bounds of Rectangle object.
	 Postconditions: the current column coordinate is updated and changed to the value specified by input parameter.
	*/
	void changeCurrCol(int);

	/*
	 changePrevRow:
	 Preconditions: current Rectangle object must exist and is not null;
					the int representing the new coordinate to the row is within bounds of Rectangle object.
	 Postconditions: the previous row coordinate is updated and changed to the value specified by input parameter.
	*/
	void changePrevRow(int);

	/*
	 changePrevCol:
	 Preconditions: current Rectangle object must exist and is not null;
					the int representing the new coordinate to the column is within bounds of Rectangle object.
	 Postconditions: the previous column coordinate is updated and changed to the value specified by input parameter.
	*/
	void changePrevCol(int);

	/*
	 changeRowSize:
	 Preconditions: current Rectangle object must exist and is not null;
					the int representing the new coordinate to the row is within bounds of Rectangle object.
	 Postconditions: the current row size is updated and changed to the value specified by input parameter.
	*/
	void changeRowSize(int);

	/*
	 changeColSize:
	 Preconditions: current Rectangle object must exist and is not null;
					the int representing the new coordinate to the column is within bounds of Rectangle object.
	 Postconditions: the current column size is updated and changed to the value specified by input parameter.
	*/
	void changeColSize(int);
};
#endif
