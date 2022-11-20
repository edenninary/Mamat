// 123456789
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hist(int *bins,FILE *f,int nbins);

int main(int argc, char **argv) {

	FILE *f;
	int nbins=0;
	f = stdin;
	
	for(int i=1; i<argc; ++i){
		if(!strcmp(argv[i], "-")){
			f = stdin;
		}
		else if (!strcmp(argv[i], "-n_bins")){
			nbins = i<argc-1 ? atoi(argv[i+1]) : 10;
			i++;
		} 
		else{
			f = fopen(argv[i], "r");
		}
	}
	
	if(!f){
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
		return 1;
	}
	int *bins = (int*)malloc(sizeof(int)*nbins);
	for( int i=0; i<nbins; ++i){
		bins[i]=0;
	}
	hist(bins,f,nbins);
	free(bins);

}


void hist(int *bins, FILE *f, int nbins) {
	int grade;
	int getscan;
	int linen = 0;
	double leg =0;
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
		int curnum = (grade == 100) ? 99/(100/nbins) : grade/(100/nbins);
		bins[curnum]++;
		linen++;
	}
	leg = 100.0/nbins;
	for(int i=0; i<nbins; ++i){
		printf("%.0lf-%.0lf\t%d\n",i*leg,((i+1)*leg-1 == 99) ? 100 : (i+1)*leg-1,bins[i]);
	}

}
