#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <time.h>

#define MIN_DIST 0.01

using namespace std;

void printArray( const vector<int>& array){
	for(int i = 0; i < array.size(); i++){
		printf("%d\n", array[i]);
	}
}

void printMatrix( const vector<vector<double>>& matrix){
	int i = 0, j = 0;
	for(i = 0; i < matrix.size(); i++){
		for(j = 0; j < matrix[i].size(); j++){
			printf("%lf, ", matrix[i][j]);
		}
		printf("\n");
	}
}

double distance(const vector<double>& v1, const vector<double>& v2){
	double dist = 0;
	int i = 0;
	for(i = 0; i < v1.size(); i++){
		dist += (v1[i] - v2[i]) * (v1[i] - v2[i]);
	}
	return sqrt(dist);
}

vector<vector<double>> generateKernels(int amount, int dimensions){
	vector<vector<double>> kernels(amount);
	for (int i = 0; i < amount; i++){
		kernels[i].resize(dimensions);
		for (int j = 0; j < dimensions; j++){
			kernels[i][j] = 2*(((double)rand() / RAND_MAX) - 0.5);
		}
	}
	return kernels;
}

vector<vector<double>> smoothStroke(const vector<vector<double>>& input, double minDistance){
	vector<vector<double>> smooth;
	vector<double> lastPoint = input[0];
	smooth.push_back(input[0]);
	for (int i = 1; i < input.size(); ++i){
		if(distance(lastPoint, input[i]) >= minDistance){
			smooth.push_back(input[i]);
		}
	}
	return smooth;
}

vector<int> kernelCanvas(vector<vector<double>>& input, vector<vector<double>>& kernels){
	if(kernels.size() == 0){
		kernels = generateKernels(input.size(), input[0].size());
	}
	kernels = smoothStroke(kernels, MIN_DIST);
	vector<int> canvas(input.size() * input[0].size(), 0.0);
	int closestKernel;
	double lastDistance, currentDistance;
	int i = 0, j = 0;

	for (i = 0; i < input.size(); ++i){
		closestKernel = 0;
		lastDistance = distance(input[i], kernels[0]);
		for(j = 1; j < kernels.size(); j++){
			currentDistance = distance(input[i], kernels[j]);
			if(currentDistance < lastDistance){
				lastDistance = currentDistance;
				closestKernel = j;
			}
		}
		canvas[closestKernel] = 1;
	}

	return canvas;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	vector<vector<double>> input = generateKernels(20, 3);
	vector<vector<double>> kernels = generateKernels(10, 3);

	vector<int> canvas = kernelCanvas(input, kernels);

	printf("Input\n");
	printMatrix(input);
	printf("Kernels\n");
	printMatrix(kernels);
	printf("Canvas\n");
	printArray(canvas);

	return 0;
}