

.bss
input_adress: .skip 262159  # buffer
teste: .skip 7
width_str: .skip 5
height_str: .skip 5



.data
img_path: .asciz "milking.pgm"



.text
open:
    la a0, img_path    # endereço do caminho para o arquivo
    li a1, 0             # flags (0: rdonly, 1: wronly, 2: rdwr)
    li a2, 0             # modo
    li a7, 1024          # syscall open 
    ecall
    ret

read:
    # li a0, 0 # file descriptor = 0 (stdin)
    la a1, input_adress #  buffer
    li a2, 262159 # size (lendo apenas 1 byte, mas tamanho é variável)
    li a7, 63 # syscall read (63)
    ecall
    ret


setPixel:
    # li a0, 100 # coordenada x = 100
    # li a1, 200 # coordenada y = 200
    # li a2, 0x000000FF # pixel branco
    li a7, 2200 # syscall setGSPixel (2200)
    ecall
    jalr zero, a4, 0



setCanvasSize:
    # li a0, 0 ##
    # li a1, 0
    li a7, 2201
    ecall
    jalr zero, a4, 0

setScaling:
    li a0, 1
    li a1, 1
    li a7, 2202
    ecall
    jalr zero, a4, 0



initial_sets:

    jal a4, setCanvasSize 
    jal a4, setScaling
    
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
    div a5, a5, a6 # a5 = 100



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


num_to_str:
    div t2, a0, a5
    rem a0, a0, a5
    div t3, a0, a6
    rem a0, a0, a6


    addi t2, t2, 48
    addi t3, t3, 48
    addi a0, a0, 48

    jalr zero, a2, 0



find_dimensions:
    la t0, input_adress

    li a3, 32
    li a4, 1
    li a5, 1
    li a7, 100
    li a6, 10
    
    addi t0, t0, 3 

    la t1, width_str
    mv t3, t1

    jal a2, func1
    
    mv a0, t5





    li a3, 10
    li a5, 1
    li a6, 10


    la t1, height_str
    mv t3, t1
    
    jal a2, func1


    mv a1, t5

    mul a3, a0, a1

   

    jal a2, initial_sets


    add t0, t0, 5
    li t2, 0

    


    4: 
        bge t2, a3, 5f # if t2 >= t1 then target
        
        lb a2, 0(t0)
        slli t3, a2, 24
        slli t4, a2, 16
        slli t5, a2, 8
        add a2, t3, t4
        add a2, a2, t5
        addi a2, a2, 255

        div a0, t2, a1
        rem a1, t2, a1
        
        jal a4, setPixel

        addi t0, t0, 1
        addi t2, t2, 1
        j 4b

    5:



    ret

write:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, teste       # buffer
    li a2, 7           # size
    li a7, 64           # syscall write (64)
    ecall
    jalr zero, a2, 0

write_t:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, width_str       # buffer
    li a2, 5          # size
    li a7, 64           # syscall write (64)
    ecall
    jalr zero, a2, 0




.globl _start
_start:
    jal open
    jal read
    jal find_dimensions

