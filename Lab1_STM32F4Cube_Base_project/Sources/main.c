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
	arm_matrix_instance_f32 residuals;
} kalman_state;

typedef struct dsp{
	float32_t standard_deviation;
} dsp;


extern void kalman_asm(float *input, float* kda, int arrLen, kalman_state *ptr); //
int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int Length, int State_dimension, int Measurement_dimension);
int dsp_c(float* dsp_input, float* dsp_input2, int State_dimension, int Measurement_dimension);

int main() {
	float input[] = {0.1, 2.2, -0.1, 3.5, 4.0, 4.1, 9.9, 0.0, 0.0, 2.3};
	float kda[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //out [x_1, x,2, ..., x_w] (m x w)
	// In the comments, we refer to state_dimension as m
	int state_dimension = 1;
	// In the comments, we refer to measurement_dimension as n
	int measurement_dimension = 1;
	int len = 10;
	struct kalman_state ks;
	// q_data is (m x m)
	float q_data[] = {0.1};
	
	// Error check for q
	int q_size = (sizeof(q_data)/sizeof(q_data[0]));
	if (q_size != state_dimension * state_dimension) {
		printf("q size mismatch\n");
		return -1;
	}		
	
	// Initialize q
	arm_mat_init_f32(&ks.q, state_dimension, state_dimension, (float32_t *)q_data);
	
	// r (n x n)
	float r_data[] = {0.1};
	
	// Error check for r
	int r_size = (sizeof(r_data)/sizeof(r_data[0]));
	if (r_size != measurement_dimension * measurement_dimension) {
		printf("r size mismatch\n");
		return -1;
	}	
	
	// Initialize r
	arm_mat_init_f32(&ks.r, measurement_dimension, measurement_dimension, (float32_t *)r_data);
	
	// x (m x 1)
	float x_data[] = {0.0};
	
	// Error check for x
	int x_size = (sizeof(x_data)/sizeof(x_data[0]));
	if (x_size != state_dimension) {
		printf("x size mismatch\n");
		return -1;
	}	
	
	// Initialize x
	arm_mat_init_f32(&ks.x, state_dimension, 1, (float32_t *)x_data);
	
	//p (m x m)
	float p_data[] = {0.1};
	
	// Error check for p	
	int p_size = (sizeof(p_data)/sizeof(p_data[0]));
	if (p_size != state_dimension * state_dimension) {
		printf("p size mismatch\n");
		return -1;
	}
	
	// Initialize p
	arm_mat_init_f32(&ks.p, state_dimension, state_dimension, (float32_t *)p_data);
	
	// k (m x n)
	float k_data[] = {0.0};
	
	// Error check for k
	int k_size = (sizeof(k_data)/sizeof(k_data[0]));
	if (k_size != state_dimension * measurement_dimension) {
		printf("k size mismatch\n");
		return -1;
	}
	
	// Initialize k
	arm_mat_init_f32(&ks.k, state_dimension, measurement_dimension, (float32_t *)k_data);
	
	//f	(m x m)
	float f_data[] = {0.8}; //this is a 3x3 I matrix
	
	// Error check for f
	int f_size = (sizeof(f_data)/sizeof(f_data[0]));
	if (f_size != state_dimension * state_dimension) {
		printf("f size mismatch\n");
		return -1;
	}	
	
	// Initialize f
	arm_mat_init_f32(&ks.f, state_dimension, state_dimension, (float32_t *)f_data);
	
	//h (n x m)
	float h_data[] = {1.2};
	
	// Error check for h
	int h_size = (sizeof(h_data)/sizeof(h_data[0]));
	if (h_size != state_dimension * measurement_dimension) {
		printf("h size mismatch\n");
		return -1;
	}	
	
	// Initialize h
	arm_mat_init_f32(&ks.h, measurement_dimension, state_dimension, (float32_t *)h_data); //TODO: add a check that dimensions of f match up with given state_dimension
	
	// Residuals
	float residual_data[measurement_dimension]; 
	arm_mat_init_f32(&ks.residuals, measurement_dimension, measurement_dimension, (float32_t *)residual_data); //(n x n)
	
	// Part 2
	//Kalmanfilter_C(input, kda, &ks, len, state_dimension, measurement_dimension);
	
	// Part 3
	float dsp_input[] = {1.0, 4.0, 7.0, 2.0, 5.0, 6.0};
	float dsp_input2[] = {2.0, 3.0, 6.0, 6.0, 3.0, 5.0};
	dsp_c(dsp_input, dsp_input2, 3, 2);
	
	return 0;
}

int dsp_c(float* dsp_input, float* dsp_input2, int State_dimension, int Measurement_dimension){
	// Standard Deviation
	float32_t standard_deviation[Measurement_dimension];
	float32_t arithmetic_mean_arr[State_dimension];
	float32_t temp_arr[State_dimension];
	
	int column;
	int row;
	// Arithmetic Mean (x bar)
	for(row = 0; row < State_dimension; row++) {
		// Adding each input
		for(column = 0; column < Measurement_dimension; column++) {
			printf("will be adding %f with %f\n", temp_arr[row], dsp_input[row * Measurement_dimension + column]);
			arithmetic_mean_arr[row] = arithmetic_mean_arr[row] + dsp_input[row * Measurement_dimension + column];
		}
		// Divide by N
		arithmetic_mean_arr[row] = arithmetic_mean_arr[row] / Measurement_dimension;
	}
	// Standard Deviation
	for(row = 0; row < State_dimension; row++) {
		// Subtract and square
		for(column = 0; column < Measurement_dimension; column++) {
			temp_arr[row] = dsp_input[row * Measurement_dimension + column] - arithmetic_mean_arr[row];
			temp_arr[row] = temp_arr[row] * temp_arr[row];
			standard_deviation[row] = standard_deviation[row] + temp_arr[row];
		}
		// Divide and square root
		standard_deviation[row] = sqrt(standard_deviation[row] / Measurement_dimension);	
	}
	
	int t;
	for(t = 0; t < 3; t++){
		printf("diffArray %f\n", standard_deviation[t]);
	}
	
	
	// Subtraction of original data and filtered data
//	for (i=0; i < Measurement_dimension; i++) {
//		analysisOut->diffArr[i] = diffArray[i] = outputArray[i] - inputArray[i];
//		meanDiff += diffArray[i];
//}
	
	
	for(row = 0; row < State_dimension; row++) {
		for(column = 0; column < Measurement_dimension; column++) {
			printf("Row %d with value: %f\n", row, dsp_input[row * Measurement_dimension + column]);
		}
	}
}

int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int Length, int State_dimension, int Measurement_dimension) {
	// Field to hold arm_matrix_instance_f32 errors
	arm_status status;
	// Number of columns
	int w = Length/Measurement_dimension;

	// Initialize x_predict matrix
	float x_predict_data[State_dimension]; //(m x 1)
	arm_matrix_instance_f32 x_predict = {State_dimension, 1.0, x_predict_data};
	
	// Initialize p_predict matrix
	float p_predict_data[State_dimension * State_dimension]; //(m x m)
	arm_matrix_instance_f32 p_predict = {State_dimension, State_dimension, p_predict_data};
	
	// Initialize temp_n_x_m
	float temp_n_x_m_data[Measurement_dimension * State_dimension];
	arm_matrix_instance_f32 temp_n_x_m = {Measurement_dimension, State_dimension, temp_n_x_m_data};
	
	// Initialize temp_n_x_n_1
	float temp_n_x_n_data_1[Measurement_dimension * Measurement_dimension];
	arm_matrix_instance_f32 temp_n_x_n_1 = {Measurement_dimension, Measurement_dimension, temp_n_x_n_data_1};
	
	// Initialize temp_n_x_n_
	float temp_n_x_n_data_2[Measurement_dimension * Measurement_dimension];
	arm_matrix_instance_f32 temp_n_x_n_2 = {Measurement_dimension, Measurement_dimension, temp_n_x_n_data_2};
	
	// Initialize temp_m_x_n
	float temp_m_x_n_data[State_dimension * Measurement_dimension];
	arm_matrix_instance_f32 temp_m_x_n = {State_dimension, Measurement_dimension, temp_m_x_n_data};
	
	// Initialize temp_m_x_m_1
	float temp_m_x_m_data_1[State_dimension * State_dimension];
	arm_matrix_instance_f32 temp_m_x_m_1 = {State_dimension, State_dimension, temp_m_x_m_data_1};
		
	// Initialize temp_m_x_m_2
	float temp_m_x_m_data_2[State_dimension * State_dimension];
	arm_matrix_instance_f32 temp_m_x_m_2 = {State_dimension, State_dimension, temp_m_x_m_data_2};
	
	// Initialize temp_n_x_1
	float temp_n_x_1_data[Measurement_dimension];
	arm_matrix_instance_f32 temp_n_x_1 = {Measurement_dimension, 1, temp_n_x_1_data};
	
	// Initialize temp_m_x_1
	float temp_m_x_1_data[State_dimension];
	arm_matrix_instance_f32 temp_m_x_1 = {State_dimension, 1, temp_m_x_1_data};
	
	// Initialize f_transpose
	float f_transpose_data[State_dimension * State_dimension];
	arm_matrix_instance_f32 f_transpose = {State_dimension, State_dimension, f_transpose_data};
	
	// Calculate f_transpose
	arm_mat_trans_f32(&kstate->f, &f_transpose);
	
	// Initialize h_transpose
	float h_transpose_data[State_dimension * Measurement_dimension]; //( m x n)
	arm_matrix_instance_f32 h_transpose = {State_dimension, Measurement_dimension, h_transpose_data};
	
	// Calculate h_transpose
	arm_mat_trans_f32(&(kstate->h), &h_transpose);
	
	// Initialize I
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
		
	int curr_column, curr_row;
	for(curr_column = 0; curr_column < w; curr_column++) {		
		// Eq'1
		status = arm_mat_mult_f32(&kstate->f, &kstate->x, &x_predict);
		// Error check for Eq'1
		if(status != ARM_MATH_SUCCESS) {
			printf("EQ'1 MUL FAIL\n");
		}
		// Print X_PREDICT
		int predict_x;	
		printf("-----------X_Predict---------\n");
		for(predict_x = 0 ; predict_x < State_dimension; predict_x++) {
			printf("%f\n",(float)(x_predict.pData[predict_x]));
		}
		// --------------------------------------
		
		// Eq'2
		// temp_m_x_m_1 = F * P
		arm_mat_mult_f32(&kstate->f, &kstate->p, &temp_m_x_m_1); 			
		// temp_m_x_m_2 = temp1 * F^T
		arm_mat_mult_f32(&temp_m_x_m_1, &f_transpose, &temp_m_x_m_2);	
		// p_predict = temp2 + Q
		arm_mat_add_f32(&temp_m_x_m_2, &kstate->q, &p_predict);				
		
		// Print P_PREDICT
		int predict_p;	
		printf("-----------P_Predict---------\n");
		for(predict_p = 0 ; predict_p < State_dimension * State_dimension; predict_p++) {
			printf("%f\n",(float)(p_predict.pData[predict_p]));
		}
		// --------------------------------------
		
		// Eq'3
		arm_mat_mult_f32(&kstate->h, &p_predict, &temp_n_x_m);	
		// temp_nm = H * p_predict
		arm_mat_mult_f32(&temp_n_x_m, &h_transpose, &temp_n_x_n_1);		//temp_nn1 = temp_nm * H^T	
		arm_mat_add_f32(&temp_n_x_n_1, &kstate->r, &temp_n_x_n_2);		//temp_nn2 = temp_nn1 + R	
		// Perform the inversion
		status = arm_mat_inverse_f32(&temp_n_x_n_2, &temp_n_x_n_1);
		// Check for inversion error
		if(status != ARM_MATH_SUCCESS) {
			printf("INV FAIL\n");
			return -1;
		}

		// temp_m_x_n = H^T * temp_n_x_n_1
		arm_mat_mult_f32(&h_transpose, &temp_n_x_n_1, &temp_m_x_n);
		// K = p_predict * temp_m_x_n		
		arm_mat_mult_f32(&p_predict, &temp_m_x_n, &kstate->k);			//K = p_predict * temp_mn		
				
		// Eq'4
		// temp_m_x_m_1 = K * H
		arm_mat_mult_f32(&kstate->k, &kstate->h, &temp_m_x_m_1);
		// temp_mm2 = I - temp_m_x_m_1	
		arm_mat_sub_f32(&i_matrix, &temp_m_x_m_1, &temp_m_x_m_2);	
		// kstate->p = temp_m_x_m_2 * P_predict
		arm_mat_mult_f32(&temp_m_x_m_2, &p_predict, &kstate->p);			
				
		// Eq'5
		// temp_n_x_1 = H * x_predict
		arm_mat_mult_f32(&kstate->h, &x_predict, &temp_n_x_1);		
		
		// Load data from InputArray to z_i (n x 1)
		float z_curr_column_data [Measurement_dimension]; 
		for (curr_row = 0; curr_row < Measurement_dimension; curr_row++){
			z_curr_column_data[curr_row] = InputArray[(curr_row * w) + curr_column];
		}
		arm_matrix_instance_f32 z_curr_column = {Measurement_dimension, 1, z_curr_column_data};

		// temp_n1 = z_i - temp_n1		
		arm_mat_sub_f32(&z_curr_column, &temp_n_x_1, &temp_n_x_1);		
		
		// Save this into the residuals (part 3)
		for(curr_row = 0; curr_row < State_dimension; curr_row++) {
			kstate->residuals.pData[curr_row * w + curr_column] = (float)(*(temp_n_x_1.pData + curr_row));
		}
		
		// temp_m1 = K * temp_n1
		arm_mat_mult_f32(&kstate->k, &temp_n_x_1, &temp_m_x_1);		
		arm_mat_add_f32(&x_predict, &temp_m_x_1, &kstate->x);	
				
		// save to filtered array
		for(curr_row = 0; curr_row < State_dimension; curr_row++) {
			OutputArray[curr_row * w + curr_column] = (float)(*(kstate->x.pData + curr_row));
		}
	
		printf("----------- Output--------- with w: %d \n", w);
		int ee, ll;	
		for(ee = 0 ; ee < State_dimension; ee++) {
			for(ll = 0; ll< w; ll++){
				printf("%f, ", (float)(OutputArray[ee*w + ll]));
			}
			printf("\n");
		}
		// --------------------------------------				
	}
	
	return 0;
}
