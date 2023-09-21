.data
array: .space 12

.text
main:	la $t0, array # 0000 0000 0000
	
	li $t1, 1	#0001 0000 0000
	sw $t1, ($t0)
	
	li $t1, 2	# 0001 0010 0000
	sw $t1, 4($t0)
	
	li $t1, 3	# 0001 0010 0011
	sw $t1, 8($t0)
	
	# [1, 2,  3]  --> [3, 2, 1]
	
	lw $t1, ($t0)	#t1 = 0001
	lw $t2, 8($t0)	#t2 = 0011
	sw $t1, ($t0)
	sw $t1, ($t0)