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
	float input[] = {0.1, 2.2, -0.1, 3.5, 4.0, 4.1, 9.9, 0.0, 0.0, 2.3}; //input [z_1, z_2, ..., z_w] (n x w)
	float kda[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //out [x_1, x,2, ..., x_w] (m x w)
	int state_dimension = 3; //we'll refer to this as m
	int measurement_dimension = 2; //we'll refer to this as n					//TODO: add check that m>=n
	//kalman_state initializations
	struct kalman_state ks;
	//q (m x m)
	float q_data[] = {1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1};
	
	arm_matrix_instance_f32 q = {state_dimension, state_dimension, q_data};
	ks.q = q;
	
	//r (n x n)
	float r_data[] = {0.1, 0.2, 0.0, 0.4};
	arm_matrix_instance_f32 r = {measurement_dimension, measurement_dimension, r_data};
	ks.r = r;
	
	//x (m x 1)
	float x_data[] = {2.0, 3.0, 4.0};
	arm_matrix_instance_f32 x = {state_dimension, 1, x_data};
	ks.x = x;
	
	//p (m x m)
	float p_data[] = {0.1, 0.8, 0.5, 0.2, 0.4, 0.7, 0.4, 1.5, 1.2};
	arm_matrix_instance_f32 p = {state_dimension, state_dimension, p_data};
	ks.p = p;
	
	//k (m x n)
	float k_data[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	arm_matrix_instance_f32 k = {state_dimension, measurement_dimension, k_data};
	ks.k = k;
	
	//f	(m x m)
	float f_data[] = {2.0, 3.0, 4.0, 6.0, 3.0, 1.0, 2.0, 0.0, 2.0}; //this is a 3x3 I matrix
	//float f_data[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}; //this is a 3x3 I matrix

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
	arm_matrix_instance_f32 p_predict = {State_dimension, State_dimension, p_predict_data};
	
	//initialize temp_n_x_m
	float temp_n_x_m_data[Measurement_dimension * State_dimension];
	arm_matrix_instance_f32 temp_n_x_m = {Measurement_dimension, State_dimension, temp_n_x_m_data};
	
	//initialize temp_n_x_n_1
	float temp_n_x_n_data_1[Measurement_dimension * Measurement_dimension];
	arm_matrix_instance_f32 temp_n_x_n_1 = {Measurement_dimension, Measurement_dimension, temp_n_x_n_data_1};
	
	//initialize temp_n_x_n_
	float temp_n_x_n_data_2[Measurement_dimension * Measurement_dimension];
	arm_matrix_instance_f32 temp_n_x_n_2 = {Measurement_dimension, Measurement_dimension, temp_n_x_n_data_2};
	
	//initialize temp_m_x_n
	float temp_m_x_n_data[State_dimension * Measurement_dimension];
	arm_matrix_instance_f32 temp_m_x_n = {State_dimension, Measurement_dimension, temp_m_x_n_data};
	
	//initialize temp_m_x_m_1
	float temp_m_x_m_data_1[State_dimension * State_dimension];
	arm_matrix_instance_f32 temp_m_x_m_1 = {State_dimension, State_dimension, temp_m_x_m_data_1};
		
	//initialize temp_m_x_m_2
	float temp_m_x_m_data_2[State_dimension * State_dimension];
	arm_matrix_instance_f32 temp_m_x_m_2 = {State_dimension, State_dimension, temp_m_x_m_data_2};
	
	//initialize temp_n_x_1
	float temp_n_x_1_data[Measurement_dimension];
	arm_matrix_instance_f32 temp_n_x_1 = {Measurement_dimension, 1, temp_n_x_1_data};
	
	//initialize temp_m_x_1
	float temp_m_x_1_data[State_dimension];
	arm_matrix_instance_f32 temp_m_x_1 = {State_dimension, 1, temp_m_x_1_data};
	
	//initialize f_transpose
	float f_transpose_data[State_dimension * State_dimension];
	arm_matrix_instance_f32 f_transpose = {State_dimension, State_dimension, f_transpose_data};
	//calculate f_transpose
	arm_mat_trans_f32(&kstate->f, &f_transpose);
	
	//initialize h_transpose
	float h_transpose_data[State_dimension * Measurement_dimension]; //( m x n)
	arm_matrix_instance_f32 h_transpose = {State_dimension, Measurement_dimension, h_transpose_data};
	//calculate h_transpose
	arm_mat_trans_f32(&kstate->h, &h_transpose);
	
	//initialize I
	float i_matrix_data[State_dimension * State_dimension]; //(m x m)
	int j;
	int temp = State_dimension + 1;
	
	for (j = 0; j < State_dimension*State_dimension; j++){ //build I based on m
		if ((j % temp) == 0){
			i_matrix_data[j] = 1.0;
		}
		else{
			i_matrix_data[j] = 0.0;
		}
	}
	
	arm_matrix_instance_f32 i_matrix = {State_dimension, State_dimension, i_matrix_data};
		
	int i;
	for(i = 0; i < Length; i++) {		
		// Eq'1
		arm_mat_mult_f32(&kstate->f, &kstate->x, &x_predict);
		
		// PRINT X_PREDICT
		int predict_x;	
		printf("-----------X_Predict---------\n");
		for(predict_x = 0 ; predict_x < State_dimension; predict_x++) {
			printf("%f\n",(float)(x_predict.pData[predict_x]));
		}
		// --------------------------------------
		
		// Eq'2
		arm_mat_mult_f32(&kstate->f, &kstate->p, &temp_m_x_m_1); 			//temp1 = F * P
		arm_mat_mult_f32(&temp_m_x_m_1, &f_transpose, &temp_m_x_m_2);	//temp2 = temp1 * F^T
		arm_mat_add_f32(&temp_m_x_m_2, &kstate->q, &p_predict);				//p_predict = temp2 + Q
		
		// PRINT P_PREDICT
		int predict_p;	
		printf("-----------P_Predict---------\n");
		for(predict_p = 0 ; predict_p < State_dimension * State_dimension; predict_p++) {
			printf("%f\n",(float)(p_predict.pData[predict_p]));
		}
		// --------------------------------------
		
		// Eq'3
		arm_mat_mult_f32(&kstate->h, &p_predict, &temp_n_x_m);			//temp_nm = H * p_predict
		arm_mat_mult_f32(&temp_n_x_m, &h_transpose, &temp_n_x_n_1);		//temp_nn1 = temp_nm * H^T
		arm_mat_add_f32(&temp_n_x_n_1, &kstate->r, &temp_n_x_n_2);		//temp_nn2 = temp_nn1 + R	
		arm_mat_inverse_f32(&temp_n_x_n_2, &temp_n_x_n_1);				//temp_nn1 = tempnn2^-1	
		arm_mat_mult_f32(&h_transpose, &temp_n_x_n_1, &temp_m_x_n);		//temp_mn = H^T * temp_nn1
		arm_mat_mult_f32(&p_predict, &temp_m_x_n, &kstate->k);			//K = p_predict * temp_mn		
		
		// PRINT k
		printf("-----------K---------\n");
		int k_index;
		for(k_index = 0 ; k_index < State_dimension * Measurement_dimension; k_index++) {
			printf("%f\n",(float)(kstate->k.pData[k_index]));
		}
		// --------------------------------------
		
		// Eq'4
		arm_mat_mult_f32(&kstate->k, &kstate->h, &temp_m_x_m_1);		//temp_mm1 = K * H
		arm_mat_sub_f32(&i_matrix, &temp_m_x_m_1, &temp_m_x_m_2);		//temp_mm2 = I - temp_mm1	
		arm_mat_mult_f32(&temp_m_x_m_2, &p_predict, &kstate->p);			//kstate->p = temp_mm2 * P_predict
		
		printf("-----------Pfinal---------\n");
		int pfinal_index;	
		for(pfinal_index = 0 ; pfinal_index < State_dimension * State_dimension; pfinal_index++) {
			printf("%f\n",(float)(kstate->p.pData[pfinal_index]));
		}
		// --------------------------------------
				
		// Eq'5
		arm_mat_mult_f32(&kstate->h, &x_predict, &temp_n_x_1);		//temp_n1 = H * x_predict
		arm_matrix_instance_f32 input_i = {Measurement_dimension, 1, &(InputArray[i])}; //storing InputArray[i] in an (n x 1) matrix 
		arm_mat_sub_f32(&input_i, &temp_n_x_1, &temp_n_x_1);		//temp_n1 = InputArray[i] - temp_n1		//I'm reusing temp_n1 since it's subtraction - TODO: check if this is ok
		arm_mat_mult_f32(&kstate->k, &temp_n_x_1, &temp_m_x_1);		//temp_m1 = K * temp_n1
		arm_mat_add_f32(&x_predict, &temp_m_x_1, &kstate->x);		//kstate->x = x_predict + temp_m1
		
		// save to filtered array
		int save_index;
		for(save_index = 0; save_index < State_dimension; save_index++) {
			OutputArray[save_index] = (float)(*(kstate->x.pData + save_index));
		}
		
		printf("----------- Output---------\n");
		int ee;	
		for(ee = 0 ; ee < State_dimension; ee++) {
			printf("%f\n", (float)(OutputArray[ee]));
		}
		// --------------------------------------				
	}
	
	return 0;
}
