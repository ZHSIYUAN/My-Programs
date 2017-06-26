bne $2, $0, 3
lis $3 ; if length is empty
.word -1
jr $31 ; if length is not 0, use loop
add $4, $2, $0 ; $4 = $2 = length
lis $5 ; $5 = 4
.word 4
add $6, $1, $0 ; $6 = $1 = address of beginning
lis $7 ; $7 = 1
.word 1
sub $6, $6, $5
add $6, $6, $5 ; start of loop
sub $4, $4, $7 ; $4 - 1
bne $4, $0, -3 ; if $4 != 0, loop again
lw $3, 0($6)
jr $31
