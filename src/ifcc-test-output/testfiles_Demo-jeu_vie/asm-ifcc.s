# Déclaration : cell00 -> -4 (%rbp)
# Déclaration : cell01 -> -8 (%rbp)
# Déclaration : cell02 -> -12 (%rbp)
# Déclaration : cell10 -> -16 (%rbp)
# Déclaration : cell11 -> -20 (%rbp)
# Déclaration : cell12 -> -24 (%rbp)
# Déclaration : cell20 -> -28 (%rbp)
# Déclaration : cell21 -> -32 (%rbp)
# Déclaration : cell22 -> -36 (%rbp)
# Déclaration : neighbors -> -40 (%rbp)
# Déclaration : next -> -44 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $0, %eax
    movl %eax, -4(%rbp)
    movl $1, %eax
    movl %eax, -8(%rbp)
    movl $0, %eax
    movl %eax, -12(%rbp)
    movl $1, %eax
    movl %eax, -16(%rbp)
    movl $1, %eax
    movl %eax, -20(%rbp)
    movl $1, %eax
    movl %eax, -24(%rbp)
    movl $0, %eax
    movl %eax, -28(%rbp)
    movl $1, %eax
    movl %eax, -32(%rbp)
    movl $0, %eax
    movl %eax, -36(%rbp)
    movl $0, %eax
    movl %eax, -40(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -48(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -52(%rbp)
    movl -48(%rbp), %eax
    addl -52(%rbp), %eax
    movl %eax, -56(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -60(%rbp)
    movl -56(%rbp), %eax
    addl -60(%rbp), %eax
    movl %eax, -64(%rbp)
    movl -16(%rbp), %eax
    movl %eax, -68(%rbp)
    movl -64(%rbp), %eax
    addl -68(%rbp), %eax
    movl %eax, -72(%rbp)
    movl -24(%rbp), %eax
    movl %eax, -76(%rbp)
    movl -72(%rbp), %eax
    addl -76(%rbp), %eax
    movl %eax, -80(%rbp)
    movl -28(%rbp), %eax
    movl %eax, -84(%rbp)
    movl -80(%rbp), %eax
    addl -84(%rbp), %eax
    movl %eax, -88(%rbp)
    movl -32(%rbp), %eax
    movl %eax, -92(%rbp)
    movl -88(%rbp), %eax
    addl -92(%rbp), %eax
    movl %eax, -96(%rbp)
    movl -36(%rbp), %eax
    movl %eax, -100(%rbp)
    movl -96(%rbp), %eax
    addl -100(%rbp), %eax
    movl %eax, -40(%rbp)
    movl $0, %eax
    movl %eax, -44(%rbp)
    movl -40(%rbp), %eax
    movl %eax, -104(%rbp)
    movl $3, %eax
    movl %eax, -108(%rbp)
    movl -104(%rbp), %eax
    cmpl -108(%rbp), %eax
    sete %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label2
    jnz label1
label1:
    movl $1, %eax
    movl %eax, -44(%rbp)
    jmp label2
label2:
    movl -40(%rbp), %eax
    movl %eax, -112(%rbp)
    movl $2, %eax
    movl %eax, -116(%rbp)
    movl -112(%rbp), %eax
    cmpl -116(%rbp), %eax
    setl %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label4
    jnz label3
label3:
    movl $0, %eax
    movl %eax, -44(%rbp)
    jmp label4
label4:
    movl -40(%rbp), %eax
    movl %eax, -120(%rbp)
    movl $3, %eax
    movl %eax, -124(%rbp)
    movl -120(%rbp), %eax
    cmpl -124(%rbp), %eax
    setg %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label6
    jnz label5
label5:
    movl $0, %eax
    movl %eax, -44(%rbp)
    jmp label6
label6:
    movl -40(%rbp), %eax
    movl %eax, -128(%rbp)
    movl $2, %eax
    movl %eax, -132(%rbp)
    movl -128(%rbp), %eax
    cmpl -132(%rbp), %eax
    sete %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label8
    jnz label7
label7:
    movl -20(%rbp), %eax
    movl %eax, -136(%rbp)
    movl $1, %eax
    movl %eax, -140(%rbp)
    movl -136(%rbp), %eax
    cmpl -140(%rbp), %eax
    sete %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label10
    jnz label9
label8:
    movl -44(%rbp), %eax
    popq %rbp
    ret
label9:
    movl $1, %eax
    movl %eax, -44(%rbp)
    jmp label10
label10:
    jmp label8
