	AREA kalmanFilter, CODE, READONLY
	EXPORT part1

; Define constant F
;F EQU 1
;H EQU 1
;R6, R4, R5 ARE FREE

part1
	PUSH {R4-R12}; Saving context

	;--------------------------------------
	LDR R7, [R3] ; A pointer to the Kalman filter state (struct)
	;-------------------------------------- 1
	; x(k|k-1) = Fx(k-1|k-1)
	ADD R8, R7, #8
	VMOV S4, R8
	
	; Define F and move it to S5 (temporary fix)
	MOV R9, #1
	VMOV S5, R9
	
	; F * x(k-1|k-1) 
	VMUL.F32 S6, S4, S5 ;Estimated value, x(k|k-1), is S6 
	;-------------------------------------- 2
	ADD R10, R7, #12; P(k-1|k-1)
	VMOV S7, R10
	
	; F*P(k-1|k-1)*F
	VMUL.F32 S8, S7, S5
	VMUL.F32 S8, S8, S5; S8 has F*P(k-1|k-1)*F
	
	; Q
	VMOV S9, R7
	
	; F*P(k-1|k-1)*F + Q
	VADD.F32 S10, S9, S8; P(k|k-1)
	;-------------------------------------- 3
	ADD R11, R7, #4; R
	
	; Define H and move it to S11 (temporary fix)
	MOV R12, #1; R12 contains the number 1. This register is used multiple times in the code
	VMOV S11, R12; H is inside S11
	
	; H * P(k|k-1)
	VMUL.F32 S12, S10, S11
	VMUL.F32 S12, S12, S11; S12 has H * P(k|k-1) * H
	
	; R
	VMOV S13, R11
	
	; H * P(k|k-1) + R
	VADD.F32 S14, S12, S13; 
	
	;(H * P(k|k-1) + R)^-1
	VMOV S15, R12; R12 was defined earlier and has value 1
	VDIV.F32 S16, S15, S14 
	
	; H * (H * P(k|k-1) + R)^-1
	VMUL.F32 S17, S11, S16; S17 has H * (H * P(k|k-1) + R)
	
	; K = P(k-1|k-1) * H * (H * P(k|k-1) + R)^-1
	VMUL.F32 S18, S7, S17; S18 has P(k-1|k-1) * H * (H * P(k|k-1) + R)^-1
	;-------------------------------------- 4
	; P(k|k) = (I - K*H) * P(k|k-1)
	
	; K * H
	VMUL.F32 S19, S18, S11
	; I
	MOV R6, #1
	VMOV S15, R6; I is inside S15
	; I - K * H
	VSUB.F32 S20, S15, S19
	
	; P(k|k) = (I - K*H) * P(k|k-1)
	VMUL.F32 S21, S20, S10
	;-------------------------------------- 5
	; X(k|k) = X(k|k-1) + K(Z(k) - H * X(k|k-1))
	
	; H *  X(k|k-1)
	VMUL.F32 S22, S11, S6
	
	; LOOP X(k|k-1) + K(Z(k) - H * X(k|k-1))
	;MOV R9, #2 ; RE-USE R10 as array length R2
	MOV R9, #0 ; RE-USE R9 as index i
Loop
	; Loading current array data 
	ADD R10, R0, R9, LSL #2; R10 is the current address -- R10 = R0 + 4 * i
	VLDR.F32 S0, [R10]
	
	; Logic
	; Z(k) - H * X(k|k-1)
	VSUB.F32 S0, S0, S22
	;K(Z(k) - H * X(k|k-1))
	VMUL.F32 S0, S18, S0
	VADD.F32 S0, S6, S0
	
	; Location to store in the filter array
	ADD R10, R1, R9, LSL #2
	VSTR.F32 S0, [R10]
	
	ADD R9, R9, #1; Increase counter
	CMP R9, R2; Compare with array length to know when to exit while loop
	BLT Loop; Branch to loop if R9 < Array length
	
Finish
	POP {R4-R12}
	BX LR
	END ;IT'S NOT ENDING FOR SOME ODD REASON, WHY?
	
	
	
	
	
	
	 	
						