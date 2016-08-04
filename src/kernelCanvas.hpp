#ifndef __KERNELCANVAS_HPP_
#define __KERNELCANVAS_HPP_

void printArray(const vector<int>& array);

void printMatrix(const vector<vector<double>>& matrix);

double distance(const vector<double>& v1, const vector<double>& v2);

vector<vector<double>> generateKernels(int amount, int dimensions);

vector<vector<double>> smoothStroke(vector<vector<double>>& input, double minDistance);

vector<int> kernelCanvas(vector<vector<double>>& input, vector<vector<double>>& kernels, int kernelsAmount);

#endif
