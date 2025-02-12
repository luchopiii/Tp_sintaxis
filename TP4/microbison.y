%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern void yyerror(char*);

typedef struct {
    char nombre[32+1];
    } RegTS; 

void guardarIdentificador(RegTS [],int*);
void ordenadorDeListas(RegTS [],int);
int busquedaBinaria(RegTS [], int, char*);
void existeElID(RegTS [],int);

RegTS TS[1000];
int espaciosOcupado = 0;
int resultado = 0;

%}
%union{
 char* cadena;
 int num;
}
%token INICIO FIN LEER ESCRIBIR MAS RESTA ASIGNACION PARENTESISIZQUIERDO PARENTESISDERECHO COMA PUNTOCOMA FDT
%token <cadena> ID
%token <num> CONSTANTE
%%
objetivo:programa FDT {printf("Terminado\n");}
;
programa:INICIO listasentencias FIN
;
listasentencias:sentencia
|listasentencias sentencia
;
sentencia:identificador {if(yyleng>32)yyerror("ERROR SEMANTICO POR EXCESO DE CARACTERES\n");guardarIdentificador(TS,&espaciosOcupado);} ASIGNACION expresion PUNTOCOMA
|LEER PARENTESISIZQUIERDO listaidentificadores PARENTESISDERECHO PUNTOCOMA
|ESCRIBIR PARENTESISIZQUIERDO listaexpresiones PARENTESISDERECHO PUNTOCOMA
;
listaidentificadores:identificador
|listaidentificadores COMA identificador
;
listaexpresiones:expresion
|listaexpresiones COMA expresion
;
expresion:primaria
|expresion operadoraditivo primaria 
;
primaria:identificador {existeElID(TS,espaciosOcupado);}
|CONSTANTE
|PARENTESISIZQUIERDO expresion PARENTESISDERECHO
;
operadoraditivo:MAS
|RESTA
;
identificador:ID
;
%%
int main(){
yyparse();
}

void guardarIdentificador(RegTS TS[1000], int *espaciosOcupado){
    if(*espaciosOcupado == 0){
        strncpy(TS[*espaciosOcupado].nombre, yytext, 32);
        (*espaciosOcupado)++;
    }else{
    if((*espaciosOcupado)!=1){
        ordenadorDeListas(TS,*espaciosOcupado);}
    
    resultado = busquedaBinaria(TS,*espaciosOcupado,yytext);

    if(resultado == -1){
        strncpy(TS[*espaciosOcupado].nombre, yytext, 32);
        (*espaciosOcupado)++;
    } else{
        yyerror("ERROR SEMANTICO POR COINCIDENCIA DE NOMBRES DE IDENTIFICADORES\n");
    }}
}

void ordenadorDeListas(RegTS TS[1000],int espaciosOcupado){
    char temp[32+1];
    int i = 0;
    int j = 0;
    for (i; i < espaciosOcupado - 1; i++) {
        for (j; j < espaciosOcupado - i - 1; j++) {
            if (strcmp(TS[j].nombre, TS[j + 1].nombre) > 0) {
                strcpy(temp, TS[j].nombre);
                strcpy(TS[j].nombre, TS[j + 1].nombre);
                strcpy(TS[j + 1].nombre, temp);
            }
        }
    }
}

int busquedaBinaria(RegTS TS[1000],int espaciosOcupado,char* clave) {
    int inicio = 0;
    int fin = espaciosOcupado - 1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;

        int comparacion = strcmp(TS[medio].nombre, clave);

        if (comparacion == 0) {
            return medio;  // Encontró la clave
        } else if (comparacion < 0) {
            inicio = medio + 1;  // Buscar en la mitad derecha
        } else {
            fin = medio - 1;  // Buscar en la mitad izquierda
        }
    }

    return -1;
}

void existeElID(RegTS TS[1000],int espaciosOcupado){
    if(espaciosOcupado == 0){
        yyerror("ERROR SEMANTICO, ESE ID NO TIENE NINGUN VALOR REGISTRADO\n");

    }
    
    if((espaciosOcupado)!=1){
        ordenadorDeListas(TS,espaciosOcupado-1);}

    int i =0;
    for(i;i<espaciosOcupado;i++){
        printf ("%s\n",TS[i]);
    }
    resultado = busquedaBinaria(TS,espaciosOcupado-1,yytext);

    if(resultado == -1){
        yyerror("ERROR SEMANTICO, ESE ID NO TIENE NINGUN VALOR REGISTRADO\n");
    }

}