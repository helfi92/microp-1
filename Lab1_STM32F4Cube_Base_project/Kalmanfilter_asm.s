	AREA kalmanFilter, CODE, READONLY
	EXPORT part1

; Define constant F
;F EQU 1
;H EQU 1
	
part1
	;--------------------------------------
	LDR R4, [R0] ; A pointer to the input data array
	LDR R5, [R1] ; A pointer to the filtered data array
	LDR R6, [R2] ; The array's length
	LDR R7, [R3] ; A pointer to the Kalman filter state (struct)
	;-------------------------------------- 1
	; x(k|k-1) = Fx(k-1|k-1)
	ADD R8, R7, #8
	VMOV S4, R8
	
	; Define F and move it to S5 (temporary fix)
	MOV R9, #1
	VMOV S5, R9
	
	; F * x(k-1|k-1) 
	VCVT.F32.U32 S4, S4; x(k-1|k-1) 
	VCVT.F32.U32 S5, S5; F
	VMUL.F32 S6, S4, S5 ;Estimated value, x(k|k-1), is S6 
	;-------------------------------------- 2
	ADD R10, R7, #12; P(k-1|k-1)
	VMOV S7, R10
	
	; F*P(k-1|k-1)*F
	VCVT.F32.U32 S7, S7
	VMUL.F32 S8, S7, S5
	VMUL.F32 S8, S8, S5; S8 has F*P(k-1|k-1)*F
	
	; Q
	VMOV S9, R7
	VCVT.F32.U32 S9, S9
	
	; F*P(k-1|k-1)*F + Q
	VADD.F32 S10, S9, S8; P(k|k-1)
	;-------------------------------------- 3
	ADD R11, R7, #4; R
	
	; Define H and move it to S11 (temporary fix)
	MOV R12, #1
	VMOV S11, R12; H is inside S11
	
	; H * P(k|k-1)
	VCVT.F32.U32 S11, S11
	VMUL.F32 S12, S10, S11
	VMUL.F32 S12, S12, S11; S12 has H * P(k|k-1) * H
	
	; R
	VMOV S13, R11
	VCVT.F32.U32 S13, S13
	
	; H * P(k|k-1) + R
	VADD.F32 S14, S12, S13; 
	
	; H * (H * P(k|k-1) + R)
	VMUL.F32 S15, S11, S14; S15 has H * (H * P(k|k-1) + R)
	
	; TAKE INVERSE!!!!!
	
	; P(k-1|k-1) * H * (H * P(k|k-1) + R)
	VMUL.F32 S16, S7, S15; S16 has P(k-1|k-1) * H * (H * P(k|k-1) + R)
	
	
	
	
	BX LR
	END
	 	
						