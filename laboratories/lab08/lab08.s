
.section .text

.set read_gps, 0xFFFF0100
.set engine_direction,  0xFFFF0121
.set steering_wheel_direction, 0xFFFF0120
.set x_car_position, 0xFFFF0110
.set y_car_position, 0xFFFF0114
.set z_car_position, 0xFFFF0118





time:

    addi sp, sp, -16
    mv a0, sp
    addi a0, a0, 4
    mv t0, a0
    addi sp, sp, -16
    mv a1, sp 
    addi a1, a1, 12 

    li a7, 169 # chamada de sistema gettimeofday 
    ecall 

    
    lw t1, 0(t0) # tempo em segundos
    lw t2, 8(t0) # fração do tempo em microssegundos
    li t3, 1000
    mul t1, t1, t3
    div t2, t2, t3
    add a0, t2, t1

    addi sp, sp, 16
    addi sp, sp, 16 

    ret

em_frente:

    addi sp, sp, -16
    sw ra, 12(sp)
    sw a0, 8(sp)
    jal time
    mv a2, a0

    1:
        jal time
        sub a3, a0, a2

        li a4, engine_direction
        li a5, 1
        sb a5, 0(a4)


        li a4, read_gps
        li a5, 1
        sb a5, 0(a4)


        2:
            lb a6, 0(a4)
            beqz a6, 3f
            bne a5, zero, 2b
        3:

        li a4, x_car_position
        lw a5, 0(a4)

        li a4, z_car_position
        lw a6, 0(a4)

        addi a5, a5, -165
        addi a6, a6, 114

        li t4, 95
        li t5, 92

        mul a5, a5, t4
        mul a6, a6, t5

        add a5, a5, a6


            blt a5, zero, 2f 
            li a4, steering_wheel_direction
            li a6, -19
            sb a6, 0(a4)            
            j 3f
        2:
            li a4, steering_wheel_direction
            li a6, 19
            sb a6, 0(a4)
        3:


        
        lw a0, 8(sp)
        blt a3, a0, 1b


    lw ra, 12(sp)
    addi sp, sp, 16

    ret




.globl _start
_start:
    li a0, 5000
    jal em_frente

    li a4, engine_direction
    li a5, 0
    sb a5, 0(a4)



/*

inicio
165.399
-114

fim
73
-19

*/

