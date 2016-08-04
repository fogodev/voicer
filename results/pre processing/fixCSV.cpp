#include <stdio.h>
int main(){
	double number;
	int counter = 0;
	printf("time, original\n");
	while(scanf("%lf", &number) != EOF){
		printf("%d, %lf\n", counter, number);
		counter++;
	}
	return 0;
}