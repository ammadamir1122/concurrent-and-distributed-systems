#include<stdio.h>
#include<pthread.h>

double A[SIZE][SIZE];
double B[SIZE][SIZE];
double C[SIZE][SIZE];
#define MAX_THREAD 4            //creating four threads

void* multi(void* arg){        //Function for Matrix Multiplication
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
	    for(int k = 0; k < SIZE; k++){
	        C[i][j] = C[i][j] + A[i][k] * B[k][j];
	    }
	}
    }
}




int main()
{
	int t, u;    		//intializing each and every matrix element to 1
	/* Input Data */
	for (t = 0; t < SIZE; t++) {
		for (u = 0; u < SIZE; u++) {
			A[t][u] = B[u][t] = 1;
		}
	}

	struct timespec start, finish;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);

	// declaring four threads
        pthread_t threads[MAX_THREAD];
  
        // Creating four threads, each evaluating its own part
        for (int i = 0; i < MAX_THREAD; i++) {
            int* p;
            pthread_create(&threads[i], NULL, multi, (void*)(p));
        }

	 // joining and waiting for all threads to complete
        for (int i = 0; i < MAX_THREAD; i++){
            pthread_join(threads[i], NULL);
        }

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed  = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0; 

	for (t = 0; t < SIZE; t++) {
		for (u = 0; u < SIZE; u++) {
			printf("%.0f ", C[t][u]);
		}
		printf("\n");
	}

	fprintf(stderr, "Time: %f s\n", elapsed);	// Do not modify this line
}

