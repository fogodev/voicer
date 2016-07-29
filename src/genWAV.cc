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
		srand(time(NULL));
		double noise = rand()/((double)RAND_MAX);
		noise = noise - 1/2;
		noise *= 2 * intensity;
		if(x + noise > 2 || x - noise < -2){
			return x;
		}
		return x + noise;
}

int main (int argc, char** argv){
        double* amps;
        double sampleRate = 0.1;//in time units, should be named inverse of sampleRate
        int size = 30;
        int f_sin = 10; //default value, can be overwritten with an argument
        int f_cos = 3;  //default value, ...
		double intensity = 0.1;

        if(argc < 5){
                printf("ERROR: Wrong number of parameters. (size, f_sin, f_cos, intensity)\n");
                exit(-1);
        }
        else{
                size = atoi(argv[1]);
        }

        if (argc > 2) {
                f_sin = atoi(argv[2]);
        }

        if (argc > 3) {
                f_cos = atoi(argv[3]);
        }
		if (argc > 4){
				intensity = atof(argv[4]);
		}

        amps = (double*) malloc(size * sizeof(double));

        for(int i = 0; i < size; i++){
                amps[i] = addNoise(f(i*sampleRate, f_sin, f_cos), intensity);
        }

        printf("%d\n", size);
        printf("%lf\n", sampleRate);
        printArray(size, amps);

        return 0;
}

