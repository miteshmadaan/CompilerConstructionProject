CC = gcc

all:
	gcc -o stage1.exe driver.c lexer.c parser.c parserHashTable.c stack.c