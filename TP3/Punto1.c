#include <stdio.h>
#include <ctype.h>

//Punto 1
int verifica(char *cadena){
    int i;
	for(i=0;cadena[i];i++)
	{
		if(!(cadena[i]=='-'||
			 cadena[i]=='#'||
             cadena[i]>='a' && cadena[i]<='f'||
             cadena[i]>='A' && cadena[i]<='F'||
			 cadena[i]=='o'||
			 cadena[i]=='O'||
			 cadena[i]=='x'||
			 cadena[i]=='X'||
			 isdigit(cadena[i])))
		 {
		 	return 0;
		 }
	}
	return 1;
}
int columna(int c){
    if(c =='-'){
		return 0;
	}
	if(c=='#'){
		return 27;
	}
	if(c=='x'){
		return 11;
	}
	if(c=='X'){
		return 12;
	}
	if(c=='o'){
		return 25;
	}
	if(c=='O'){
		return 26;
	}
	if(c >= 'a' && c<='f'){
		return c-84;
	}
	if(c >= 'A' && c<='F'){
		return c-46;
	}
	else
	{
        return c-47;
	}
}
int esPalabra(char *cadena){
    static int tt[9][28] = {
      //    - 0 1 2 3 4 5 6 7 8 9 x X a b c d e f A B C D E F o O #
/*-A|0 */   {1,3,2,2,2,2,2,2,2,2,2,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
/*B|1 */   {8,8,2,2,2,2,2,2,2,2,2,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
/*+C|2 */   {8,2,2,2,2,2,2,2,2,2,2,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0},
/*D|3 */   {8,8,8,8,8,8,8,8,8,8,8,4,4,8,8,8,8,8,8,8,8,8,8,8,8,6,6,8},
/*E|4 */   {8,5,5,5,5,5,5,5,5,5,5,8,8,5,5,5,5,5,5,5,5,5,5,5,5,8,8,8},
/*+F|5 */   {8,5,5,5,5,5,5,5,5,5,5,8,8,5,5,5,5,5,5,5,5,5,5,5,5,8,8,0},
/*G|6 */   {8,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
/*+H|7 */   {8,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0},
/*I|8 */   {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
    };
    int estado = 0;
    int i=0;
	int c=cadena[0];
    while(c!='\0')
	{
		estado=tt[estado][columna(c)];
		
		c=cadena[++i];
	}

	if(estado==2 || estado ==5 || estado ==7)// estados de aceptacion
	{
		return 1;
	}
	
	return 0;
}

int main()
{
	char cadena[] = "";
	printf("Ingrese una expresion: \n");
    scanf("%s",&cadena);

	if(!verifica(cadena))
	{
		printf("Hay caracteres que no pertenecen al alfabeto");
		return 0;
	}
	
	if(esPalabra(cadena))
	{
		printf("Es palabra del lenguaje");
	}
	else
	{
		printf("No pertenece al lenguaje");
	}	
	
	return 0;
}