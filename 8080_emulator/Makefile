all: dir disassembler emulator

dir:
	mkdir -p ./bin/temp

disassembler: dir
	gcc -o ./bin/disassembler -Wall -Werror -O3 ./src/disassembler.c

main: dir
	gcc -g -o ./bin/temp/hal.o -I./inc -c src/hal.c
	gcc -g -o ./bin/temp/cpu.o -I./inc -c src/cpu.c
	gcc -g -o ./bin/temp/main.o -I./inc -c src/main.c
	
emulator: dir main
	gcc -g -o ./bin/emulator ./bin/temp/*.o
	
clean:
	rm -rf bin
