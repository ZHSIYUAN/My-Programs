bne $2, $0, 2;跳到最后
jr $31

sw $1, -4($30)
sw $2, -8($30)
sw $3, -12($30)
sw $4, -16($30)
sw $5, -20($30); 回来补
sw $6, -24($30); 回来补
sw $31, -28($30)
lis $31
.word 28
sub $30, $30, $31

add $3, $1, $0 ; $3 is the address of the start of array
add $4, $2, $0 ; $4 is the length of the array
lis $5 ; $5 = 4
.word 4
lis $6 ; $6 = 1
.word 1
lis $2 ; let  $2 be call procedure
.word print

sub $3, $3, $5 ; $3 = $3 - 4

sub $4, $4, $6 ; $4 = $4 - 1
add $3, $3, $5 ; $3 = $3 + 4
lw $1, 0($3)
jalr $2
bne $4, $0, -5

lis $31
.word 28
add $30, $30, $31

lw $1, -4($30)
lw $2, -8($30)
lw $3, -12($30)
lw $4, -16($30)
lw $5, -20($30)
lw $6, -24($30)
lw $31, -28($30)

jr $31


