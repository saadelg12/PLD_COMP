# Fonction avec `return` !
# Fonction avec `return` !
# Fonction avec `return` !
# Fonction avec `return` !
# Fonction avec `return` !
# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : op -> -12 (%rbp)
# Déclaration : res -> -16 (%rbp)
# Fonction avec `return` !
.globl main
add:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl %esi, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    addl -16(%rbp), %eax
    popq %rbp
    ret
sub:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl %esi, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    subl -16(%rbp), %eax
    popq %rbp
    ret
mul:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl %esi, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    imull -16(%rbp), %eax
    popq %rbp
    ret
divide:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl %esi, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    cltd
    idivl -16(%rbp)
    popq %rbp
    ret
mod:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl %esi, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    cltd
    idivl -16(%rbp)
    movl %edx, %eax 
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $9, %eax
    movl %eax, -4(%rbp)
    movl $12, %eax
    movl %eax, -8(%rbp)
    movl $43, %eax
    movl %eax, -12(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -20(%rbp)
    movl $43, %eax
    movl %eax, -24(%rbp)
    movl -20(%rbp), %eax
    cmpl -24(%rbp), %eax
    sete %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label7
    jnz label6
label6:
    movl -4(%rbp), %eax
    movl %eax, %edi
    movl -8(%rbp), %eax
    movl %eax, %esi
    call add
    movl %eax, -16(%rbp)
    jmp label7
label7:
    movl -12(%rbp), %eax
    movl %eax, -28(%rbp)
    movl $45, %eax
    movl %eax, -32(%rbp)
    movl -28(%rbp), %eax
    cmpl -32(%rbp), %eax
    sete %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label9
    jnz label8
label8:
    movl -4(%rbp), %eax
    movl %eax, %edi
    movl -8(%rbp), %eax
    movl %eax, %esi
    call sub
    movl %eax, -16(%rbp)
    jmp label9
label9:
    movl -12(%rbp), %eax
    movl %eax, -36(%rbp)
    movl $42, %eax
    movl %eax, -40(%rbp)
    movl -36(%rbp), %eax
    cmpl -40(%rbp), %eax
    sete %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label11
    jnz label10
label10:
    movl -4(%rbp), %eax
    movl %eax, %edi
    movl -8(%rbp), %eax
    movl %eax, %esi
    call mul
    movl %eax, -16(%rbp)
    jmp label11
label11:
    movl -12(%rbp), %eax
    movl %eax, -44(%rbp)
    movl $47, %eax
    movl %eax, -48(%rbp)
    movl -44(%rbp), %eax
    cmpl -48(%rbp), %eax
    sete %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label13
    jnz label12
label12:
    movl -4(%rbp), %eax
    movl %eax, %edi
    movl -8(%rbp), %eax
    movl %eax, %esi
    call divide
    movl %eax, -16(%rbp)
    jmp label13
label13:
    movl -12(%rbp), %eax
    movl %eax, -52(%rbp)
    movl $37, %eax
    movl %eax, -56(%rbp)
    movl -52(%rbp), %eax
    cmpl -56(%rbp), %eax
    sete %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label15
    jnz label14
label14:
    movl -4(%rbp), %eax
    movl %eax, %edi
    movl -8(%rbp), %eax
    movl %eax, %esi
    call mod
    movl %eax, -16(%rbp)
    jmp label15
label15:
    movl -16(%rbp), %eax
    popq %rbp
    ret
