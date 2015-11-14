.PHONY: all clean
all: proc asm
proc:
	cd ./s_proc && $(MAKE) proc
run:
	cd ./s_proc && $(MAKE) run
asm:
	cd ./s_asm && $(MAKE) asm
compile:
	cd ./s_asm && $(MAKE) compile
clean:
	cd ./s_asm && $(MAKE) clean
	cd ./s_proc && $(MAKE) clean
