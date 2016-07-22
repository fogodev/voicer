#ifndef __KERNELCANVAS_HPP_
#define __KERNELCANVAS_HPP_

void printArray(int size, double* array);

void printIntArray(int size, int* array);

void printMatrix(int x, int y, int** matrix);

void temporalResampling(int size, double* input, int newSize, double* resampled);

int thermometerDiscretization(int size, double* values, int* discreteValues, int precision, int _maxVal, int _minVal);

void buildRetina(int size, int* discreteValues, int precision, int** retina, int startingValue);

#endif
