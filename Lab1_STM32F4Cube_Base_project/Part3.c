/*-------------------------------------Part3----------------------------------------- */	

// This is for calling the function and should be put in main
	part3(input, kda, ks->residuals.pData, state_dimension, measurement_dimension, len/n);
	// ks->residuals.pData is a pointer to the ResidualArray

/**
** Paramaters:
** pointer to InpuyArray (n x w)
** pointer to OutputArray (m x w)
** pointer to ResidualArray (n x w)
** m = State_dimension
** n = Measurement_dimension
** w = number of columns
**/
void Part3(float* InputArray, float* OutputArray,float* ResidualArray, int m, int n, int w){ //Remember to define this at the top of main and to call it

//Using CMSIS-DSP
//---------------

	//Mean of the residuals (n x 1)
	//-----------
	
	
	//Standard deviation of the residuals (n x 1)
	//-----------

	//Correlation between the residuals and the observed data (ie the InputArray) (n x 1)
	//-----------

	//autocorrelation of the residuals (with a lag of one time step and a lag of two time steps) (n x 1)
	//-----------

//Calculated without CMSIS-DSP library
//-----------------------------------
	
	//Mean of the residuals
	//-----------

	//Standard deviation of the residuals
	//-----------

	//Correlation between the residuals and the observed data (ie the InputArray)
	//-----------

	//autocorrelation of the residuals (with a lag of one time step and a lag of two time steps)
	//-----------	

	//Mean

	arm_mean_f32 (float32_t *pSrc, uint32_t blockSize, float32_t *pResult);
}
	