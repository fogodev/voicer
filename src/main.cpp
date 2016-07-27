#include "../include/WiSARD.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "kernelCanvas.hpp"

#define RESAMPLING_SIZE 32
#define PRECISION 8
#define RETINA_LENGTH (RESAMPLING_SIZE * PRECISION)
#define NUM_BITS_ADDR 2

double* readInputFromFile(std::string path, int* inputSize) {
  double *inputValues;
  double value;
  std::ifstream file (path);

  file >> *inputSize;

  inputValues = (double *) malloc(*inputSize * sizeof(double));
  for (int i = 0 ; i < *inputSize ; i++) {
    file >> inputValues[i];
  }

  file.close();
  return inputValues;
}

std::vector<int> buildRetinaFromFile(std::string path, int resamplingSize, int precision) {
  int inputSize;
  double* inputValues;
  double* resampledValues;
  int* discreteValues;
  int** retina;
  int zeroIndex = precision/2;

  std::vector<int> retinaVector;

  inputValues = readInputFromFile(path, &inputSize);

  // allocate memory for the intermediate arrays
	resampledValues = (double *) malloc(resamplingSize * sizeof(double));
	discreteValues = (int *) malloc(resamplingSize * sizeof(int));
	retina = (int**) malloc(precision * sizeof(int*));

  for(int i = 0; i < precision; i++){
		retina[i] = (int*) malloc(resamplingSize * sizeof(int));
	}

  //Do intermediate steps to build retina matrix
  temporalResampling(inputSize, inputValues, resamplingSize, resampledValues);
  zeroIndex = thermometerDiscretization(resamplingSize, resampledValues, discreteValues, precision, 0, 0);
  buildRetina(resamplingSize, discreteValues, precision, retina, zeroIndex);

  //Converts retina matrix into a vector
  for (int i = 0 ; i < precision ; i++) {
    for (int j = 0 ; j < resamplingSize ; j++) {
      retinaVector.push_back(retina[i][j]);
    }
  }

  // Free all arrays used in the process
  free(inputValues);
  free(resampledValues);
  free(discreteValues);
  for (int i = 0 ; i < precision ; i++) {
    free(retina[i]);
  }
  free(retina);

  return retinaVector;
}

// Initializes vectors with training data.
void getTrainingData(std::vector<std::vector<int>> &trainingSamples, std::vector<std::string> &trainingClasses) {
    trainingSamples.push_back(buildRetinaFromFile("genwavs/a_1.gw", RESAMPLING_SIZE, PRECISION));
    trainingSamples.push_back(buildRetinaFromFile("genwavs/a_2.gw", RESAMPLING_SIZE, PRECISION));
    trainingSamples.push_back(buildRetinaFromFile("genwavs/b_1.gw", RESAMPLING_SIZE, PRECISION));
    trainingSamples.push_back(buildRetinaFromFile("genwavs/b_2.gw", RESAMPLING_SIZE, PRECISION));

    trainingClasses = {"a", "a", "b", "b"};
}

// Initializes the samples vector with the samples for prediction
void getSamples(std::vector<std::vector<int>> &samples) {
    samples.push_back(buildRetinaFromFile("genwavs/a_3.gw", RESAMPLING_SIZE, PRECISION)); // a
    samples.push_back(buildRetinaFromFile("genwavs/b_3.gw", RESAMPLING_SIZE, PRECISION)); // b
}

void printResults(std::vector<std::string> results) {
    std::cout << "Results:";

    for (std::vector<std::string>::iterator it = results.begin(); it != results.end() ; ++it) {
        std::cout << " " << *it;
    }

    std::cout << std::endl;
}

int main(int argc, char **argv) {
    // Training data
    std::vector<std::vector<int>> trainingSamples;
    std::vector<std::string> trainingClasses;

    // Actual samples for preditcion
    std::vector<std::vector<int>> samples;

    wann::WiSARD *wisard = new wann::WiSARD(RETINA_LENGTH, NUM_BITS_ADDR);

    // Train
    getTrainingData(trainingSamples, trainingClasses);
    wisard->fit(trainingSamples, trainingClasses);

    // Predict
    getSamples(samples);
    std::vector<std::string> results = wisard->predict(samples);

    // Print results
    printResults(results);

    return 0;
}
