#define Q_INIT 2.0
#define R_INIT 50.0
#define X_INIT 0.0
#define P_INIT 300.0
#define K_INIT 0.0
#define F_INIT 1.0
#define H_INIT 1.0
#define LEN 1

typedef struct kalman_state{
	float q; 
	float r;
	float x;
	float p;
	float k;
	float f;
	float h;
} kalman_state;

int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int Length);
