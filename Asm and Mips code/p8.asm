add $20, $1, $0 ; $20 = $1
add $22, $2, $0
lis $24 
.word 1
lis $21 ; $21 = height
.word height
lis $3
.word 3
jr $31
jalr $21 ; call height

height:
beq $22, $0, jumpout
sub $22, $22, $24
add $4, $1, $0 ; $4 stores the address
lw $5, 4($4) ; $5 is left child
lw $6, 8($4) ; $6 is the right child

lis $7 ; $7 = -1
.word -1

lis $8 ; $8 = 1
.word 1

lis $9
.word height

lis $10 ; $10 = 4
.word 4

lis $11 ; $11 = 8
.word 8

bne $5, $7, 2; 跳到下面
beq $6, $7, hasnochild; if $5 = -1 and $6 = -1,跳到$3 = 1那里
bne $6, $7, hasrightchild
beq $6, $7, hasleftchild ; bne $5, $7 跳到这里！
bne $6, $7, hastwochild; 跳到下面

hasnochild:
lis $3  ; ; 这个地方要不再读取下面的任何instruction
.word 1
beq $3, $3, theend;需要在这里停止

hastwochild:
add $1, $1, $10
jalr $9
add $12, $3, $0 ; now $12 = $3

add $1, $1, $11
jalr $9
add $13, $3, $0 ; now $12 = $3

; compare the larger one
slt $28, $12, $13
bne $28, $0, 2
add $3, $12, $0 ;$3 = $12
beq $28, $0, 1
add $3, $13, $0 ; $3 = $13
add $3, $3, $8 ; $3 = max + 1
beq $3, $3, theend


hasleftchild:
add $1, $1, $10 ; $1 = $1 + 4
jalr $9
add $3, $3, $8 ; $3 = $3 + 1
beq $3, $3, theend

hasrightchild:
add $1, $1, $11
jalr $9
add $3, $3, $8
beq $3, $3, theend

jumpout:
add $1, $20, $0
jr $31

theend:
