lex mylexer.l 
yacc -d mylexer.y 
cc lex.yy.c y.tab.c -o mylexer -lfl
./mylexer < test.txt
