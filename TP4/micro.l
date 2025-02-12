%{
#include <stdio.h>
#include "y.tab.h"
extern void yyerror(char*);
%}
%option noyywrap
letras [a-zA-Z]
digito [0-9]
%%
"inicio"             {return INICIO;}
"fin"                {return FIN;}
"leer"               {return LEER;}
"escribir"           {return ESCRIBIR;}
"fdt"                {return FDT;}
{letras}[a-zA-Z0-9]* {return ID;}
{digito}{digito}*    {return CONSTANTE;}
"+"                  {return MAS;}
"-"                  {return RESTA;}
":="                 {return ASIGNACION;}
"("                  {return PARENTESISIZQUIERDO;}
")"                  {return PARENTESISDERECHO;}
","                  {return COMA;}
";"                  {return PUNTOCOMA;}
" "                  {}
.                    {yyerror("ERROR LEXICO");}
%%
void yyerror (char *s){
printf ("Ocurrio un %s\n",s);
}