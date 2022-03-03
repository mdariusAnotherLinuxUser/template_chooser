flags = -Wextra -Wall -static -g
template:template.c
	gcc $(flags) -o $@ template.c 
