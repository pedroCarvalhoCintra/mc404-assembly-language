
.bss
img_input: .skip 262159  # buffer
width_str: .skip 5
height_str: .skip 5


.data
img_path: .asciz "imagem.pgm"


.text
open:
    la a0, img_path    # endereço do caminho para o arquivo
    li a1, 0             # flags (0: rdonly, 1: wronly, 2: rdwr)
    li a2, 0             # modo
    li a7, 1024          # syscall open 
    ecall
    ret

read:
    la a1, img_input #  buffer
    li a2, 262159 # size (lendo apenas 1 byte, mas tamanho é variável)
    li a7, 63 # syscall read (63)
    ecall
    ret


setPixel:
    li a7, 2200 # syscall setGSPixel (2200)
    ecall
    jalr zero, a4, 0

setCanvasSize:
    li a7, 2201
    ecall
    jalr zero, a2, 0



func1:
    3: 
        lb t2, 0(t0) 
        addi t0, t0, 1
        sb t2, 0(t1) 
        addi t1, t1, 1
        bne t2, a3, 3b
    
    sub t2, t1, t3 
    sub t2, t2, a4
    li t1, 0
    4: 
        bge t1, t2, 5f
        mul a5, a5, a6
        addi t1, t1, 1
        j 4b
    5: 
    div a5, a5, a6 


    li t1, 0
    li t5, 0
    4: 
        bge t1, t2, 5f 
        lb t4, 0(t3)
        addi t4, t4, -48
        mul t4, t4, a5
        add t5, t5, t4
        div a5, a5, a6
        addi t3, t3, 1
        addi t1, t1, 1
        j 4b    
    5:

    jalr zero, a2, 0


sets:
    la t0, img_input

    li a3, 32
    li a4, 1
    li a5, 1
    li a7, 100
    li a6, 10
    
    addi t0, t0, 3 

    la t1, width_str
    mv t3, t1

    jal a2, func1
    
    mv t6, t5
    mv a0, t5



    li a3, 10
    li a5, 1

    la t1, height_str
    mv t3, t1
    
    jal a2, func1

    mv a1, t5


    mul a3, a0, a1

    jal a2, setCanvasSize



    add t0, t0, 4
    mv s0, t0

    li t0, 0 
    li t1, 0     
    for1:
        bge t0, t5, cont1
        li t1, 0
        for2:
            bge t1, t6, cont2

                mul t2, t0, t6
                add t2, t2, t1

                add t2, t2, s0
                lbu a2, 0(t2)

                slli t3, a2, 24
                slli t4, a2, 16
                slli a5, a2, 8
                add a2, t3, t4
                add a2, a2, a5
                addi a2, a2, 255

                mv a0, t1
                mv a1, t0

                jal a4, setPixel

            addi t1, t1, 1
            j for2
        cont2:


        addi t0, t0, 1
        j for1
    cont1:

    # add t0, t0, 4
    # li t2, 0
    # 4: 
    #     bge t2, a3, 5f 
        
    #     lbu a2, 0(t0)
        # slli t3, a2, 24
        # slli t4, a2, 16
        # slli t5, a2, 8
        # add a2, t3, t4
        # add a2, a2, t5
        # addi a2, a2, 255

    #     div a1, t2, t6
    #     rem a0, t2, t6
        
    #     jal a4, setPixel

    #     addi t0, t0, 1
    #     addi t2, t2, 1
    #     j 4b

    # 5:

    ret



.globl _start
_start:
    jal open
    jal read
    jal sets
