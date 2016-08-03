#include <stdio.h>
#include <stdlib.h>
#include <cmath>

void printArray(int size, double* array){
	for(int i = 0; i < size; i++){
		printf("%lf\n", array[i]);
	}
}

void printIntArray(int size, int* array){
	for(int i = 0; i < size; i++){
		printf("%d\n", array[i]);
	}
}

void printMatrix(int x, int y, int** matrix){
	int i = 0, j = 0;
	for(i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

vector<double> mult(vector<double> vec, double scalar){
	for(int i = 0; i < vec.size(); i++){
		vec[i] *= scalar;
	}
	return vec;
}

vector<double> add(vector<double> v1, vector<double> v2){
	vector<double> res;
	for(int i = 0; i < v1.size(); i++){
		res = v1[i] + v2[i];
	}
	return res;
}

vector<vector<double>> temporalResampling(int size, const vector<vector<double>>& input, int newSize){
	vector<vector<double>> resampled(newSize);
	//The nearest previous and next indexes to the resampled point.
	int prev, next;
	//Percentage of the completion of the interpolation from prev to next.
	double interpolationStep;
	
	//Calculates the new values for the resampled vector
	for (int i = 0; i < newSize; ++i){
		//Calculates where the new point fits on the original scale
		// Ex:  |-------o-------|
		//               \    The upper point is on the resampled scale.
		//                \   It will obtain its value based on where
		//                 \  it fits on the original scale.
		//      |-----------o-----------|
		//Note: this isn't actually the interpolationStep yet.
		//Keep reading for further information.
		interpolationStep = (((1.0*size - 1)/(1.0*newSize - 1) * i));

		//Calculates the nearest index of the original vector previous
		//to the resampled point converted to the original scale.
		prev = floor(interpolationStep);
		
		//Calculates the point imediately next to prev in the original vector.
		//We can guarantee that our resampled point is between prev and next.
		next = prev + 1;
		
		//Finishes the interpolation step calculation.
		//We're interested solely on the values after the decimal point,
		//as we'll use them as percentages later on.
		interpolationStep -= prev;

		//Makes sure we don't go beyond the vector's limits.
		if(next >= size){
			resampled[i].push_back( input[size - 1] );
		}
		else{
			//Assigns the linear interpolation of prev and next with
			//interpolationStep percentage of completion to our resampled point.
			//resampled[i] = (1 - interpolationStep) * input[prev] + interpolationStep * input[next];	
			resampled[i].push_back( add(mult(input[prev], (1 - interpolationStep)) , mult(input[next], interpolationStep)) );

		}
	}
	return resampled;
}

vector<int> nDimensionalThermometer(const vector<vector<double>>& values, int precision, int maxVal, int minVal ){
	vector<int> result;
	int fillBits = 0;
	double range = maxVal - minVal;
	for(int i = 0; i < values.size(); i++){
		for(int j = 0; j < values[i].size(); j++){
			fillBits = ((values[i][j] - minValue)/range * (precision + 1));
			//Finish this	
		}
	}
}

int thermometerDiscretization(int size, double* values, int* discreteValues, int precision, int _maxVal, int _minVal){
	double maxVal = _maxVal, minVal = _minVal;
	int maxThermometerVal = precision/2;
	int i = 0;
	//Calculates the maximum value within the resampled values.
	//Note: Remove this initial for loop once the _maxVal and _minVal are fixed.
	if(_maxVal == 0 && _minVal == 0){
		for(i = 0; i < size; i++){
	
			if(i == 0){
				maxVal = values[i];
				minVal = values[i];
			}
			else{
				if(values[i] > maxVal){
					maxVal = values[i];
				}
				if(values[i] < minVal){
					minVal = values[i];
				}	
			}
			
		}
	}
	//Calculates the correponding discrete value based on global maximum,
	//minimum and the precision of the thermometer.
	for(i = 0; i < size; i++){
		discreteValues[i] = round(values[i]/(maxVal-minVal) * (precision));
		if(maxThermometerVal < discreteValues[i]){
			maxThermometerVal = discreteValues[i];
		}
		
	}
	return maxThermometerVal;
}

void buildRetina(int size, int* discreteValues, int precision, int** retina, int startingValue){
	int i = 0, j = 0;
	for(i = 0; i < precision; i++){
		for(j = 0; j < size; j++){
			retina[i][j] = 0;
		}
	}
	for(i = 0; i < size; i++){
		if(discreteValues[i] > 0){
			for(j = startingValue - 1; j >= startingValue - discreteValues[i]; j--){
				retina[j][i] = 1;
			}
		}
		else if(discreteValues[i] < 0){
			for(j = startingValue; j < startingValue - discreteValues[i]; j++){
				retina[j][i] = 1;
			}
		}
	}
}
/*
int main(int argc, char** argv){
	int inputSize, newSize = 20;
	double* inputValues;
	double* resampledValues;
	int* discreteValues;
	int precision = 8;
	int** retina;
	int i = 0;
	int zeroIndex = precision/2;

	if(argc < 3){
		printf("ERROR: No resampling size set or no thermometer precision set.\n");
		exit(-1);
	}
	else{
		newSize = atoi(argv[1]);
		precision = atoi(argv[2]);
	}

	scanf("%d", &inputSize);
	inputValues = (double *) malloc(inputSize * sizeof(double));
	resampledValues = (double *) malloc(newSize * sizeof(double));
	discreteValues = (int *) malloc(newSize * sizeof(int));
	retina = (int**) malloc(precision * sizeof(int*));

	for(i = 0; i < precision; i++){
		retina[i] = (int*) malloc(newSize * sizeof(int));
	}

	for (i = 0; i < inputSize; i++){
		scanf("%lf", &(inputValues[i]));
	}

	
	temporalResampling(inputSize, inputValues, newSize, resampledValues);
	zeroIndex = thermometerDiscretization(newSize, resampledValues, discreteValues, precision, 0, 0);
	buildRetina(newSize, discreteValues, precision, retina, zeroIndex);

	printf("Original input:\n");
	printArray(inputSize, inputValues);
	printf("\nResampled values:\n");
	printArray(newSize, resampledValues);
	printf("\nDiscrete values:\n");
	printIntArray(newSize, discreteValues);
	printf("Retina:\n");
	printMatrix(precision, newSize, retina);

	return 0;
}
*/
