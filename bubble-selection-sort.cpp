/*
* Data Structure & Algorithm | Assignment 1
* This is a program to study, measure and compare the time complexity of bubble sort and selection sort
* @author Norman Low Wei Kit
*/

#include <iostream>
#include <time.h>
using namespace std;

/* Constant definitions */
#define arrayRows 5		// Number of arrays rows to generate
#define elementsMinSize 1000	// Determine the minimum array size used this benchmark
#define elementsMaxSize 5000	// Determine the maximum array size used this benchmark

int listA[ arrayRows ][ elementsMaxSize ];	// Multidimensional array for use with bubbleSort
int listB[ arrayRows ][ elementsMaxSize ];	// Multidimensional array for use with insertionSort
										// Example: array listA[5][25000] will have 5 rows and 25000 columns each row
int arraySize[ arrayRows ];	// Initialize arraySize

/* Generate elements into array */
void initiateArray() {
	int listSize;	// Temporarily hold the current max size of array
	int elementsSize = elementsMinSize;	// Copy minimum size of array to a non-constant manipulateable variable
										// Constant variable elementsMinSize will no longer be used
	for(int k = 0; k < arrayRows; k++) {	
		arraySize[ k ] = elementsSize;	// Filling up the global arraySize variable | k is rows | elementsSize is columns
		elementsSize += elementsMaxSize / arrayRows;	// Generate size of arrays between elementsMinSize and elementMaxSize
	} // end for

	for(int i = 0; i < arrayRows; i++) {
		srand(time(NULL));	// Generates a new seed for random()
		listSize = arraySize[ i ];	// Copying the max number of elements exist in listA[i] and listB[i]

		for(int j = 0; j < listSize; j++) {		// Loop accordingly
			listA[ i ][ j ] = rand() % 1000;	// Randomly generate values from the range of 0-1000 into j
			listB[ i ][ j ] = listA[ i ][ j ];	// Duplicate array of randomly generated values
		} // end inner for loop
	} // end outer for loop
} // end initiateArray function prototype

void bubbleSort( int arrayIndex ) {
	int i, j;	// Loop indexes
	int temp;	// Holding the temporary value in the arrays

	for (i = 0; i < arraySize[ arrayIndex ]; i++ ) {  // Looping from 0 to maximum index held by arraySize
		for (j = 0; j < arraySize[ arrayIndex ] - i - 1; j++ ) {	// Array begins at index 0 not 1 hence arraySize[] - 1
			if ( listA[ arrayIndex ][ j ] > listA[ arrayIndex ][ j + 1 ] ) { // Condition to swap values
				 temp = listA[arrayIndex][ j ];		// Backup value into an temporary variable
				 listA[ arrayIndex ][ j ] = listA[ arrayIndex ][ j + 1 ];	// Initial value is swapped
				 listA[ arrayIndex ][ j + 1 ] = temp;		// Inherit value from a backup
			} // end if
		} // end inner for loop
	} // end outer for loop
} // end bubbleSort function prototype

int insertionSort( int arrayIndex ) {
	int i, j;	// Loop indexes
	int temp;	// Holding the temporary value in the arrays

	for( i = 1; i < arraySize[ arrayIndex ]; i++) { // Insertion sort begins at the 2nd index hence i = 1 and not 0
		temp = listB[ arrayIndex ][ i ];	// Backup values into temp variable
		j = i - 1; // Define the index position of j
		while( temp < listB[ arrayIndex ][ j ] && j >= 0) {		// "j >= 0" is to keep sorting from going out of bounds						
			listB[ arrayIndex ][ j + 1 ] = listB[ arrayIndex ][ j ];	
			j--;	// j is decremented and this condition will be tested again in while loop
		} // end while
		listB[ arrayIndex ][ j + 1 ] = temp;	// Next adjacent index will have value from temp
	} // end for

	return 0;
} // end insertionSort function prototype

void main() {
	clock_t startTime, endTime;
	double duration;	// Variable to record time taken to finish performing an algorithm

	initiateArray(); // Initiating the primary requirements : Generating the pace and filling the arrays

	cout << "Sorting In Progress...\n\n\n";

	for( int i = 0; i < arrayRows; i++) {	// Calling both sort systems and requiring them to sort all arrays in order
		
		cout << "Sorting Benchmark "<< i + 1 << ": " << arraySize[ i ] << " Indexes\n";

		startTime = clock();	// Records the start time
		bubbleSort( i );		// Execute bubbleSort 
		endTime = clock();		// Records the end time

		duration = (endTime - startTime) / 1000.0;	// Time taken to finish performing an algorithm
		cout << endl << "Bubble sort needs " << duration << " ms to complete.\n";

		startTime = clock();
		insertionSort( i );		// Execute insertionSort
		endTime = clock();

		duration = (endTime - startTime) / 1000.0;
		cout << "Insertion sort needs " << duration << " ms to complete.\n\n";
	} // end for

	cout << "\nEnd of sorting algorithm benchmark.\n\n" << endl;
} // end main