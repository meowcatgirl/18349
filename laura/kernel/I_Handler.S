	.file "I_Handler.S"
	.extern C_IRQ_Handler
	.text

	.comm 	saved_lr 4,4
	.global I_Handler
	.global I_Handler_Cleanup

I_Handler:
	STMFD	sp!, {r0-r7, r9-r12, lr} @set up the stack
	@MRS	ip, cpsr
	@ORR	ip, #0x80
	@MSR	cpsr, ip

	@LDR	r2, =saved_r8	  @saving addres of r8 to r2
	@LDR	r8, [r2]	  @storing value of r8 from address stored in r2
	B	C_IRQ_Handler	  @initialize C_IRQ_Handler
	
I_Handler_Cleanup:
	@MRS	ip, cpsr
	@BIC	ip, #0x80
	@MSR	cpsr, ip
 	LDMFD	sp!, {r0-r7, r9-r12, lr} @restore vars from stack
	SUBS	pc, lr, #4	  @return to U-Boot I_Handler Table
