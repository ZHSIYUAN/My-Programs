add $4, $2, $0 ; $4 = $2
lis $5 ; $5 = 4
.word 4
add $6, $1, $0 ; $6 = $1
lis $7 ; $7 = 1
.word 1
lw $3, 0($1) ; now $3 stores first element in array
sub $6, $6, $5 ; $6 = $6 - 4

sub $4, $4, $7 ; $4 = $4 - 1
add $6, $6, $5 ; $6 + 4
lw $8, 0($6)
slt $9, $3, $8 ; if $3 < $8, set $9 to 1
beq $9, $0, 1
add $3, $8, $0 ; set $3 = $8
bne $4, $0, -7 ; check if array is end

jr $31

