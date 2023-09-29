
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


    jal a2, setCanvasSize
    
    add t0, t0, 4
    mv s0, t0

    li t0, 0 # i
    li t1, 0 # j
    li t2, 0 # k 
    li t3, 0 # q
    

    for1:
        bge t0, t5, cont1
        li t1, 0
        for2:
            bge t1, t6, cont2
            li t2, 0
            li a2, 0


            beq t0, zero, cod1
            addi a4, t5, -1
            beq t0, a4, cod1
            beq t1, zero, cod1
            addi a4, t6, -1
            beq t1, a4, cod1
                for3:
                    li a3, 3
                    bge t2, a3, cont3
                    li t3, 0
                    for4:
                        bge t3, a3, cont4

                        add a1, t0, t2
                        addi a1, a1, -1

                        add a0, t1, t3
                        addi a0, a0, -1

                        mul t4, a1, t6
                        add t4, t4, a0
                        
                        add t4, t4, s0

                        lbu a5, 0(t4)
                        
                        li a4, 1
                        li a6, -1
                        li a7, 8

                        bne t2, a4, 1f # if 
                        bne t3, a4, 1f
                            mul a5, a5, a7
                            j 2f
                        1: # else 
                            mul a5, a5, a6
                        2:
                        
                        add a2, a2, a5

                        addi t3, t3, 1
                        j for4
                    cont4:

                    addi t2, t2, 1
                    j for3
                cont3:
                j cod2
            cod1:
                li a2, 0
            cod2:


            li a4, 256
            blt a2, a4, 1f
                addi a4, a4, -1
                mv a2, a4
            1:

            bge a2, zero, 1f
                li a2, 0
            1:

            slli a3, a2, 24
            slli a4, a2, 16
            slli a5, a2, 8
            add a2, a3, a4
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


/*
    t0 -> posição inicial img_input 
    t1 = t0
    a2 -> cor
    for (int i = 0; i < heitght; i++){
        for (int j = 0; j < width; j++){

            # posição_no_vetor = i*widht + j;
            # t1 = posição_no_vetor
            # t1 = t1 + t0
            # lb a2, 0(t1)

            a2 = 0 

            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    a1 = i + k - 1
                    a0 = j + q - 1

                    posição_no_vetor = a1*widht + a0;
                    t1 = posição_no_vetor
                    t1 = t1 + t0
                    lb a3, 0(t1)

                    if ( k == 1 and q == 1 ) {
                        a3 = a3 * 8;
                    } else {
                        a3 = a3 * -1;
                    }
                    a2 = a2 + a3;
                }
            }
            a0 = j
            a1 = i 
            setPixel();
        }
    }
*/

    ret

.globl _start
_start:
    jal open
    jal read
    jal sets
