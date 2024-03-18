.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    # Prologue
    addi sp, sp, -4
    sw s0, 0(sp)
    li t0, 1
    bge a1, t0, loop_start
    li a1, 78
    j exit2
loop_start:
    li t1, 0
loop_continue:
    slli t2, t1, 2
    add t0, a0, t2
    lw s0, 0(t0)
    bge s0, zero, loop_next
    li s0, 0
    sw s0, 0(t0)
loop_next:
    addi t1, t1, 1
    blt t1, a1,  loop_continue
loop_end:
    # Epilogue
    lw s0, 0(sp)
    addi sp, sp, 4
    ret