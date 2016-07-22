#include "../include/WiSARD.hpp"
#include <vector>
#include <iostream>
#include "kernelCanvas.hpp"

#define RETINA_LENGTH 8
#define NUM_BITS_ADDR 2

// Initializes vectors with training data.
void getTrainingData(std::vector<std::vector<int>> *trainingSamples, std::vector<std::string> *trainingClasses) {
    *trainingSamples = {{1, 1, 1, 1, 0, 0, 0, 0},
                        {0, 1, 1, 1, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 1, 1, 1},
                        {0, 0, 0, 0, 1, 1, 1, 0}};

    *trainingClasses = {"a", "a", "b", "b"};
}

// Initializes the samples vector with the samples for prediction
void getSamples(std::vector<std::vector<int>> *samples) {
    *samples = {{0, 0, 0, 0, 0, 1, 1, 1}, // b
                {1, 0, 1, 0, 0, 0, 0, 0}, // a
                {1, 0, 1, 1, 1, 0, 0, 0}, // a
                {0, 0, 0, 1, 1, 1, 1, 1}};// b
}

void printResults(std::vector<std::string> results) {
    std::cout << "Results:";

    for (std::vector<std::string>::iterator it = results.begin(); it != results.end() ; ++it) {
        std::cout << " " << *it;
    }

    std::cout << std::endl;
}

int main(int argc, char **argv) {

    //Kernel Canvas

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

    //WiSARD

    // Training data
    std::vector<std::vector<int>> trainingSamples;
    std::vector<std::string> trainingClasses;

    // Actual samples for preditcion
    std::vector<std::vector<int>> samples;

    wann::WiSARD *wisard = new wann::WiSARD(RETINA_LENGTH, NUM_BITS_ADDR);
    
    // Train
    getTrainingData(&trainingSamples, &trainingClasses);
    wisard->fit(trainingSamples, trainingClasses);

    // Predict
    getSamples(&samples);
    std::vector<std::string> results = wisard->predict(samples);
    
    // Print results
    printResults(results);

    return 0;
}

