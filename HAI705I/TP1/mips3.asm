.data
prompt: .asciiz "Entez un nb entier:\n"
.text
main:	#print le prompt
	li $v0, 4
	la $a0, prompt
	syscall 
	
	#input int qui sera contenu dans $v0
	li $v0, 5
	syscall 
	
	# on met $v0 dans $a0
	move $a1, $v0
	
	#on commence a 1
	li $a2, 1
	
bouclenum:	#
		bge $a1, $a2, fin
		li $v0, 1
		la $a0, ($a1)
		syscall 
		
		#incr $a1
		addi $a2, $a2, 1
		
		#on revient en debut de boucle
		j bouclenum
fin:	#exit
	li $v0, 10
	syscall 