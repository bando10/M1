.data
prompt: .asciiz "Entez un nb entier:\n"
res: .asciiz "La valeur absolue est: \n"

.text
main:	#print le prompt
	li $v0, 4
	la $a0, prompt
	syscall 
	
	#input int qui sera contenu dans $v0
	li $v0, 5
	syscall 
	
	
	#dabord liberer v0 en bougeant le int a $a0
	move $a0, $v0
	
	#compare input int to 0
	blt $a0, $zero, negatif #on compare le int a zero et sil est inf on va dans negatif
	
	#si positif on le print directm dabord res
	li $v0, 4
	la $a0, res
	syscall 
	
	#mtn le int
	li $v0, 1
	la $a0, 
negatif:	#int negatif on retourne le contraire

	
	
	
	
	
	