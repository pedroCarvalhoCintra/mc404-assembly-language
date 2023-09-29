
.section .bss
.align 4
isr_stack: # Final da pilha das ISRs
.skip 1024 # Aloca 1024 bytes para a pilha
isr_stack_end: # Base da pilha das ISRs

.globl _system_time
_system_time: .skip 4



.section .text
.align 2
//gpt FFFF0300 - FFFF0500
.set inicia_leitura_tempo, 0xFFFF0100
.set tempo_atual, 0xFFFF0104
.set gera_interrupcao, 0xFFFF0108



//midi FFFF0500 - FFFF0700
.set canal, 0xFFFF0300
.set id_instrumento, 0xFFFF0302
.set valor_nota, 0xFFFF0304
.set velocidade_nota, 0xFFFF0305
.set duracao_nota, 0xFFFF0306



.globl play_note
play_note:
    /*
    a0 = canal
    a1 = id instrumento
    a2 = nota musical
    a3 = velocidade da nota 
    a4 = duração da nota

    .set canal, 0xFFFF0500
    .set id_instrumento, 0xFFFF0502
    .set valor_nota, 0xFFFF0504
    .set velocidade_nota, 0xFFFF0505
    .set duracao_nota, 0xFFFF0506

    */
    li a5, canal
    sb a0, 0(a5)

    li a5, id_instrumento
    sh a1, 0(a5)

    li a5, valor_nota
    sb a2, 0(a5)

    li a5, velocidade_nota
    sb a3, 0(a5)

    li a5, duracao_nota
    sh a4, 0(a5)

    ret


external_isr:
    
    li a0, gera_interrupcao
    li a1, 100
    sw a1, 0(a0)

    li a0, inicia_leitura_tempo
    li a1, 1
    sw a1, 0(a0)

    1:
        lw a1, 0(a0)
        beqz a1, 2f
        j 1b 
    2:

    li a0, tempo_atual
    lw a1, 0(a0)

    la a0, _system_time
    sw a1, 0(a0)

    ret


main_isr:

    #salvar o contexto
    csrrw sp, mscratch, sp # Troca sp com mscratch
    addi sp, sp, -64 # Aloca espaço na pilha da ISR
    sw a0, 0(sp) # Salva a0
    sw a1, 4(sp) # Salva a1
    sw a2, 8(sp) # Salva a2
    sw a3, 12(sp) # Salva a3
    sw a4, 16(sp) # Salva a4

    #trata interrupção
    csrr a1, mcause # lê a causa da interrupção
    bgez a1, handle_exc # Verifica se é exceção ou int.
    andi a1, a1, 0x3f # Isola a causa de interrupção
    li a2, 11 # a2 = interrupção externa
    bne a1, a2, otherInt # desvia se não for interrupção externa
    
    # Trata interrupção externa
    jal external_isr

    otherInt:
    handle_exc:

    #recupera contexto

    lw a4, 16(sp) # Recupera a4
    lw a3, 12(sp) # Recupera a3
    lw a2, 8(sp) # Recupera a2
    lw a1, 4(sp) # Recupera a1
    lw a0, 0(sp) # Recupera a0
    addi sp, sp, 64 # Desaloca espaço da pilha da ISR
    csrrw sp, mscratch, sp # Troca sp com mscratch novamente
    mret # Retorna da interrupção


.globl _start
_start:

    # Carrega o endereço da main_isr em mtvec
    la t0, main_isr 
    csrw mtvec, t0

    # Configura mscratch com o topo da pilha das ISRs.
    la t0, isr_stack_end # t0 <= base da pilha
    csrw mscratch, t0 # mscratch <= t0




    #configurando periféricos
    li a5, gera_interrupcao
    li a6, 100
    sw a6, 0(a5)


    # Habilita Interrupções Externas
    # Seta o bit 11 (MEIE) do registrador mie
    csrr t1, mie 
    li t2, 0x800  
    or t1, t1, t2
    csrw mie, t1

    # Habilita Interrupções Global
    # Seta o bit 3 (MIE) do registrador mstatus
    csrr t1, mstatus 
    ori t1, t1, 0x8 
    csrw mstatus, t1


    
    jal main
