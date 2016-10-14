#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
float median = 0; 
float calcMedian(int passed[] , int size){
	
	//SORT THE ARRAY
	float temp;
    int i, j;
    // sort the array x in ascending order
    for(i=0; i<size-1; i++) {
        for(j=i+1; j<size; j++) {
            if(passed[j] < passed[i]) {
                // swap 
                temp = passed[i];
                passed[i] = passed[j];
                passed[j] = temp;
            }
        }
    }

	//Find Median
	float middle = 0;
	float secondMiddle = 0;
	int twoMids = 0;
	int location = size/2;

	middle = passed[location];
	int mod = size  % 2;
	if(mod == 0){				
		secondMiddle = passed[location-1];
		twoMids = 1;
	}	
	if(twoMids == 1){
		/*
		printf("middle:%f\n",middle);
		printf("2middle:%f\n",secondMiddle);
		printf("sum:%f\n",middle+secondMiddle);	
		*/
		median = (middle + secondMiddle)/2;
	}
	else{
		median = middle;
	}	

	return median;
	//printf("%f\n", median);
	
	/*
	//Return if it is +,-,0	
	if(median > 0){
		return 1;
	}	
	else if(median == 0){
		return 0;
	}
	else if(median < 0){
		return -1;
	}
	else{
		printf("%s\n", "Median was not positive, negative or zero");
		return -10;
	}*/

}

int main(int argc, const char* argv[]){
	pid_t parentPid = atoi(argv[2]);
	int readBuffer;
	read(parentPid, &readBuffer, sizeof(readBuffer));
    double *data = shmat(readBuffer, NULL, 0);
	printf("Median Process [%d]: Starting.\n", getpid());
	
	int A[10];
	FILE *fp = fopen(argv[1], "r");
	int number;	

	int i = 0;	
	fscanf(fp, "%d", &number);
	while(!feof(fp))
	{
		A[i] = number;
		fscanf(fp, "%d", &number);
		//printf("A[i]: %d\n", A[i]);
		i++;
	}
	int n = sizeof(A) / sizeof(A[0]);
	float result = calcMedian(A,n);
	data[0] = result;
	printf("Median: Process [%d]:  Median is %f.\n", getpid(), median);	
	printf("Median: Process [%d]: Stopping.\n", getpid());	
	//printf("%f\n", result);

	return 0;
}
