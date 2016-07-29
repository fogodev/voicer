#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

int main(int argc, char** argv){
	
	ifstream inputFile;
	ofstream outputFile;
	string buffer;

	int size;
	double sampleRate;
	
	if(argc < 2){
		cerr << "ERROR: Usage " << argv[0] << " <filename> " << endl;
		return 1;
	}
	
	inputFile.open(argv[1]);
	outputFile.open(strcat(argv[1], ".csv"));
	
	if(inputFile.is_open()){
		inputFile >> buffer;
		size = stoi(buffer);
		inputFile >> buffer;
		sampleRate = stod(buffer);
		
		outputFile << "x, y" << endl;

		int cont = 0;
		while(!inputFile.eof()){
			inputFile >> buffer;
			outputFile << sampleRate * cont << "," << buffer << endl;
			cont++;
		}
	}	
	
	inputFile.close();
	outputFile.close();
	
	
	return 0;
}
