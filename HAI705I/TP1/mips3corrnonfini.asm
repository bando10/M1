.data
msg:	.asciiz "Entrer un entier: \n"

.text
main:	li $v0, 4
	la $a0, msg
	syscall
	
	li $v0, 5
	syscall
	
	li $t0, 1
	move $t1, $v0
for: 