#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

extern void calc_accelerations(float* matrix, int* acce, int rows);

void generate_input(float* matrix, int rows) {
	int i = 0;
	for (i = 0; i < rows; i++) {
		matrix[i * 3] = (float)(rand() % 2000) / 10.0f; // Vi
		matrix[i * 3 + 1] = matrix[i * 3] + (float)(rand() % 1000) / 10.0f; // Vf
		matrix[i * 3 + 2] = 1.0f + (float)(rand() % 90) / 10.0f; // Time: 1 to 10 seconds
	}
}

void read_input(float* matrix, int rows) {
	int i = 0;

	for (i = 0; i < rows; i++) {
		printf("Enter data for car %d (Vi, Vf, Time): ", i + 1);
		scanf_s("%f %f %f", &matrix[i * 3], &matrix[i * 3 + 1], &matrix[i * 3 + 2]);
	}
}


// Prints the calculated acceleration values
// param: acce: array of calculated acceleration values
//        rows: number of cars (size of the array)
void print_result(int* acce, int rows) {
	
	int i = 0;

	printf("Accelerations: \n");

	for(i = 0; i < rows; i++) {
		printf("Car %d: %d m/s^2\n", i + 1, acce[i]);
	}
}

int main() {
	int Y = 0;

	// Read number of cars

	printf("Manual inputting\n");
	printf("Enter number of cars: ");
	scanf_s("%d", &Y);

	//Allocate memory for matrix and accelerations
	float* matrix = (float*)malloc(Y * 3 * sizeof(float));
	int* accelerations = (int*)malloc(Y * sizeof(int));

	// Read input data
	read_input(matrix, Y);

	//calculate accelerations with assembly function
	calc_accelerations(matrix, accelerations, Y);

	//print the results
	print_result(accelerations, Y);

	// Free allocated memory
	free(matrix);
	free(accelerations);

	//for auto-generad inputs
	// generate a random number of cars
	srand(time(NULL));
	Y = rand() % 100 + 1;
	printf("\nGenerating random input for a random number of cars... Now, we generate the randomized %d cars \n", Y);
	float* matrix2 = (float*)malloc(Y * 3 * sizeof(float));
	int* accelerations2 = (int*)malloc(Y * sizeof(int));
	generate_input(matrix2, Y);

	for(int i = 0; i < Y; i++) {

		printf("Car %d: Vi = %.1f, Vf = %.1f, Time = %.1f\n", i + 1, matrix2[i * 3], matrix2[i * 3 + 1], matrix2[i * 3 + 2]);
	}
	calc_accelerations(matrix2, accelerations2, Y);
	print_result(accelerations2, Y);

	free(matrix2);
	free(accelerations2);

	printf("\nFor testing input sizes(Y = {10, 100, 1000, 10000} \n");

	int test_sizes[] = { 10, 100, 1000, 10000 };

	for (int i = 0; i < sizeof(test_sizes) / sizeof(test_sizes[0]); i++) {
		float* matrix1 = (float*)malloc(test_sizes[i] * 3 * sizeof(float));
		int* accelerations1 = (int*)malloc(test_sizes[i] * sizeof(int));
		double total_time = 0.0;

		for (int j = 0; j < 30; j++) { //30 iterations/runs
			generate_input(matrix1, test_sizes[i]);

			clock_t start_time = clock();
			calc_accelerations(matrix1, accelerations1, test_sizes[i]);
			clock_t end_time = clock();

			total_time += (double)(end_time - start_time) / CLOCKS_PER_SEC;
		}

		printf("Average time for %d cars(Y): %.6f seconds\n", test_sizes[i], total_time / 30);
		
		free(matrix1);
		free(accelerations1);
	}


	return 0;
}