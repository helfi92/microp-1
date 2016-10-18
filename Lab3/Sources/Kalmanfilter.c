#include <stdio.h>
#include "Kalmanfilter.h"


int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int Length) {		
	float x_predict, p_predict;
	int i;
	
	for(i = 0; i < Length; i++) {		
		// Eq'1
		x_predict = kstate->f * kstate->x;
		// kstate->x = kstate->f * xOld;
		
		// Eq'2
		p_predict = kstate->f * kstate->f * kstate->p + kstate->q;
		//kstate->p = kstate->f * kstate->f * x_predict + kstate->q;
		
		// Eq'3
		kstate->k = (p_predict * kstate->h) / (kstate->h * kstate->h * p_predict + kstate->r);
		
		// Eq'4
		kstate->p = (1 - kstate->k * kstate->h) * p_predict;
		
		// Update x
		kstate->x = x_predict + kstate->k * (InputArray[i] - kstate->h * x_predict);
		
		// Eq'5
		OutputArray[i] = kstate->x;
		
	}
	
	return 0;
}
