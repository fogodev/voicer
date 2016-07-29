#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cmath>

void printArray(int size, double* array){
        for(int i = 0; i < size; i++){
                printf("%lf\n", array[i]);
        }
}

double f(double x, int f_sin=10, int f_cos=3){
        return cos(f_cos*x) + sin(f_sin*x);
}

double addNoise(double x, double intensity){
		double noise = rand()/((double)RAND_MAX);
		noise = noise - 0.5;
		noise *= 2 * intensity;
		if(x + noise > 2 || x - noise < -2){
			return x;
		}
		return x + noise;
}

int main (int argc, char** argv){
        double* amps;
        double sampleRate = 0.1;//in time units, should be named inverse of sampleRate. Default value, can be overwritten with an argument
        int size = 30; //default value, can be overwritten with an argument
        double f_sin = 10; //default value, ...
        double f_cos = 3;  //default value, ...
        double intensity = 0.1; //default value, ...

        if(argc < 6){
                printf("ERROR: Wrong number of parameters (size, sample period, f_sin, f_cos, intensity).\n");
                exit(-1);
        }
        else{
                size = atoi(argv[1]);
        }

        if (argc > 2) {
                sampleRate = atof(argv[2]);
        }

        if (argc > 3) {
                f_sin = atof(argv[3]);
        }

        if (argc > 4) {
                f_cos = atof(argv[4]);
        }
	
        if (argc > 5){
		intensity = atof(argv[5]);
	}

        srand(time(NULL));
        amps = (double*) malloc(size * sizeof(double));

        for(int i = 0; i < size; i++){
                amps[i] = addNoise(f(i*sampleRate, f_sin, f_cos), intensity);
        }

        printf("%d\n", size);
        printf("%lf\n", sampleRate);
        printArray(size, amps);

        return 0;
}

