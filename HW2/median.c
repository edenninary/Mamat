// 123456789
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void median(FILE *f);

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
	median(f);

}

void median(FILE *f) {
	int grade;
	int hist[101] = {0};
	int getscan;
	int linen = 0;
	int med_loc = 0;

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
		hist[grade]++;
		linen++;
	}
		
	med_loc = (linen+1)/2;	
	int i=0;
	while(0 < med_loc){
		med_loc = med_loc - hist[i];
		i++;
	}
	i--;
	if(linen%2!=0){
		while(hist[i]==0){
			i++;
		}
	}
	printf("%d\n",i);

}
