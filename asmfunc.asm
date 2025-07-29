section .data
align 16
ms_conversion: dd 0.277778, 0.277778, 0.277778, 0.277778 ; Conversion factor from km/h to m/s. This is 1000/3600s
	
section .text
bits 64
default rel

global calc_accelerations

calc_accelerations:
	mov r10, rcx ;matrix pointer
	mov r11, rdx ;acceleration pointer
	mov r12, r8  ;row index

	movss xmm3, [ms_conversion] ;xmm3 = conversion factor

solve_per_row:
	movss xmm0, [r10] ;Load initial velocity (Vi) from matrix
	movss xmm1, [r10 + 4] ;Load final velocity (Vf) from matrix
	movss xmm2, [r10 + 8] ;Load time from matrix

	mulss xmm0, xmm3 ;Convert Vi
	mulss xmm1, xmm3 ;Convert Vf

	;subtract
	subss xmm1, xmm0 ;Vf - Vi
	divss xmm1, xmm2 ;Divide by time

	cvtss2si eax, xmm1 ;Convert result to integer
	mov [r11], eax ;Store the result in the acceleration array

	add r10, 12 ;Move to the next set of values in the matrix
	add r11, 4 ;Move to the next acceleration slot
	dec r12 
	jnz solve_per_row 

	ret
