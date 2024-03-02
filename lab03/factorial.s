.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    beq a0, x0, base
    mv a1, a0
    addi sp, sp, -12
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw ra, 8(sp)
    addi a0, a0, -1
    jal factorial
    lw a1, 4(sp)
    lw ra, 8(sp)
    addi sp, sp, 12
    mul a0, a0, a1
    ret
base:
    li a0, 1
    ret