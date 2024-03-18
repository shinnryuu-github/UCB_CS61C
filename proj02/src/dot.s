.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# =======================================================
dot:
    # Prologue
    addi sp, sp, -24
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)

    li t0, 1
    bge a2, t0, check_stride0
    li a1, 75
    j exit2
check_stride0:
    bge a3, t0, check_stride1
    li a1, 76
    j exit2
check_stride1:
    bge a4, t0, loop_start
    li a1, 76
    j exit2
loop_start:
    li t0, 0    #t0 is the counter
    mv s0, a0   #s0 is the base address of v0
    li a0, 0    #a0 is the sum
    mv s1, a1   #s1 is the base address of v1
    li t1, 0    #t1 is the counter of v0
    li t2, 0    #t2 is the counter of v1
loop_continue:
    slli t3, t1, 2
    add s2, t3, s0  #s2 is the address of v0
    lw s4, 0(s2)
    slli t4, t2, 2  
    add s3, t4, s1  #s3 is the address of v1
    lw s5, 0(s3)
    mul t5, s4, s5
    add a0, a0, t5
    add t1, t1, a3
    add t2, t2, a4
    addi t0, t0, 1
    blt t0, a2, loop_continue
loop_end:
    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    addi sp, sp, 24
    ret
