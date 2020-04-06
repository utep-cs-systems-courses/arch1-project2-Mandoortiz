	.arch msp430g2553
	
	.data			; lightshow_state is static
lightshow_state:
	.word 0

	.text			;
jt:
	.word option0		; jt[0]
	.word option1		; jt[1]
	.word option2		; jt[2]
	.word option3		; jt[3]
	.word default		; jt[4]

	.global assembly_lightshow
assembly_lightshow:
	cmp #4, &lightshow_state; lightshow_state-4
	jnc default		; doesn't borrow if lightshow_state > 3

	mov &lightshow_state, r12;
	add r12, r12		;
	mov jt(r12), r0		;
option0:
	mov #0, &red_on		; red_on = 0
	mov #0, &green_on	; green_on = 0
	add #1, &lightshow_state; lightshow_state++
	jmp end			; break
option1:
	mov #1, &red_on		; red_on = 1
	mov #0, &green_on	; green_on = 0
	add #1, &lightshow_state; lightshow_state++
	jmp end			; break
option2:
	mov #0, &red_on		; red_on = 0
	mov #1, &green_on	; green_on = 1;
	add #1, &lightshow_state; lightshow_state++
	jmp end			; break
option3:
	mov #1, &red_on		; red_on = 1
	mov #1, &green_on	; green_on = 1
	mov #0, &lightshow_state; lightshow_state = 0
	jmp end			; break
default:
	mov #0, &lightshow_state; lightshow_state = 0
	jmp end			; break
	
end:	pop r0			; return
