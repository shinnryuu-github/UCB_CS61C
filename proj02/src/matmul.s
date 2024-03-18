.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 72.
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 73.
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 74.
# =======================================================
matmul:
    # Error checks
    # Prologue
    addi sp, sp, -28
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw s6, 24(sp)

    li t0, 1
    bge a1, t0, check1
    li a1, 72
    j exit2
check1:
    bge a2, t0, check2
    li a1, 72
    j exit2
check2:
    bge a4, t0, check3
    li a1, 73
    j exit2
check3:
    bge a5, t0, check4
    li a1, 73
    j exit2
check4:
    beq a2, a4, outer_loop_start
    li a1, 74
    j exit2

outer_loop_start:
    li t0, 0    #t0 = i
    mv s0, a0
    mv s1, a1
    mv s2, a2
    mv s3, a3
    mv s4, a4
    mv s5, a5
    mv s6, a6
outer_loop_continue:
    mul t2, t0, s2
    slli t2, t2, 2
    add t3, s0, t2    #t3 = s0 + i * a2(start of ith row)
inner_loop_start:
    li t1, 0    #t1 = j

inner_loop_continue:
    mv t2, t1
    slli t2, t2, 2
    add t4, s3, t2  #t4 = s0 + j(start of ith col)

    addi sp, sp, -28
    sw ra, 0(sp)
    sw t0, 4(sp)
    sw t1, 8(sp)
    sw t2, 12(sp)
    sw t3, 16(sp)
    sw t4, 20(sp)
    sw t5, 24(sp)
    
    mv a0, t3
    mv a1, t4
    mv a2, s2
    li a3, 1
    mv a4, s5

    jal dot

    sw a0, 0(s6)
    addi s6, s6, 4

    lw ra, 0(sp)
    lw t0, 4(sp)
    lw t1, 8(sp)
    lw t2, 12(sp)
    lw t3, 16(sp)
    lw t4, 20(sp)
    lw t5, 24(sp)
    addi sp, sp, 28

    addi t1, t1, 1
    blt t1, s5, inner_loop_continue
    
inner_loop_end:
    li t1, 0
    addi t0, t0, 1
    blt t0, s1, outer_loop_continue
outer_loop_end:

    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    lw s6, 24(sp)
    addi sp, sp, 28

    ret
