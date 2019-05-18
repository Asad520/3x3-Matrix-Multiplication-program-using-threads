#include <pthread.h>  // header file for threads
#include <stdio.h>   // header file for standard input and output.
#include <stdlib.h> // header file for functions involving memory allocation, process control, conversions and others
#include <unistd.h> //header file that provides access to the POSIX operating system API. (fork, pipe and I/O primitives [read, write, close, etc.] )
#include <errno.h>  //header file for error handling 
#include <math.h> //header file for math fast operations 


void * multiplyer (void *);  //prototype for function multiplyer

int a=0,b=0;
int times=0;
int* matrix1[3];
int* matrix2[3];
int* matrix3[3];

int main(int argc, char ** args)
{
	//fetching file path from commandline arguments
	
	char *file1_name = args[1];
	char *file2_name = args[2];
	
	FILE* fptr;
	FILE* fptr2;
	fptr=fopen(file1_name, "r");
	fptr2=fopen(file2_name, "r");

	for (int i = 0; i < 3; i++)
	{
		matrix1[i] = (int*)malloc(3 * sizeof(int));
		matrix2[i] = (int*)malloc(3 * sizeof(int));
		matrix3[i] = (int*)malloc(3 * sizeof(int));
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			fscanf(fptr, "%d", &matrix1[i][j]);
			fscanf(fptr2, "%d", &matrix2[i][j]);
		        matrix3[i][j]=0;
		}
	}
	fclose(fptr);
	fclose(fptr2);

	pthread_t tid[9];
	
	for (int itr = 0; itr < 9; itr++)
        {
		  pthread_create(&tid[itr], NULL, multiplyer, NULL);
	}

	for(int itr=0;itr<9;itr++) 
	{ 
	   pthread_join(tid[itr],NULL);
	}

	FILE* out = fopen("ans.txt", "w");
	puts("");
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			printf( "%d ", matrix3[i][j]);
			fprintf(out, "%d ", matrix3[i][j]);
		}
		printf("\n");
		fprintf(out, "\n");
	}
	fclose(out);

	printf("\nmain is ended \n");
	return 0;
}

void * multiplyer (void * arg)
{
	printf("\n executing thread # %d", times++ );
	
	for(int k=0;k<3;k++)
	{
		matrix3[a%3][b%3] += matrix1[a%3][k]*matrix2[k][b%3];
	}

	    b++;

	if(b%3==0)
	{
		a++;
	}
	return NULL;

}
