#include <stdio.h>
#include <ctype.h>

int columna(int c){
    if(c =='+'){
		return 10;
	}
	if(c=='-'){
		return 11;
	}
	if(c=='*'){
		return 12;
	}
	if(c=='/'){
		return 13;
	}
	else
	{
        return c-48;
	}
}
int esPalabra(char *cadena){
    static int tt[7][14] = {
      //    0 1 2 3 4 5 6 7 8 9 + - * /
/*A|0 */   {1,1,1,1,1,1,1,1,1,1,3,3,6,6},
/*B+|1 */  {1,1,1,1,1,1,1,1,1,1,2,2,2,4},
/*C|2 */   {1,1,1,1,1,1,1,1,1,1,3,3,6,6},
/*D|3 */   {1,1,1,1,1,1,1,1,1,1,6,6,6,6},
/*E|4 */   {5,1,1,1,1,1,1,1,1,1,5,5,6,6},
/*F|5 */   {5,1,1,1,1,1,1,1,1,1,6,6,6,6},
/*G|6 */   {6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    };
    int estado = 0;
    int i=0;
	int c=cadena[0];
    while(c!='\0')
	{
		estado=tt[estado][columna(c)];
		
		c=cadena[++i];
	}

	if(estado==1)// estados de aceptacion
	{
		return 1;
	}
	
	return 0;
}


int esCaracter(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/'){
        return 1;
    }else{
        return 0;
    }
}

int verificacion(char expr[100+1]){
    int i;
    for(i=0;expr[i];i++)
    {
        if(!(esCaracter(expr[i])||
            isdigit(expr[i])))
            {
                return 0;
            }
    }
    return 1;
}

int deIntaChar(char letra){
    return letra - 48;
}

float evaluar_expresion(char expr[100+1]){//ver si no es de otro tipo

    float numeros[100+1];//ver si no es de otro tipo
    char operadores[100+1];
    int i = 0;
    int puntero_numeros = 0;
    float acumulador_de_numero = 0;
    int puntero_operadores = 0;

    for(i = 0; expr[i] != '\0'; i++) {//recorro toda la expresion hasta encontrar el simbolo de finalizacion

            if(i == 0 && expr[i]=='-'){
            i++;
            while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               numeros[puntero_numeros++] = acumulador_de_numero * (-1); // Agrega el número a la pila y luego aumenta en 1 el puntero
          }

            if(isdigit(expr[i])) {
            acumulador_de_numero = 0;//sirve para almacenar porque los numeros son de varias cifras y los voy a ir guardando en una pila para luego aplicarles los operadores
            
            while(isdigit(expr[i])) {
                acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                i++;
            }
            numeros[puntero_numeros++] = acumulador_de_numero; // Agrega el número a la pila y luego aumenta en 1 el puntero
       }

            if(i == 0 && expr[i]=='+'){
            i++;
            while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               numeros[puntero_numeros++] = acumulador_de_numero; // Agrega el número a la pila y luego aumenta en 1 el puntero
          }

       if(expr[i]=='*'){
            i++;
            
            if(expr[i]=='-'){
                i++;
                acumulador_de_numero = 0;
                while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros-1] = numeros[puntero_numeros-1] * acumulador_de_numero * (-1);
            } else{
             if(isdigit(expr[i])) {
            acumulador_de_numero = 0;//sirve para almacenar porque los numeros son de varias cifras y los voy a ir guardando en una pila para luego aplicarles los operadores
            
            while(isdigit(expr[i])) {
                acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                i++;
            }
            i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros-1] = numeros[puntero_numeros-1] * acumulador_de_numero;
        }else{if(expr[i]=='+'){
                i++;
                acumulador_de_numero = 0;
                while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros-1] = numeros[puntero_numeros-1] * acumulador_de_numero;
            }}}
        }

        if(expr[i]=='/'){
            i++;
            
            if(expr[i]=='-'){
                i++;
                acumulador_de_numero = 0;
                while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros-1] = (numeros[puntero_numeros-1] / acumulador_de_numero) * (-1);
            } else{
             if(isdigit(expr[i])) {
            acumulador_de_numero = 0;//sirve para almacenar porque los numeros son de varias cifras y los voy a ir guardando en una pila para luego aplicarles los operadores
            
            while(isdigit(expr[i])) {
                acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                i++;
            }
            i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros-1] = numeros[puntero_numeros-1] / acumulador_de_numero;
        } else{if(expr[i]=='+'){
                i++;
                acumulador_de_numero = 0;
                while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros-1] = (numeros[puntero_numeros-1] / acumulador_de_numero);
            }}}
        }

        if(expr[i]=='+'){
            i++;

            if(expr[i]=='-'){
                i++;
                acumulador_de_numero = 0;
                while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros++] = acumulador_de_numero * (-1);
            } else{
             if(isdigit(expr[i])) {
            acumulador_de_numero = 0;//sirve para almacenar porque los numeros son de varias cifras y los voy a ir guardando en una pila para luego aplicarles los operadores
            
            while(isdigit(expr[i])) {
                acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                i++;
            }
            i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros++] = acumulador_de_numero;
        } else{if(expr[i]=='+'){
                i++;
                acumulador_de_numero = 0;
                while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros++] =acumulador_de_numero;
            }}}

        operadores[puntero_operadores++]='+';
        }

    if(expr[i]=='-'){
            i++;

            if(expr[i]=='-'){
                i++;
                acumulador_de_numero = 0;
                while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros++] = acumulador_de_numero * (-1);
            } else{
             if(isdigit(expr[i])) {
            acumulador_de_numero = 0;//sirve para almacenar porque los numeros son de varias cifras y los voy a ir guardando en una pila para luego aplicarles los operadores
            
            while(isdigit(expr[i])) {
                acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                i++;
            }
            i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros++] = acumulador_de_numero;
        }else{if(expr[i]=='+'){
                i++;
                acumulador_de_numero = 0;
                while(isdigit(expr[i]) && expr[i] != '\0') {
                  acumulador_de_numero = acumulador_de_numero * 10 + (deIntaChar(expr[i]));
                   i++;
              }
               i--; // Tengo que restarle uno porque cuando detecta que no es un digito es porque es el operador asi que no me lo tengo que saltar
               numeros[puntero_numeros++] =acumulador_de_numero;
            }}}

        operadores[puntero_operadores++]='-';
        }
        
    }
    int numero1 = 0;
    puntero_operadores--;
    puntero_numeros--;
    while(operadores[puntero_operadores] != '\0'){
    if(operadores[puntero_operadores] == '+'){
       numero1 = numeros[puntero_numeros--];
        numeros[puntero_numeros] = numeros[puntero_numeros] + numero1;
        puntero_operadores--;
    } else {
            if(operadores[puntero_operadores] == '-'){
       numero1 = numeros[puntero_numeros--];
        numeros[puntero_numeros] = numeros[puntero_numeros] - numero1;
        puntero_operadores--;
    }
    }

}

return numeros[0];
}

int main() {
    char expresion[100+1];
    printf("Ingrese una expresion: \n");
    scanf("%s",&expresion);

    if(!verificacion(expresion))
    {
        printf("Hay caracteres que no pertenecen al alfabeto");
        return 0;
    }

    if(esPalabra(expresion)){
        printf("La expresion es valida\n");
        printf("Resultado: %f\n", evaluar_expresion(expresion));
    }else{
        printf("La expresion no es valida\n");
    }
    return 0;
}
