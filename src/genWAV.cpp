#include <stdio.h>
#include <stdlib.h>
#include <cmath>

void printArray(int size, double* array){
	for(int i = 0; i < size; i++){
		printf("%lf\n", array[i]);
	}
}

double f(double x){
	return cos(3*x) + sin(10*x);
}

int main (int argc, char** argv){
	double* amps;
	double sampleRate = 0.1;//in time units, should be named inverse of sampleRate ¯\_(ツ)_/¯
	int size = 30;

	if(argc < 2){
		printf("ERROR: No number of samples set\n");
		exit(-1);
	}
	else{
		size = atoi(argv[1]);
	}

	amps = (double*) malloc(size * sizeof(double));

	for(int i = 0; i < size; i++){
		amps[i] = f(i*sampleRate);
	}

	printf("%d\n", size);
	printf("%lf\n", sampleRate);
	printArray(size, amps);

	return 0;
}