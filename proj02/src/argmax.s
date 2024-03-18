.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:

    # Prologue
    addi sp, sp, -12
    sw s0, 0(sp)    #s0 is the element in the vector
    sw s1, 4(sp)    #s1 is the address in the vector
    sw s2, 8(sp)   #s2 is the tempt maxinum

    li t0, 1
    bge a1, t0, loop_start
    li a1, 77
    j exit2
loop_start:
    li t0, 0    #t0 is counter
    li s2, 0
    mv t2, a0
    li a0, 0
loop_continue:
    slli t1, t0, 2  #t1 is the real offset
    add s1, t2, t1
    lw s0, 0(s1)
    bge s2, s0, loop_next
    mv s2, s0
    mv a0, t0
loop_next:
    addi t0, t0, 1
    blt t0, a1, loop_continue
loop_end:
    
    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    addi sp, sp, 12

    ret
