.globl abs

.text
# =================================================================
# FUNCTION: Given an int return its absolute value.
# Arguments:
# 	a0 (int) is input integer
# Returns:
#	a0 (int) the absolute value of the input
# =================================================================
abs:
    # Prologue
    

    # return 0
    blt a0, zero, minus
    j exit
minus:
    sub a0, zero, a0
exit:
    # Epilogue

    ret
