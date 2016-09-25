#include <stdio.h>

typedef struct kalman_state{
	float q;
	float r;
	float x;
	float p;
	float k;
	float f;
	float h;
} kalman_state;


#define Q_INIT 0.1
#define R_INIT 0.1
#define X_INIT 0.0
#define P_INIT 0.1
#define K_INIT 0.0
#define F_INIT 0.8
#define H_INIT 1.2
#define LEN 10

#define I 1


extern void kalman_asm(float *input, float* kda, int arrLen, kalman_state *ptr); //

int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int Length);

int main() {
	float input[] = {0.1, 2.2, -0.1, 3.5, 4.0, 4.1, 9.9, 0.0, 0.0, 2.3}; //input	
	float kda[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //out
	kalman_state ks;
	
	Kalmanfilter_C(input, kda, &ks, LEN);
	return 0;
}

int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int Length) {
	
	// set state
	kstate->q = Q_INIT;
	kstate->r = R_INIT;
	kstate->x = X_INIT;
	kstate->p = P_INIT;
	kstate->k = K_INIT;
	kstate->f = F_INIT;
	kstate->h = H_INIT;
	
		
	float pOld, xOld;
	int i;
	
	for(i = 0; i < Length; i++) {
		// Set pOld
		pOld = kstate->p;
		xOld = kstate->x;
		
		// Eq'1
		kstate->x = kstate->f * xOld;
		
		// Eq'2
		kstate->p = kstate->f * kstate->f * pOld + kstate->q;
		
		// Eq'3
		kstate->k = (pOld * kstate->h) / (kstate->h * kstate->h * kstate->p + kstate->r);
		
		// Eq'4
		kstate->p = (I - kstate->k * kstate->h) * kstate->p;
		
		// Eq'5
		OutputArray[i] = kstate->x + kstate->k * (InputArray[i] - kstate->h * kstate->x);

		printf("%f\n",OutputArray[i]);
	}
	
	return 0;
}























/*int main()
{
	float input[] = {0.1, 2.2, -0.1, 3.5, 4.0, 4.1, 9.9, 0.0, 0.0, 2.3};//input
	
	float kda[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};//out
	int arrLength = 10;
	
	struct kalman_state myKfs;
	myKfs.q = 0.1;
	myKfs.r = 0.1;
	myKfs.x = 0.0;
	myKfs.p = 0.1;
	myKfs.k = 0.0;
	myKfs.f = 0.8;
	myKfs.h = 1.2;
	
	
	kalman_asm(input, kda, arrLength, &myKfs);
	//for loop
	int i;
	for(i= 0; i < arrLength; i++) {
		printf("%f\n", kda[i]);
	}

	return 0;
}*/
