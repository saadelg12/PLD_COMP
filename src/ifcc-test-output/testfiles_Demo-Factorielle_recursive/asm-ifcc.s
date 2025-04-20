# Déclaration : c -> -8 (%rbp)
# Fonction avec `return` !
# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Avertissement : Variable 'a' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
factorielle:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -12(%rbp)
    movl $0, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    cmpl -16(%rbp), %eax
    sete %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label2
    jnz label1
label1:
    movl $1, %eax
    movl %eax, -8(%rbp)
    jmp label3
label2:
    movl -4(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -24(%rbp)
    movl $1, %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    subl -28(%rbp), %eax
    movl %eax, %edi
    call factorielle
    movl %eax, -32(%rbp)
    movl -20(%rbp), %eax
    imull -32(%rbp), %eax
    movl %eax, -8(%rbp)
    jmp label3
label3:
    movl -8(%rbp), %eax
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $10, %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    movl %eax, %edi
    call factorielle
    movl %eax, -8(%rbp)
    movl -8(%rbp), %eax
    popq %rbp
    ret
