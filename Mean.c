#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

float mean;

float calcMean(int passed[] , int size){
		
	float sum;	
	
	for(int i = 0; i <= size; i ++){
		sum += passed[i];
	}
	
	mean = (sum)/(size); 
	return mean;	
	//printf("sum:%f\nmean:%f\nsize:%d\n", sum, mean, size);
	/*if(mean > 0){
		return 1;
	}	
	else if(mean == 0){
		return 0;
	}
	else if(mean < 0){
		return -1;
	}
	else{
		printf("%s\n", "Mean was not positive, negative ro zero");
		return -10;
	}*/
}

int main(int argc, const char* argv[]){
	//pipe stuff
	pid_t parentPid = atoi(argv[2]);
	int readBuffer;
	read(parentPid, &readBuffer, sizeof(readBuffer));
    printf("Initiator: wrote shm ID %d to pipe (4 bytes)\n", readBuffer);
    double *data = shmat(readBuffer, NULL, 0);
	

	printf("Mean Process [%d]: Starting.\n", parentPid);	

	int A[10];
	FILE *fp = fopen(argv[1], "r");
	int number;	

	int i = 0;	
	fscanf(fp, "%d", &number);
	while(!feof(fp))
	{
		A[i] = number;
		fscanf(fp, "%d", &number);
		i++;
	}	
	
	int n = sizeof(A) / sizeof(A[0]);
	float result = calcMean(A,n);
	data[0] = result;
	printf("Mean: Process [%d]:  Mean is %f.\n", parentPid, mean);	
	printf("Mean: Process [%d]: Stopping.\n", parentPid);	

	return 0;
;
}
