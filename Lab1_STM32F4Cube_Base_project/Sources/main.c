#include <stdio.h>
#include "arm_math.h"

typedef struct kalman_state{
	arm_matrix_instance_f32 q; 
	arm_matrix_instance_f32 r;
	arm_matrix_instance_f32 x;
	arm_matrix_instance_f32 p;
	arm_matrix_instance_f32 k;
	arm_matrix_instance_f32 f;
	arm_matrix_instance_f32 h;
} kalman_state;

#define LEN 10
#define I 1

extern void kalman_asm(float *input, float* kda, int arrLen, kalman_state *ptr); //

int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int Length, int State_dimension, int Measurement_dimension);

int main() {
	float input[] = {0.1, 2.2, -0.1, 3.5, 4.0, 4.1, 9.9, 0.0, 0.0, 2.3}; //input	
	float kda[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //out
	int state_dimension = 3; //we'll refer to this as m
	int measurement_dimension = 2; //we'll refer to this as n					//TODO: add check that m>=n
	
//kalman_state initializations
	struct kalman_state ks;
	
	//q (m x 1)
	float q_data[] = {0.1, 0.1, 0.1};
	arm_matrix_instance_f32 q = {state_dimension, state_dimension, q_data};
	ks.q = q;
	
	//r (n x n)
	float r_data[] = {0.1, 0.1, 0.1, 0.1};
	arm_matrix_instance_f32 r = {state_dimension, state_dimension, r_data};
	ks.r = r;
	
	//x (m x 1)
	float x_data[] = {0.0, 0.0, 0.0};
	arm_matrix_instance_f32 x = {state_dimension, state_dimension, x_data};
	ks.x = x;
	
	//p (m x m)
	float p_data[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
	arm_matrix_instance_f32 p = {state_dimension, state_dimension, p_data};
	ks.p = p;
	
	//k (m x n)
	float k_data[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	arm_matrix_instance_f32 k = {state_dimension, state_dimension, k_data};
	ks.k = k;
	
	//f	(m x m)
	float f_data[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}; //this is a 3x3 I matrix
	arm_matrix_instance_f32 f = {state_dimension, state_dimension, f_data}; //TODO: add a check that dimensions of f match up with given state_dimension
	ks.f = f;
	
	//h (n x m)
	float h_data[] = {1.2, 0.0, 0.0, 1.2, 0.0, 0.0};
	arm_matrix_instance_f32 h = {measurement_dimension, state_dimension, h_data}; //TODO: add a check that dimensions of f match up with given state_dimension
	ks.h = h;
	
	
	Kalmanfilter_C(input, kda, &ks, LEN, state_dimension, measurement_dimension);
	return 0;
}

int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int Length, int State_dimension, int Measurement_dimension) {
	
	//initialize x_predict matrix
	float x_predict_data[State_dimension]; //(m x 1)
	arm_matrix_instance_f32 x_predict = {State_dimension, 1.0, x_predict_data};
	
	//initialize p_predict matrix
	float p_predict_data[State_dimension * State_dimension]; //(m x m)
	arm_matrix_instance_f32 p_predict = {State_dimension, 1.0, x_predict_data};
	
	//initialize temp_n_x_m
	float temp_n_x_m_data[Measurement_dimension * State_dimension];
	arm_matrix_instance_f32 temp_n_x_m = {Measurement_dimension, State_dimension, temp_n_x_m_data};
	
	//initialize temp_n_x_n
	float temp_n_x_n_data[Measurement_dimension * Measurement_dimension];
	arm_matrix_instance_f32 temp_n_x_n = {Measurement_dimension, Measurement_dimension, temp_n_x_n_data};
	
	//initialize temp_m_x_n
	float temp_m_x_n_data[State_dimension * Measurement_dimension];
	arm_matrix_instance_f32 temp_m_x_n = {State_dimension, Measurement_dimension, temp_m_x_n_data};
	
	//initialize temp_m_x_m_1
	float temp_m_x_m_data_1[State_dimension * State_dimension];
	arm_matrix_instance_f32 temp_m_x_m_1 = {State_dimension, State_dimension, temp_m_x_m_data_1};
		
	//initialize temp_m_x_m_2
	float temp_m_x_m_data_2[State_dimension * State_dimension];
	arm_matrix_instance_f32 temp_m_x_m_2 = {State_dimension, State_dimension, temp_m_x_m_data_2};
	
	//initialize f_transpose
	float f_transpose_data[State_dimension * State_dimension];
	arm_matrix_instance_f32 f_transpose = {State_dimension, State_dimension, f_transpose_data};
	//calculate f_transpose
	arm_mat_trans_f32(&kstate->f, &f_transpose);
	
	//initialize I
	float i_matrix_data[State_dimension * State_dimension]; //(m x m)
	int j;
	int temp = State_dimension + 1;
	for (j = 0; j < State_dimension; j++){ //build I based on m
		if ((j % temp) == 0){
			i_matrix_data[j] = 1.0;
		}
		else{
			i_matrix_data[j] = 0.0;
		}
		printf("%f, ", i_matrix_data[j]);
	}
	
	
	arm_matrix_instance_f32 i_matrix = {State_dimension, State_dimension, i_matrix_data};
		
	int i;
	
	for(i = 0; i < Length; i++) {		
		// Eq'1
		arm_mat_mult_f32(&kstate->f, &kstate->x, &x_predict);
		// x_predict = F * x;
		
		// Eq'2
		arm_mat_mult_f32(&kstate->f, &kstate->p, &temp_m_x_m_1); 			//temp1 = F * P
		arm_mat_mult_f32(&temp_m_x_m_1, &f_transpose, &temp_m_x_m_2);	//temp2 = temp1 * F^T
		arm_mat_add_f32(&temp_m_x_m_2, &kstate->q, &p_predict);				//p_predict = temp2 + Q
		//p_predict = F * P * F^t + Q
		
		// Eq'3
//		kstate->k = p_predict * H^T * (H * p_predict * H^T + R)
		
		// Eq'4
//		kstate->p = (I - kstate->k * kstate->h) * p_predict;
		
		// Update x
//		kstate->x = x_predict + kstate->k * (InputArray[i] - kstate->h * x_predict);
		
		// Eq'5
//		OutputArray[i] = kstate->x;
		
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
