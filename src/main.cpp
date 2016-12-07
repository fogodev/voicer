#include "../include/WiSARD.hpp"
#include "../include/PreProcessing.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "kernelCanvas.hpp"

#define KERNEL_AMOUNT 1024
#define NUM_BITS_ADDR 3

#define INVALID_FILE "Invalid filename"

using namespace voicer;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::vector<std::vector<double>> getKernelsFromFile(std::string path){
  int size, length;
  std::vector<std::vector<double>> kernels;
  std::ifstream file (path);
  if(!file.is_open()) {
    printf("ERROR: Invalid or no kernel file chosen\n");
    return kernels;
  }

  file >> size;
  kernels.resize(size);
  file >> length;
  for(int i = 0; i < kernels.size(); i++){
    for(int j = 0; j < length; j++){
      file >> kernels[i][j];
    }
  }
  return kernels;

}

std::vector<int> buildRetinaFromFile(std::string path, std::vector<std::vector<double>>& kernels, int kernelsAmount) {
  int inputSize;
  vector<vector<double>> inputValues;
  int** retina;

  std::vector<int> retinaVector;

  PreProcessing p;
  vector<vector<double>> processedAudio = p.loadAudioFile(path);
  // for(int i = 0; i < processedAudio.size(); i++){
  //   for(int j = 0; j < processedAudio[i].size(); j++){
  //     printf("%lf ", processedAudio[i][j]);
  //   }
  //   printf("\n");
  // }

  retinaVector = kernelCanvas(processedAudio, kernels, kernelsAmount);

  return retinaVector;
}

// Initializes vectors with training data.
void getTrainingData(std::string trainingDataPath, std::vector<std::vector<int>> &trainingSamples, std::vector<std::string> &trainingClasses, std::vector<std::vector<double>>& kernels) {
    std::ifstream file (trainingDataPath);
    std::string line;

    if (!file.is_open()) {
      throw INVALID_FILE;
    }

    while (std::getline(file, line)) {
      std::vector<std::string> tokens = split(line, ' ');

      trainingSamples.push_back(buildRetinaFromFile(tokens[0], kernels, KERNEL_AMOUNT));
      trainingClasses.push_back(tokens[1]);
    }

    file.close();
}

// Initializes the samples vector with the samples for prediction
bool getSamples(std::vector<std::vector<int>> &samples, std::vector<std::vector<double>>& kernels) {
    std::string path;

    std::cout << "Enter file for prediction (-q to exit)" << std::endl;
    std::cin >> path;

    if (path.compare("-q")) {
      samples.push_back(buildRetinaFromFile(path, kernels, KERNEL_AMOUNT));
    } else {
      return false;
    }

    return true;
}

void printResults(std::vector<std::string> results) {
    std::cout << "Results:";

    for (std::vector<std::string>::iterator it = results.begin(); it != results.end() ; ++it) {
        std::cout << " " << *it;
    }

    std::cout << std::endl;
}

void printVec(std::vector<std::vector<double>> vec){
  for (int i = 0; i < vec.size(); i++){
    for (int j = 0; j < vec[j].size(); j++){
      printf("%lf ", vec[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {

    //Training data
    std::string trainingDataPath;
    std::vector<std::vector<int>> trainingSamples;
    std::vector<std::string> trainingClasses;
    std::vector<std::vector<double>> kernels;
    

    // get training data path from the argument
    if (argc > 1) {
      trainingDataPath = argv[1];
    }

    if(argc > 2){
      kernels = getKernelsFromFile(argv[2]);
      printf("Kernels read from file.\n");
      printf("%lu\n", kernels.size());
      printf("%lu\n", kernels[0].size());
      printVec(kernels);
    }

    // Actual samples for preditcion
    std::vector<std::vector<int>> samples;

    /*********************************************************************
     *******************    WiSARD constructor call    *******************
     *********************************************************************/
     wann::WiSARD *wisard = new wann::WiSARD(KERNEL_AMOUNT, NUM_BITS_ADDR);
    /*********************************************************************
     *********************************************************************
     *********************************************************************/


    // Train
    try {
      getTrainingData(trainingDataPath, trainingSamples, trainingClasses, kernels);
    } catch (const char* exception) {
      std::cerr << exception << " (training data)"<<  std::endl;
      return 1;
    }

    wisard->fit(trainingSamples, trainingClasses);

    // Predict
    while (true) {
      try {
        if (!getSamples(samples, kernels)) {
          break;
        }
      } catch (const char* exception) {
        std::cerr << exception <<  std::endl;
        continue;
      }

      std::vector<std::string> results = wisard->predict(samples);

      // Print results
      printResults(results);
      std::cout << std::endl;

      samples.clear();
    }

    return 0;
}
