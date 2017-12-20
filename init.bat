yacc -dv CoralSyntax
flex CoraLexer.l
gcc lex.yy.c y.tab.c zyywrap.c CoralSemantic.c
pause