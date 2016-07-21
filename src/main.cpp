#include "../include/WiSARD.hpp"
#include <vector>
#include <iostream>

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
