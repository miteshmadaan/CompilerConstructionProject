CC = gcc

all:
	gcc -o stage1exe driver.c lexer.c parser.c parserHashTable.c stack.c AST.c utils.c