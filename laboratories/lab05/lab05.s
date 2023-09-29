
.bss
input_adress: .skip 20  # buffer
num_1: .skip 4
num_2: .skip 4
num_3: .skip 4
num_4: .skip 4
out: .skip 20


.text
read:
    li a0, 0 # file descriptor = 0 (stdin)
    la a1, input_adress #  buffer
    li a2, 20 # size (lendo apenas 1 byte, mas tamanho é variável)
    li a7, 63 # syscall read (63)
    ecall
    ret


str_to_num:
    addi t0, t0, -48
    mul t0, t0, a1
    addi t1, t1, -48
    mul t1, t1, a2
    addi t2, t2, -48
    mul t2, t2, a3
    addi t3, t3, -48

    add t4, t0, t1
    add t4, t4, t2
    add t4, t4, t3
    
    jalr zero, a4, 0

copy_num_1:
    la a0, input_adress
    li a1, 1000
    li a2, 100
    li a3, 10


    lb t0, 0(a0)
    lb t1, 1(a0)
    lb t2, 2(a0)
    lb t3, 3(a0)

    jal a4, str_to_num

    la t5, num_1
    sw t4, 0(t5)



    lb t0, 5(a0)
    lb t1, 6(a0)
    lb t2, 7(a0)
    lb t3, 8(a0)

    jal a4, str_to_num

    la t5, num_2
    sw t4, 0(t5)



    lb t0, 10(a0)
    lb t1, 11(a0)
    lb t2, 12(a0)
    lb t3, 13(a0)

    jal a4, str_to_num

    la t5, num_3
    sw t4, 0(t5)



    lb t0, 15(a0)
    lb t1, 16(a0)
    lb t2, 17(a0)
    lb t3, 18(a0)

    jal a4, str_to_num

    la t5, num_4
    sw t4, 0(t5)

    ret


babylonian:
    li t4, 0
    while_1: 
        bge t4, t5, fim_1
        div t6, t1, t2
        add t2, t2, t6
        div t2, t2, t3
        addi t4, t4, 1
        j while_1
    fim_1:

    jalr zero, a4, 0

operations:
    li t3, 2
    li t5, 11


    la t0, num_1
    lw t1, 0(t0)
    
    add t2, zero, t1
    
    div t2, t2, t3

    jal a4, babylonian
    
    sw t2, 0(t0)



    la t0, num_2
    lw t1, 0(t0)

    add t2, zero, t1

    div t2, t2, t3

    jal a4, babylonian

    sw t2, 0(t0)



    la t0, num_3
    lw t1, 0(t0)

    add t2, zero, t1

    div t2, t2, t3

    jal a4, babylonian

    sw t2, 0(t0)



    la t0, num_4
    lw t1, 0(t0)

    add t2, zero, t1

    div t2, t2, t3

    jal a4, babylonian

    sw t2, 0(t0)


    ret


num_to_str:
    div t2, t1, a1
    rem t1, t1, a1
    div t3, t1, a2
    rem t1, t1, a2
    div t4, t1, a3
    rem t1, t1, a3
    
    addi t2, t2, 48
    addi t3, t3, 48
    addi t4, t4, 48
    addi t1, t1, 48

    jalr zero, a4, 0

copy_num:
    la t5, out

    la t0, num_1
    lw t1, 0(t0)

    jal a4, num_to_str
    
    sb t2, 0(t5)
    sb t3, 1(t5)
    sb t4, 2(t5)
    sb t1, 3(t5)    

    li t6, 32
    sb t6, 4(t5)
    
    

    la t0, num_2
    lw t1, 0(t0)

    jal a4, num_to_str
    
    sb t2, 5(t5)
    sb t3, 6(t5)
    sb t4, 7(t5)
    sb t1, 8(t5)    

    li t6, 32
    sb t6, 9(t5)



    la t0, num_3
    lw t1, 0(t0)

    jal a4, num_to_str
    
    sb t2, 10(t5)
    sb t3, 11(t5)
    sb t4, 12(t5)
    sb t1, 13(t5)    

    li t6, 32
    sb t6, 14(t5)



    la t0, num_4
    lw t1, 0(t0)

    jal a4, num_to_str
    
    sb t2, 15(t5)
    sb t3, 16(t5)
    sb t4, 17(t5)
    sb t1, 18(t5)    

    li t6, 10
    sb t6, 19(t5)

    ret



write:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, out       # buffer
    li a2, 20         # size
    li a7, 64           # syscall write (64)
    ecall
    ret



.globl _start
_start:
    jal read
    jal copy_num_1
    jal operations
    jal copy_num
    jal write
