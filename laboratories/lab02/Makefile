lab02.o: lab02.s
	clang -g --target=riscv32 -march=rv32g -mabi=ilp32d -mno-relax lab02.s -c -o lab02.o
lab02_executavel.x: lab02.o
	ld.lld -g lab02.o -o lab02.x
