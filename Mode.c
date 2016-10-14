#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int mode;

float calcMode(int passed[] , float size){
	if(size == 0){
		printf("%s\n","Empty array, there can be no mode");
	}
	if(size == 1){
		mode = passed[0];
	}
	else{
		int i, j;
		float temp;	
		for(i=0; i<size-1; i++) 
		{
    	    for(j=i+1; j<size; j++) 
			{
    	        if(passed[j] < passed[i]) 
				{
    	            // swap 
    	            temp = passed[i];
    	            passed[i] = passed[j];
    	            passed[j] = temp;
    	        }
    	    }
    	}
		//Array sorted
		int number = passed[0];
		mode = number;
		int count = 1;
		int countMode = 1;

		for(int i = 1; i < size; i++)
		{
			if(passed[i] == number)
			{				
				count++;
			}
			else
			{
				if(count > countMode)
				{
					countMode = count;
					mode = number;
				}
				count = 1;
				number = passed[i];
			}	
		}
		//printf("mode : %d\n", mode);
		
	}

	return mode;

	/*
	//Exit codes 1,0,-1
	if(mode > 0){
		return 1;
	}	
	else if(mode == 0){
		return 0;
	}
	else if(mode < 0){
		return -1;
	}
	else{
		printf("%s\n", "Mode was not positive, negative ro zero");
		return -10;
	}*/

}

int main(int argc, const char* argv[]){
	pid_t parentPid = atoi(argv[2]);
	int readBuffer;
	read(parentPid, &readBuffer, sizeof(readBuffer));
    double *data = shmat(readBuffer, NULL, 0);
	printf("Mode Process [%d]: Starting.\n", getpid());		

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
	float result = calcMode(A,n);
	data[0] = result;
	printf("Mode: Process [%d]:  Mode is %d.\n", getpid(), mode);	
	printf("Mode: Process [%d]: Stopping.\n", getpid());	

	
	return result;
}
