flags = -Wextra -Wall -static
template:template.c
	gcc $(flags) -o $@ template.c 
