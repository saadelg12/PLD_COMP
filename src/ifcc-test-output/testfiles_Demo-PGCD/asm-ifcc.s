# Déclaration : temp -> -12 (%rbp)
# Fonction avec `return` !
# Déclaration : x -> -4 (%rbp)
# Déclaration : y -> -8 (%rbp)
# Déclaration : res -> -12 (%rbp)
# Avertissement : Variable 'x' déclarée mais jamais utilisée !
# Avertissement : Variable 'y' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
pgcd:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl %esi, -8(%rbp)
    jmp label1
label1:
    movl -8(%rbp), %eax
    movl %eax, -16(%rbp)
    movl $0, %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    cmpl -20(%rbp), %eax
    setne %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label3
    jnz label2
label2:
    movl -8(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    cltd
    idivl -28(%rbp)
    movl %edx, %eax 
    movl %eax, -8(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -4(%rbp)
    jmp label1
label3:
    movl -4(%rbp), %eax
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $1071, %eax
    movl %eax, -4(%rbp)
    movl $462, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, %edi
    movl -8(%rbp), %eax
    movl %eax, %esi
    call pgcd
    movl %eax, -12(%rbp)
    movl -12(%rbp), %eax
    popq %rbp
    ret
