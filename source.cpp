#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <sys/time.h>

int operations = 0;

void mergeSort(std::vector<double>&);
void merge(std::vector<double>&, std::vector<double>&, std::vector<double>&);
double randomDouble(double, double);
void printArray(std::vector<double>);

int main() {
	
	//omp_set_num_threads(1);
	
	std::cout << "==================== Merge Sort Algorithm ==================" << std::endl;

	int sizeOfArray;
	std::cout << "Input size of the array : ";
	std::cin >> sizeOfArray;

	std::vector<double> mainArray(sizeOfArray);

	double minValue, maxValue;


	std::cout << "\n======================================" << std::endl;
	std::cout << "Define the range of the values to generate \n" << std::endl;

	std::cout << "Input the minimum of the domain : ";
	std::cin >> minValue;

	std::cout << "Input the maximum of the domain : ";
	std::cin >> maxValue;

	std::cout << "\n======================================" << std::endl;
	std::cout << "The Array will be filled by data between " << minValue << " and " << maxValue << " !" << std::endl;

	//double elementToPush;

	for (int i = 0; i < (int)mainArray.size(); i++)
		mainArray[i] = (double)roundf(randomDouble(minValue, maxValue) * 100) / 100;
/*
	std::cout << "\n======================================" << std::endl;
	std::cout << "The unsorted Array : " << std::endl;
	printArray(mainArray);
*/
	//clock_t startTime, finishTime;
	//startTime = clock();
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	mergeSort(mainArray);

	gettimeofday(&end, NULL);

	float seconds = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

//	finishTime = clock();
//	float diff = (float)finishTime - (float)startTime;
//	float seconds = diff / CLOCKS_PER_SEC;
/*
	std::cout << "\n======================================" << std::endl;
	std::cout << "The sorted Array : " << std::endl;
	printArray(mainArray);

	std::cout << "\n======================================" << std::endl;
*/
	std::cout << "\n======================================" << std::endl;
	std::cout << operations << " operations were made in " << seconds << " seconds" << std::endl;

	return 0;
}

void merge(std::vector<double>& mainArray, std::vector<double>& rightArray, std::vector<double>& leftArray) {
	int mainIndex = 0, rightIndex = 0, leftIndex = 0;

	while (leftIndex < (int)leftArray.size() && rightIndex < (int)rightArray.size()) {
		if (leftArray[leftIndex] < rightArray[rightIndex]) {
			mainArray[mainIndex] = leftArray[leftIndex];
			leftIndex++;
			operations++;
		}
		else {
			mainArray[mainIndex] = rightArray[rightIndex];
			rightIndex++;
			operations++;
		}
		mainIndex++;
	}

	while (leftIndex < (int)leftArray.size()) {
		mainArray[mainIndex] = leftArray[leftIndex];
		mainIndex++;
		leftIndex++;
		operations++;
	}

	while (rightIndex < (int)rightArray.size()) {
		mainArray[mainIndex] = rightArray[rightIndex];
		mainIndex++;
		rightIndex++;
		operations++;
	}
}

void mergeSort(std::vector<double>& mainArray) {
	if (mainArray.size() < 2)
		return;

	else {
		int middle = mainArray.size() / 2;

		std::vector<double> leftArray(middle);
		std::vector<double> rightArray(mainArray.size() - middle);

//#pragma omp parallel for
		for (int i = 0; i < middle; i++)
			leftArray[i] = mainArray[i];

//#pragma omp parallel for
		for (int i = middle; i < (int)mainArray.size(); i++)
			rightArray[i - middle] = mainArray[i];

#pragma omp parallel {
#pragma omp single {
#pragma omp task 
			mergeSort(leftArray);

#pragma omp task
			mergeSort(rightArray);
#pragma omp taskwait
//#pragma omp task
			merge(mainArray, rightArray, leftArray);
}
}

	}
}

double randomDouble(double minValue, double maxValue) {
	double random = (double)((double)rand() / (double)RAND_MAX);
	double difference = maxValue - minValue;
	double finalRandom = random * difference;

	return (double)(minValue + finalRandom);
}

void printArray(std::vector<double> array) {
	std::cout << "\nPrinting the Array..." << std::endl;

#pragma omp parallel for
	for (int i = 0; i < (int)array.size(); i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}
