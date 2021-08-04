#  Makefile
#  Cody Fagley
#  Authored on 	 January 25, 2019
#  Last Modified    July 03, 2021

#  Contains build directives for XCS Cross Compiler (AArch64)

CCOMP=g++
CFLAGS=-lm -Wall -I/home/${USER}/CodeusTech/Xita-AArch64/src
MEMTEST=-g -O0
SILENT=-Wno-unused-variable -Wno-unused-but-set-variable -Wno-switch -Wno-conversion-null -Wno-write-strings

#  Build and Install Cross Compiler
install: build tidy
	sudo cp _build/xcs-aarch64 /usr/bin/xcs-aarch64
	sudo rm -rf _build

uninstall: 
	sudo rm -rf /usr/bin/xcs-aarch64
	rm -rf ${HOME}/.opt/cross

#  Build XCSL Cross Compiler
build:  grammar src/xcs/xcs.cc
	rm -rf _build
	mkdir _build
	${CCOMP} ${CFLAGS} ${SILENT} src/xcs/xcs.cc -o _build/xcs-aarch64

leakTest: grammar src/xcs/xcs.cc
	rm -rf _build
	mkdir _build
	${CCOMP} ${CFLAGS} ${MEMTEST} ${SILENT} src/xcs/xcs.cc -o _build/xcs-aarch64


#  Build Grammar
grammar: src/xcs/grammar/xita.y src/xcs/grammar/xcsl.l 
	bison src/xcs/grammar/xita.y
	flex src/xcs/grammar/xcsl.l


grammar-test:  src/xcs/grammar/xita.y src/xcs/grammar/xcsl.l 
	bison -Wcounterexamples src/xcs/grammar/xita.y
	flex src/xcs/grammar/xcsl.l

#  Tidy Generated Files
tidy:
	rm lex.yy.c xita.tab.c


#  PHONY TARGETS
.PHONY: install uninstall build

