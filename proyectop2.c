#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <math.h>
#include<time.h>
#define RESET_COLOR "\x1b[0m"
#define NEGRO_F "\x1b[40m"
#define VERDE_F "\x1b[42m"
#define ROJO_F "\x1b[41m"
#define    AMARILLO_F "\x1b[43m"
#define    AZUL_F "\x1b[44m"
#define MAGENTA_F "\x1b[45m"
#define CYAN_F "\x1b[46m"
#define BLANCO_F "\x1b[47m"

#define ROJO_T "\x1b[31m"
#define VERDE_T "\x1b[32m"
#define NEGRO_T "\x1b[30m"
#define AMARILLO_T "\x1b[33m"
#define AZUL_T "\x1b[34m"
#define MAGENTA_T "\x1b[35m"
#define CYAN_T "\x1b[36m"
#define BLANCO_T "\x1b[37m"
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))



int** declarar(int a,int b){
  int i,j,**matriz;

  matriz = (int**)malloc(a*sizeof(int*)); //tamaño de la matriz//
  for(i=0;i<a;i++){
    matriz[i] = (int*)malloc(b*sizeof(int));
  }

  for (i=0;i<a;i++){
      for (j=0;j<b;j++){ //se inicializa la matriz en 0//
         matriz[i][j]=0;
        }
    }

  return matriz;
}

 bool sobranEspaciosLibres(int**matriz,int n,int m) // esta funcion se encarga de ver si sobran espacios libres//
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(matriz[i][j] == 0) //pregunta si matriz en una posicion especifica = 0 significa que hay
            { // espacios libre//
                return true;
            }
        }
    }

  //No sobran mas espacios donde colocar fichas, juego empatado
  printf("No hay mas espacios: empate \n");
    return false;
}

void Imprimirmatriz(int**matriz,int n,int m,int colo1,int colo2) //esta funcion se encarga de imprimir a matriz con color//
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(matriz[i][j] == 1)
            {
                if(colo1==1){
                    printf(ROJO_T ROJO_F);printf("[0]");printf(RESET_COLOR);
                }if(colo1==2){
                    printf(AZUL_T AZUL_F);printf("[0]");printf(RESET_COLOR);
                }if(colo1==3){
                    printf(AMARILLO_T AMARILLO_F);printf("[0]");printf(RESET_COLOR);
                }if(colo1==4){
                    printf(NEGRO_T NEGRO_F);printf("[0]");printf(RESET_COLOR);
                }if(colo1==5){
                    printf(MAGENTA_T MAGENTA_F);printf("[0]");printf(RESET_COLOR);
                }if(colo1==6){
                    printf(VERDE_T VERDE_F);printf("[0]");printf(RESET_COLOR);
                }
            }
            else if(matriz[i][j] == 2)
            {
              if(colo2==1){
                    printf(ROJO_T ROJO_F);printf("[0]");printf(RESET_COLOR);
                }if(colo2==2){
                    printf(AZUL_T AZUL_F);printf("[0]");printf(RESET_COLOR);
                }if(colo2==3){
                    printf(AMARILLO_T AMARILLO_F);printf("[0]");printf(RESET_COLOR);
                }if(colo2==4){
                    printf(NEGRO_T NEGRO_F);printf("[0]");printf(RESET_COLOR);
                }if(colo2==5){
                    printf(MAGENTA_T MAGENTA_F);printf("[0]");printf(RESET_COLOR);
                }if(colo2==6){
                    printf(BLANCO_T BLANCO_F);printf("[0]");printf(RESET_COLOR);
                }if(colo1==7){
                    printf(CYAN_T CYAN_F);printf("[0]");printf(RESET_COLOR);
                }
            }
            else
            {
               printf(VERDE_T VERDE_F);printf("[0]");printf(RESET_COLOR); // fondo
            }

        }
        printf("\n");
    }
}

int ColocarFichaEn(int**matriz, int columna,int n,int m) //esta funcion se encarga de colocar fichas en la matriz//
{
    for(int i = 0; i < m; i++)
    {
        if(!(i+1 > n-1))
        {
            if(matriz[i][columna] == 0 && matriz[i+1][columna] != 0 )
            {
                return i;
            }
        }
        else
        {
            //Alcanzo la base del matriz
            if(matriz[i][columna] == 0)
            {
                return i;
            }
        }
    }

    return -1;
}

bool columnaATope(int**matriz, int columna) //esta funcion verifica si la columan esta a tope//
{
    if(matriz[0][columna] != 0)
    {
        //printf("No hay espacio para colocar la ficha ahi \n");
        return true;
    }
    return false;
}



/** Funcion para calcular conecta 4 en horizontal-vertical
 *  @returns 0 si no gano el jugador actual en la posicion dada
 *           n el numero del jugador que conectó 4
 *
 */
int gana_derecho(int ** matriz, int fila, int columna, int n, int m){

  //verificar horizontal

  int j = 0;

  for(int i = 0 ; i < n ; i++){

    if(matriz[fila][i]  == matriz[fila][columna]){
      for(j = i; ( j < (4 + i)) && (j < n) &&  (matriz[fila][j]  == matriz[fila][columna]) ; j++);

      if((j - i) == 4 )
        return matriz[fila][columna];

    }

  }

  //verificar vertical
    for(int i = 0 ; i < n ; i++){

    if(matriz[i][columna]  == matriz[fila][columna]){
      for(j = i; ( j < (4 + i)) && (j < m) &&  (matriz[j][columna]  == matriz[fila][columna]) ; j++);

      if((j - i) == 4)
        return matriz[fila][columna];
    }

  }

  return 0;

}


/** Funcion para calcular conecta 4 en diagonales
 *  @returns 0 si no gano el jugador actual en la posicion dada
 *           n el numero del jugador que conectó 4
 *
 */
int gana_diagonal(int ** matriz, int fila, int columna, int n, int m){

  int i,j,k,l = 0;
  int ganador = 0;

  //Diagonal principal ascendente (-->abajo)
  for(i = 0; (i < 4) && ( fila+i < n) && (columna + i < m)  && (matriz[fila+i][columna+i] == matriz[fila][columna]) ; i++ );

  //diagonal principal descendente (<--arriba)
  for( j = 0; (j < 4) && ( columna-j >= 0) && ( fila-j >= 0) && (matriz[fila-j][columna-j] == matriz[fila][columna]) ; j++  );

  //diagonal secundaria ascendente (<--abajo)
  for(k = 0; (k < 4) && ( fila+k < n) && (columna - k >=0) && (matriz[fila+k][columna-k] == matriz[fila][columna]) ; k++ );

  //diagonal secundaria descendente (-->arriba)
  for(l = 0; (l < 4) && ( fila-l >= 0) && (columna + l < m) && (matriz[fila-l][columna+l] == matriz[fila][columna]) ; l++ );


  //printf("i = %d j = %d k = %d l= %d\n",i,j,k,l);
  if( (i+j-1==4) || (k+l-1==4))
    ganador = matriz[fila][columna];

  return ganador;

}

//Funcion nueva
int ganador(int**matriz, int fila, int columna,int n,int m) //verifica los ganadores//
{

  int winner = 0;
  winner = gana_derecho(matriz,fila,columna,n,m);

  if( winner )
    return winner;


  winner = gana_diagonal(matriz,fila,columna,n,m);

  if( winner )
    return winner;


  return 0;


}

/*MINIMAX*/

typedef struct{
int row, col;
}Move;


// Esta función devuelve verdadero si hay movimientos
// permaneciendo en el tablero. Devuelve falso si
// no quedan movimientos por jugar
bool isMovesLeft(int **tablero, int fila, int columna){
return sobranEspaciosLibres(tablero,fila,columna);
}

// Esta es la función de evaluación como se discutió

int evaluate(int**matriz,int n,int m,int row, int col){


      int ganadorX = ganador(matriz,row,col,n,m);

      if(ganadorX == 2){

        return 10;
      }


      if(ganadorX == 1){

        return -10;
      }

  return 0;

}


// Esta es la función minimax. Considera todo
// las posibles formas en que el juego puede ir y volver
// el valor del tablero
int minimax(int **matriz,int n, int m, int depth, bool isMax, int col, int row){

  int score = evaluate(matriz,n,m,col,row);


if (score != 0){
    return score;
  }

if ((isMovesLeft(matriz,n,m)==false) || depth > 7)
return 0;

//positivo o negativo dependiendo del valor de isMax (1-0)
  int best = pow(-1,isMax)*1000;


  for(int j = 0; j< m ; j++){
    if (!columnaATope(matriz,j)){


      int colocarFila = ColocarFichaEn(matriz,j,n,m);
      matriz[colocarFila][j]=isMax+1;

     // Llamar a minimax de forma recursiva y elegir
    // el valor máximo
      if(isMax)
        best = max( best, minimax(matriz,n,m, depth+1, !isMax,j,colocarFila) );
      else
        best = min( best, minimax(matriz,n,m, depth+1, !isMax,j,colocarFila) );

      // Deshacer el movimiento
      matriz[colocarFila][j] = 0;

    }
  }


  return best + (isMax)?depth:-depth;


}


//Este es el minimax más arrecho porque no tiene restricciones
//Pero tarda MUCHISIMO en los primeros movimientos
Move findBestMove(int **matriz, int n, int m){
int bestVal = -1000;
Move bestMove;
bestMove.row = -1;
bestMove.col = -1;

/*Evaluar cada columna con minimax*/
  for (int j = 0; j<m; j++){

    //Chequear si la columna no está llena
    if (!columnaATope(matriz,j)){

     // Haz el movimiento
      int colocarFila = ColocarFichaEn(matriz,j,n,m);
      matriz[colocarFila][j] = 2;


      // calcula la función de evaluación para esto
      // moverse.
      int moveVal = minimax(matriz,n,m, 2, false,j,colocarFila);
      printf("VALOR DE MOVEVAL = %i\n",moveVal);

      // Deshacer el movimiento
      matriz[colocarFila][j] = 0;

      // Si el valor del movimiento actual es
      // más que el mejor valor, luego actualice
      // mejor/
      if (moveVal > bestVal){
        bestMove.row = colocarFila;
        bestMove.col = j;
        bestVal = moveVal;
      }
    }
  }

printf("El valor de la jugada es : %d\n\n",
bestVal);

return bestMove;
}




int main(){
int**matriz;
int n=0,m=0,modo=0,colo1=0,colo2=0;
char jugador1[20],jugador2[20];


    printf("1.- con la Pc 2.- con amigos \n"); //pide el modo de juego
    scanf ("%d", &modo);
    if (modo==2){
        printf("Ingrese el nombre del jugador 1 \n"); //los nombres de los jugadores//
        scanf ("%s", &jugador1);
        printf("ingrese el color de las fichas\n");
        printf("1.-Rojo   2.-Azul   3.-Amarillo   4.-Negro   5.-Magenta   6.-Verde\n");
        scanf ("%d", &colo1);
        printf("Ingrese el nombre del jugador 2 \n");
        scanf ("%s", &jugador2);
        printf("1.-Rojo   2.-Azul   3.-Amarillo   4.-Negro   5.-Magenta   6.-Verde\n");
        scanf ("%d", &colo2);
        if (colo2==colo1){
         do{
           printf("ingrese un color diferente \n");
            scanf("%d",&colo2);
          }while (colo2==colo1);
        }
    } else if(modo==1){
            printf("Ingrese el nombre del jugador \n"); //si juega contra el bot pidiria un solo nombre//
            scanf ("%s", &jugador1);
            printf("1.-Rojo   2.-Azul   3.-Amarillo   4.-Negro   5.-Magenta 6.-Verde \n");
            scanf ("%d", &colo1);
            colo2=6;
    }

        printf("Ingrese la cantidad de filas que desea de su conecta 4 : \n"); //pide la cantidad de filas//
        scanf("%d",&n);
        if (n<4){
          do{
           printf("Ingrese la cantidad de filas mayor a 4: \n"); //pide la cantidad de filas//
            scanf("%d",&n);
          }while (n<4); //lo pedira hasta que ingrese un numero<5//
        }
        printf("Ingrese la cantidad de columnas que desea de su conecta 4 : \n");
        scanf("%d",&m);
         if (m<4){
          do{
           printf("Ingrese la cantidad de columnas mayor a 4: \n"); //pide la cantidad de columnas//
            scanf("%d",&m);
          }while (m<4); //lo pedira hasta que ingrese un numero<5//
        }

            matriz=declarar(n,m);

//Preparamos el tablero del juego rellenandolo con 0's
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++){
                matriz[i][j] = 0;
                //cout<<matriz[i][j]<<" ";
            }
          //cout<<" "<<endl;
        }

    //Logica
    int jugador = 0;
    int ultimo = 0;
    do
    {
        int colocarColumna = -1;
        int colocarFila = -1;
        bool columnaTope = true;
        int ultimaJugada = -1;

        if(ultimo == 1){
            jugador = 2;
        }
        else{
            jugador = 1;
        }
        printf("MODO ===> %i | JUGADOR ===> %i\n",modo,jugador);

        if((modo == 2) || (jugador == 1)){

          do{
            printf("Turno del jugador %d - Elije el numero de columna \n",jugador);
           scanf("%d",&colocarColumna);
            colocarColumna--;
            columnaTope = columnaATope(matriz,colocarColumna);
          }while((colocarColumna < 0 || colocarColumna > m) || columnaTope);

          colocarFila = ColocarFichaEn(matriz,colocarColumna,n,m);
          matriz[colocarFila][colocarColumna] = jugador;


        }

        else if((modo == 1)){

          printf("MINMAX Calculandoo... boop beep boop\n");
          Move bestMove = findBestMove(matriz,n,m);
          colocarFila = bestMove.row;
          colocarColumna = bestMove.col;
          matriz[colocarFila][colocarColumna] = jugador;

        }

        Imprimirmatriz(matriz,n,m,colo1,colo2);
        //Revisar si hay un 4 en raya
        if(ganador(matriz,colocarFila,colocarColumna,n,m)){

          jugador == 1 ? printf("FELICIDADES %s !!! HAS GANADO", jugador1) : printf("FELICIDADES %s !!! HAS GANADO", jugador2);
          break;

        }

        ultimaJugada = colocarColumna;

        ultimo = jugador;
        jugador++;
    }
    while(sobranEspaciosLibres(matriz,n,m));

    return 0;
}
