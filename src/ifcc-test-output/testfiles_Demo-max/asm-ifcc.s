# Déclaration : max -> -24 (%rbp)
# Fonction avec `return` !
# Déclaration : n1 -> -4 (%rbp)
# Déclaration : n2 -> -8 (%rbp)
# Déclaration : n3 -> -12 (%rbp)
# Déclaration : n4 -> -16 (%rbp)
# Déclaration : n5 -> -20 (%rbp)
# Fonction avec `return` !
.globl main
findMax:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl %esi, -8(%rbp)
    movl %edx, -12(%rbp)
    movl %ecx, -16(%rbp)
    movl %r8d, -20(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    movl %eax, -32(%rbp)
    movl -28(%rbp), %eax
    cmpl -32(%rbp), %eax
    setg %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label2
    jnz label1
label1:
    movl -8(%rbp), %eax
    movl %eax, -24(%rbp)
    jmp label2
label2:
    movl -12(%rbp), %eax
    movl %eax, -36(%rbp)
    movl -24(%rbp), %eax
    movl %eax, -40(%rbp)
    movl -36(%rbp), %eax
    cmpl -40(%rbp), %eax
    setg %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label4
    jnz label3
label3:
    movl -12(%rbp), %eax
    movl %eax, -24(%rbp)
    jmp label4
label4:
    movl -16(%rbp), %eax
    movl %eax, -44(%rbp)
    movl -24(%rbp), %eax
    movl %eax, -48(%rbp)
    movl -44(%rbp), %eax
    cmpl -48(%rbp), %eax
    setg %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label6
    jnz label5
label5:
    movl -16(%rbp), %eax
    movl %eax, -24(%rbp)
    jmp label6
label6:
    movl -20(%rbp), %eax
    movl %eax, -52(%rbp)
    movl -24(%rbp), %eax
    movl %eax, -56(%rbp)
    movl -52(%rbp), %eax
    cmpl -56(%rbp), %eax
    setg %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label8
    jnz label7
label7:
    movl -20(%rbp), %eax
    movl %eax, -24(%rbp)
    jmp label8
label8:
    movl -24(%rbp), %eax
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $1, %eax
    movl %eax, -4(%rbp)
    movl $5, %eax
    movl %eax, -8(%rbp)
    movl $3, %eax
    movl %eax, -12(%rbp)
    movl $9, %eax
    movl %eax, -16(%rbp)
    movl $2, %eax
    movl %eax, -20(%rbp)
    movl -4(%rbp), %eax
    movl %eax, %edi
    movl -8(%rbp), %eax
    movl %eax, %esi
    movl -12(%rbp), %eax
    movl %eax, %edx
    movl -16(%rbp), %eax
    movl %eax, %ecx
    movl -20(%rbp), %eax
    movl %eax, %r8d
    call findMax
    popq %rbp
    ret
