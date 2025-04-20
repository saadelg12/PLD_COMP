# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : result -> -12 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $5, %eax
    movl %eax, -4(%rbp)
    movl $3, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    andl -20(%rbp), %eax
    testl %eax, %eax
      jz label2
    jnz label1
label1:
    movl $42, %eax
    movl %eax, -12(%rbp)
    jmp label3
label2:
    movl $0, %eax
    movl %eax, -12(%rbp)
    jmp label3
label3:
    movl -12(%rbp), %eax
    popq %rbp
    ret
