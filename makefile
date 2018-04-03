#!/usr/bin/make -f
# -*- mode:makefile -*-

CC := g++ -std=c++11
DIREXEC := ejecutables/
RUN := ./

dirs:
	mkdir -p $(DIREXEC)

SSOOIIGLE: dirs
	$(CC) manager.cpp -o $(DIREXEC)SSOOIIGLE

all: SSOOIIGLE

test: SSOOIIGLE
	cd $(DIREXEC)
	$(RUN)$(DIREXEC)SSOOIIGLE libros/SEAMOS\ PERSONAS\ DE\ INFLUENCIA\ -\ JOHN\ MAXWELL.txt influencia 5

clean:
	rm -rf $(DIREXEC)

