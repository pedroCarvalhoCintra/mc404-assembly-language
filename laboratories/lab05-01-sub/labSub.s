
.bss
input_1: .skip 12 
input_2: .skip 20

yb: .skip 4
xc: .skip 4

ta: .skip 4
tb: .skip 4
tc: .skip 4
tr: .skip 4

da: .skip 4
db: .skip 4
dc: .skip 4

y: .skip 4
x_1: .skip 4
x_2: .skip 4
x: .skip 4

out: .skip 12

.data
hyphen: .byte '-'
plus: .byte '+'

.text
read_1:
    li a0, 0 
    la a1, input_1 
    li a2, 12 
    li a7, 63 
    ecall
    ret

read_2:
    li a0, 0 
    la a1, input_2 
    li a2, 20 
    li a7, 63 
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

satellite_position:
    la a0, input_1
    la a6, hyphen
    lb a6, 0(a6)  
    li a1, 1000
    li a2, 100
    li a3, 10   
    li a5, -1

    lb t6, 0(a0)
    lb t0, 1(a0)
    lb t1, 2(a0)
    lb t2, 3(a0)
    lb t3, 4(a0)

    jal a4, str_to_num

    bne a6, t6, 1f
        mul t4, t4, a5
    1:

    la t5, yb
    sw t4, 0(t5)



    lb t6, 6(a0)
    lb t0, 7(a0)
    lb t1, 8(a0)
    lb t2, 9(a0)
    lb t3, 10(a0)

    jal a4, str_to_num

    bne a6, t6, 1f
        mul t4, t4, a5
    1:

    la t5, xc
    sw t4, 0(t5)

    ret


times:
    la a0, input_2
    
    lb t0, 0(a0)
    lb t1, 1(a0)
    lb t2, 2(a0)
    lb t3, 3(a0)

    jal a4, str_to_num

    la t5, ta
    sw t4, 0(t5)



    lb t0, 5(a0)
    lb t1, 6(a0)
    lb t2, 7(a0)
    lb t3, 8(a0)

    jal a4, str_to_num

    la t5, tb
    sw t4, 0(t5)



    lb t0, 10(a0)
    lb t1, 11(a0)
    lb t2, 12(a0)
    lb t3, 13(a0)

    jal a4, str_to_num

    la t5, tc
    sw t4, 0(t5)



    lb t0, 15(a0)
    lb t1, 16(a0)
    lb t2, 17(a0)
    lb t3, 18(a0)

    jal a4, str_to_num

    la t5, tr
    sw t4, 0(t5)

    ret

distances:

    la t0, tr
    lw a7, 0(t0) 
    li a0, 3

    la t0, ta
    lw t1, 0(t0)
    sub t2, a7, t1
    mul t2, t2, a0
    div t2, t2, a3
    la t0, da
    sw t2, 0(t0)


    la t0, tb
    lw t1, 0(t0)
    sub t2, a7, t1
    mul t2, t2, a0
    div t2, t2, a3
    la t0, db
    sw t2, 0(t0)


    la t0, tc
    lw t1, 0(t0)
    sub t2, a7, t1
    mul t2, t2, a0
    div t2, t2, a3
    la t0, dc
    sw t2, 0(t0)
    
    ret

babylonian:
    li t4, 0
    while_1: 
        bge t4, t5, fim_1
        div t6, a6, t2
        add t2, t2, t6
        div t2, t2, a0
        addi t4, t4, 1
        j while_1
    fim_1:

    jalr zero, a7, 0


geographic_position:
    
    la t0, da
    lw t1, 0(t0)
    la t2, yb
    lw t3, 0(t2) 
    la t4, db
    lw t5, 0(t4)

    li a0, 2
    la t6, y
    mul t1, t1, t1
    mul t3, t3, t3
    mul t5, t5, t5
    add a4, t1, t3
    sub a4, a4, t5
    lw t3, 0(t2)
    mul t3, t3, a0
    div a4, a4, t3
    sw a4, 0(t6)


    la t0, da
    lw t1, 0(t0)
    mul t1, t1, t1
    mul a4, a4, a4
    sub a6, t1, a4

    li t5, 21

    add t2, zero, a6
    div t2, t2, a0

    jal a7, babylonian

    la t6, x_1  
    sw t2, 0(t6)

    la t6, x_2
    mul t2, t2, a5
    sw t2, 0(t6)

    ret

find_x:

    la t0, x_1
    lw t1, 0(t0) 
    la t0, x_2
    lw t2, 0(t0)
    la t0, dc
    lw t3, 0(t0)
    la t0, y
    lw t4, 0(t0)
    la t0, xc
    lw t5, 0(t0)

    sub t1, t1, t5
    sub t2, t2, t5
    mul t1, t1, t1
    mul t2, t2, t2
    mul t4, t4, t4
    add t1, t1, t4
    add t2, t2, t4

    mul t3, t3, t3
    sub t1, t1, t3
    sub t2, t2, t3

    bge t1, zero, 1f
        mul t1, t1, a5
    1:
    
    bge t2, zero, 1f
        mul t2, t2, a5
    1:

    blt t1, t2, 1f
        la t0, x_2
        j 2f    
    1:
        la t0, x_1
    2:

    lw t1, 0(t0) 
    la t0, x
    sw t1, 0(t0)


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

    la t0, x
    lw t1, 0(t0)

    add a7, zero, t1

    bge t1, zero, 1f
        mul t1, t1, a5
    1:

    jal a4, num_to_str
    

    bge a7, zero, 1f
        la a6, hyphen 
        j 2f
    1:
        la a6, plus
    2:

    lb a6, 0(a6)

    sb a6, 0(t5)
    sb t2, 1(t5)
    sb t3, 2(t5)
    sb t4, 3(t5)
    sb t1, 4(t5)

    li t6, 32
    sb t6, 5(t5)




    la t0, y
    lw t1, 0(t0)

    add a7, zero, t1

    bge t1, zero, 1f
        mul t1, t1, a5
    1:

    jal a4, num_to_str
    

    bge a7, zero, 1f
        la a6, hyphen 
        j 2f
    1:
        la a6, plus
    2:

    lb a6, 0(a6)

    sb a6, 6(t5)
    sb t2, 7(t5)
    sb t3, 8(t5)
    sb t4, 9(t5)
    sb t1, 10(t5)

    li t6, 10
    sb t6, 11(t5)

    ret
    

write_1:
    li a0, 1           
    la a1, out
    li a2, 12       
    li a7, 64           
    ecall
    ret


.globl _start
_start:
    jal read_1
    jal read_2
    jal satellite_position
    jal times
    jal distances
    jal geographic_position
    jal find_x
    jal copy_num

    jal write_1
