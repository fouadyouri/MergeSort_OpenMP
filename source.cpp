#include <iostream>
#include <vector>

int itterations = 0;

void mergeSort(std::vector<double>&);
void merge(std::vector<double>&, std::vector<double>&, std::vector<double>&);
double randomDouble(double, double);
void printArray(std::vector<double>);

int main() {
	std::cout << "==================== Merge Sort Algorithm ==================" << std::endl;

	int sizeOfArray;
	std::cout << "Input size of the array : ";
	std::cin >> sizeOfArray;

	std::vector<double> mainArray (sizeOfArray);
	
	double minValue,
		maxValue;


	std::cout << "\n======================================" << std::endl;
	std::cout << "Define the range of the values to generate \n" << std::endl;

	std::cout << "Input the minimum of the domain : ";
	std::cin >> minValue;

	std::cout << "Input the maximum of the domain : ";
	std::cin >> maxValue;

	std::cout << "\n======================================" << std::endl;
	std::cout << "The Array will be filled by data between " << minValue << " and " << maxValue << " !" << std::endl;

	double elementToPush;

#pragma omp parallel for
	for (int i = 0; i < mainArray.size(); i++)
		mainArray[i] = roundf(randomDouble(minValue, maxValue) * 100) / 100;

	std::cout << "\n======================================" << std::endl;
	std::cout << "The unsorted Array : " << std::endl;
	printArray(mainArray);


	mergeSort(mainArray);


	std::cout << "\n======================================" << std::endl;
	std::cout << "The sorted Array : " << std::endl;
	printArray(mainArray);
	

	std::cout << "\n======================================" << std::endl;


	std::cout << "\n======================================" << std::endl;
	std::cout << "Number of itterations : " << itterations << std::endl;

	return 0;
}

void merge(std::vector<double>& mainArray, std::vector<double>& rightArray, std::vector<double>& leftArray)
{
	int mainIndex = 0, 
		rightIndex = 0,
		leftIndex = 0;

	while (leftIndex < leftArray.size() && rightIndex < rightArray.size())
	{
		if (leftArray[leftIndex] < rightArray[rightIndex])
		{
			mainArray[mainIndex] = leftArray[leftIndex];
			leftIndex++;
			itterations++;
		}
		else
		{
			mainArray[mainIndex] = rightArray[rightIndex];
			rightIndex++;
			itterations++;
		}
		mainIndex++;
	}

	while (leftIndex < leftArray.size())
	{
		mainArray[mainIndex] = leftArray[leftIndex];
		mainIndex++;
		leftIndex++;
		itterations++;
	}

	while (rightIndex < rightArray.size())
	{
		mainArray[mainIndex] = rightArray[rightIndex];
		mainIndex++;
		rightIndex++;
		itterations++;
	}
}

void mergeSort(std::vector<double>& mainArray)
{
	if (mainArray.size() < 2)
		return;

	else
	{
		int middle = mainArray.size() / 2;

		std::vector<double> leftArray (middle);
		std::vector<double> rightArray (mainArray.size() - middle);

#pragma omp parallel for
		for (int i = 0; i < middle; i++)
			leftArray[i] = mainArray[i];

#pragma omp parallel for
		for (int i = middle; i < mainArray.size(); i++)
			rightArray[i - middle] = mainArray[i];

#pragma omp parallel 
		mergeSort(leftArray);

#pragma omp parallel
		mergeSort(rightArray);

#pragma omp parallel
		merge(mainArray, rightArray, leftArray);
	}

}

double randomDouble(double minValue, double maxValue)
{
	double random = ((double)rand() / (double)RAND_MAX);

	double difference = maxValue - minValue;

	double finalRandom = random * difference;

	return (double) (minValue + finalRandom);
}

void printArray(std::vector<double> array)
{
	std::cout << "\nPrinting the Array..." << std::endl;
	
#pragma omp parallel for
	for (int i = 0; i < array.size(); i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}
