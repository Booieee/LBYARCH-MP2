#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

extern void calc_acceleration(float* matrix, int* acce, int rows);


void read_input(float* matrix, int rows) {
	// Reads input data from user
	// param: matrix: pointer to allocated memory for input data
	//        rows: number of cars (matrix rows)
	int i = 0;

	for (i = 0; i < rows; i++) {
		printf("Enter data for car %d (Vi, Vf, Time): ", i + 1);
		scanf("%f %f %f", &matrix[i * 3], &matrix[i * 3 + 1], &matrix[i * 3 + 2]);
	}

}

void print_result(int acce, int rows) {
	// Prints the calculated acceleration values
	// param: acce: array of calculated acceleration values
	//        rows: number of cars (size of the array)
	int i = 0;

	printf("Accelerations: \n");

	for(i = 0; i < rows; i++) {
		printf("Car %d: %d m/s^2\n", i + 1, acce[i]);
	}
}

int main() {
	//Read input (number of cars and matrix data)
	//Allocate memory for input matrix and output array
	// Call assembly function to perform calculations
	// Print results
	// Free allocated memory
	int rows = 0;
	float* matrix = NULL;
	int* accelerations = NULL;

	// Read number of cars
	print("Enter number of cars: \n");
	scanf("%d", &rows);

	//Allocate memory for matrix and accelerations
	matrix = (float*)malloc(rows * 3 * sizeof(float));
	accelerations = (int*)malloc(rows * sizeof(int));

	if (matrix == NULL || accelerations == NULL) {
		printf("Memory allocation failed.\n");
		return 1;
	}

	// Read input data
	read_input(matrix, rows);

	//calculate accelerations with assembly function
	calc_acceleration(matrix, accelerations, rows);

	//print the results
	print_result(accelerations, rows);

	return 0;
}