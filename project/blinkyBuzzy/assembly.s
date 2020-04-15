	.arch mps430g2553

	.data			;st is static variable
st:
	.word 1
	.align 2

	.text			
jt:
	.word default		;jt[0]
	.word option1		;jt[1]
	.word option2		;jt[2]
	.word option3		;jt[3]
	.word option4		;jt[4]

	.text
	.global assembly_lightshow
assembly_lightshow:
	cmp #5, &st		;st-5 doesn't is s > 5
	jc default		;jump if does borrow

	mov &st, r12
	add r12, r12		;r12 = 2*st
	mov jt(r12), r0		;jmp jt[st]
default:
	jmp end			; break
option1:
	mov.b #0, &red_on	; red_on = 0
	mov.b #0, &green_on	; green_on = 0
	mov #2, &st		; state = 2
	jmp end			; break
option2:
	mov.b #1, &red_on	; red_on = 1
	mov.b #0, &green_on	; green_on = 0
	mov #3, &st		; state = 3
	jmp end			; break
option3:
	mov.b #0, &red_on	; red_on = 0
	mov.b #1, &green_on	; green_on = 1
	mov #4, &st		; state = 4
	jmp end			; break
option4:
	mov.b #1, &red_on	; red_on = 1
	mov.b #1, &green_on	; green_on = 1
	mov #1, &st		; state = 1
	jmp end			; break
end:
	pop r0
