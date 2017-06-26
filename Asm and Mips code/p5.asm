add $4, $2, $0 ; $4 = $2
beq $4, $0, 21; if empty, jump to the end

lis $3 ; let $3 save address 0xffff000c
.word 0xffff000c
lis $9 ; let $9 = 32 which is space
.word 32
lis $5 ; $5 = 4
.word 4
add $6, $1, $0 ; $6 = $1
lis $7 ; $7 = 1
.word 1
lis $10 ; let $10 = 64
.word 64

sub $6, $6, $5 ; $6 = $6 - 4
; test empty

sub $4, $4, $7 ; $4  = $4 - 1
add $6, $6, $5 ; $6 = $6 + 4
lw $8, 0($6)
bne $8, $0, 2;if $8 != 0, need to transfer

sw $9, 0($3) ; print space
beq $8, $0, 2; if $8 = 0, print and transfer to next code

add $8, $8, $10 ; $8 = $8 + 64
sw $8, 0($3) ; print uppercase character
bne $4, $0, -9 ; to here

jr $31 ; if empty, jump to here directly


