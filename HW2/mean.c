// 123456789
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mean(FILE *f);

int main(int argc, char **argv) {

	FILE *f;

	if(argc == 1 || strcmp("-", argv[1])){
		f = stdin;
	}
	else {
		f = fopen(argv[1], "r");
	}
	if(!f){
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
		return 1;
	}
	mean(f);

}

void mean(FILE *f) {
	int grade;
	int getscan;
	double sum = 0;
	int linen = 0;

	while(1){
		getscan = fscanf(f,"%d",&grade);
		if (getscan == EOF){
			break;
		}
		else if (getscan != 1){
			fprintf(stderr, "Error: not a number on line %d\n",linen+1);
			exit(1);
		}
		else if (grade<0 || grade>100){
			fprintf(stderr, "Error: not a legal number on line %d\n",linen+1);
			exit(1);
		}
		sum += grade;
		linen++;
	}
	printf("%.2lf\n",(sum/linen));



}
