#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>


int main(int argc, const char* argv[]){
	////////////////////////////////////////////////Fork for Mean////////////////////////////////////////////////
	int status;
	
	// Create Pipe for child
    char meanStfd[20];
	int meanfd[2];
	pipe(meanfd);
	//
	 char medianStfd[20];
	int medianfd[2];
	pipe(medianfd);
	//
	char modeStfd[20];
	int modefd[2];
	pipe(modefd);
	//	
	pid_t meanPid;
	pid_t medianPid;
	pid_t modePid;
	meanPid = fork();
	
	float meanRead; 
	float medianRead;
	float modeRead; 	

	if(meanPid == 0)
	{		
		close(meanfd[1]);
      	sprintf(meanStfd, "%d", meanfd[0]);
		execlp("Mean", "Mean", "Nums.txt", meanStfd, NULL);
	}
	if(meanPid > 0)
	{
     	int sid = shmget(IPC_PRIVATE, sizeof(double), IPC_CREAT | 0666);		
		char stid[20];
        sprintf(stid, "%d", sid);
        write(meanfd[1], &sid, sizeof(sid));
		wait(NULL);
        double *data = (double *) shmat(sid, NULL, 0);
        meanRead = data[0];
        shmctl(sid, IPC_RMID, NULL);

		

		printf("Initiator: Forked process ID %d.\n", meanPid);
		//printf("Initiator: child process %d returned with %d.\n", meanPid, meanEs);
	}

	
	//////////////////////////////////////////////Fork For Median/////////////////////////////////////////////////	
	// Create Pipe for child
    /*char medianStfd[20];
	int medianfd[2];
	pipe(medianfd);
	
	pid_t medianPid = fork();*/
	if(meanPid > 0){
		medianPid = fork();
	}
	
	if(medianPid == 0)
	{
		close(medianfd[1]);
      	sprintf(medianStfd, "%d", medianfd[0]);
		execlp("Median", "Median", "Nums.txt", medianStfd, NULL);
	}
	if(medianPid > 0)
	{
		//Pipe stuff
		int sid = shmget(IPC_PRIVATE, sizeof(double), IPC_CREAT | 0666);		
		char stid[20];
        sprintf(stid, "%d", sid);
        write(medianfd[1], &sid, sizeof(sid));
		wait(NULL);
        double *data = (double *) shmat(sid, NULL, 0);
        medianRead = data[0];
        shmctl(sid, IPC_RMID, NULL);
		
		
		//Normal Stuff
		printf("Initiator: Forked process ID %d.\n", medianPid);
		
		//printf("Initiator: child process %d returned with %d.\n", medianPid, medianEs);
	}

	
	/////////////////////////////////////Fork For Mode//////////////////////////////////////////////////////////
	/*char modeStfd[20];
	int modefd[2];
	pipe(modefd);

	pid_t modePid = fork();*/

	if(meanPid > 0 && medianPid > 0){
		modePid = fork();
	}
	if(modePid == 0)
	{
		close(modefd[1]);
      	sprintf(modeStfd, "%d", modefd[0]);
		execlp("Mode", "Mode", "Nums.txt", modeStfd, NULL);
	}
	if(modePid > 0)
	{
		//Pipe stuff
		int sid = shmget(IPC_PRIVATE, sizeof(double), IPC_CREAT | 0666);		
		char stid[20];
        sprintf(stid, "%d", sid);
        write(modefd[1], &sid, sizeof(sid));
		wait(NULL);
        double *data = (double *) shmat(sid, NULL, 0);
        modeRead = data[0];
        shmctl(sid, IPC_RMID, NULL);		

		//Normal Stuff
		printf("Initiator: Forked process ID %d.\n", modePid);
		printf("Initiator: waiting for process [%d].\n", modePid);
		waitpid(modePid, &status, 0 );
		//printf("Initiator: child process %d returned with %d.\n", modePid, modeEs);
	}	
	
	//WAIT
	printf("Initiator: waiting for process [%d].\n", meanPid);
	waitpid(meanPid, &status, 0 );
	printf("Initiator: waiting for process [%d].\n", medianPid);
	waitpid(medianPid, &status, 0 );
	printf("Initiator: waiting for process [%d].\n", modePid);
	waitpid(modePid, &status, 0 );
	printf("Initiator: Result read from shared memory , Mean is %f\n", meanRead);
	printf("Initiator: Result read from shared memory , Median is %f\n", medianRead);
	printf("Initiator: Result read from shared memory , Mode is %f\n", modeRead);
	printf("Initiator: exiting.\n");	


	return 0;
}

