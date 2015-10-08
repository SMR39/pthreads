/***********************************************************************************************
SGP ASSIGNMENT 3

matmult.c

A program to demonstrate matrix multiplication of 64*64 matrices using pthread


Authors : Ishan & Shashi

*************************************************************************************************/
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

int M1[64][64];
int M2[64][64];
int M3[64][64];

void *pthread_multiply (void *);

struct coord {
   int i; //Row
   int j; //Column
};

int main()
{
	int i,j,l,k=1,count=0;
	//First Matrix 
	for (i=0;i<64;i++)
	{
		for (j=0;j<64;j++)
		{
			M1[i][j]=k;
			k++;
		}
	}
	
	//Second Matrix
	i=0,j=0,k=1;
	for (i=0;i<64;i++)
	{
		for (j=0;j<64;j++)
		{
			M2[i][j]=k;
			k++;
		}
	}
	//Multiplying the two Matrices
	i=0,j=0,k=1;
	int sum=0;
	for (i=0;i<64;i++)
	{
		for (j=0;j<64;j++)
		{
			for (l=0;l<8;l++)
			{
			//Assign a row and column for each thread
         		struct coord *data = (struct coord *) malloc(sizeof(struct coord));
			data->i = i;
        		data->j = j;
         		pthread_t tid;       //Thread ID
        		pthread_attr_t attr; //Set of thread attributes
         		pthread_attr_init(&attr);
         		//Creating the thread
         		pthread_create(&tid,&attr,pthread_multiply,data);
         		//Parents wait for all thread to complete
         		pthread_join(tid, NULL);
			
			}
			
		}
	}
	printf("\nDisplaying multiplied matrices\n");
		i,j=0;
		for (i=0;i<64;i++)
		{
			for(j=0;j<64;j++)
			{				
				printf("%d",M3[i][j]);
				printf("\t");
			}
		printf("\n");
		}
	return 0;
}

void *pthread_multiply(void *para)
{
	struct coord *data = para;
	int num, sum = 0; 

  	//Row multiplied by column
  	for(num = 0; num< 64; num++)
	{
   	   sum += M1[data->i][num] * M2[num][data->j];
  	}
  	//assign the sum to its coordinate
   	M3[data->i][data->j] = sum;
   	//Exit the thread
   	pthread_exit(0);
}
