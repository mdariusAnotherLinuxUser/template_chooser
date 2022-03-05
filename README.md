# template_chooser
A tool that I use everyday, it copies templates from your 
~/Templates folder to your current folder, if a file with
 the same name exists it will not do anything

Compiling the program:<br>
`make`<br>
or<br>
`cc template_chooser_main.c -o tp`

Executing the program will give you a list of the current 
templates, each item will have an id in the left<br>
`./tp`

choosing your desired template is as easy by passing 
the id to the
 program<br>
`./tp 0`

By giving it a second parameter, you will rename 
the copy of the chosen template<br>
`./tp 0 newname`

This littel program is practically a lobotomised copying program
but it prevents me from overwriting important files