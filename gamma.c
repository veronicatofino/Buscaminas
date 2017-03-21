#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


typedef	enum {
	TAPADA = 'c', NO_TAPADA = 'o'
}estado;

struct casilla{
	char tipo;  //El tipo de cada casilla 'M' es de mina y 'C' de Casilla.
	int showme; //Especie de Booleano que define si la casilla se destapo previamente.
	int nminas; //Numero de minas que tiene cada casilla
	estado estadoCasilla; //Si está tapada o destapada la casilla
	char etiqueta; //Para saber si tiene una bandera la casilla o no.

};
typedef struct casilla tipocasilla; //El tipo de variable de la casilla
void dibujar(int filas,int cols,tipocasilla** matriz,int juefi, int jueco){   //Dibuja la matriz en el cmd
	int i,j;
	for (i=1;i<filas-1;i++){
		for (j=1;j<cols-1;j++){
			if (matriz[i][j].estadoCasilla==TAPADA){ //Imprime las 'c' que significa que las casillas siguen tapadas.
			printf(" %c |",matriz[i][j].estadoCasilla);
			}
			else if ((matriz[i][j].etiqueta=='F')&&(matriz[i][j].estadoCasilla==NO_TAPADA)){ //Si la matriz en esa posicion se le puso una bandera y ya se destapo en jugar imprime las banderas puestas.
				printf(" %c |",matriz[i][j].etiqueta);
			}

			else if ((matriz[i][j].tipo=='X')&&(matriz[i][j].estadoCasilla==NO_TAPADA)){  //Imprime las minas del tablero cuando pierde
				printf(" %c |",matriz[i][j].tipo);
			}
			else if ((matriz[i][j].estadoCasilla==NO_TAPADA)&&(matriz[i][j].showme==1)){ //Cuando las casillas se destapan y se muestran es decir se abrieron las colaterales.
				printf(" %d |",matriz[i][j].nminas);
			}
			else if ((matriz[i][j].estadoCasilla==NO_TAPADA)&&(matriz[i][j].showme==0)){ //Se destapa la casilla que el jugador escribio.
				printf(" %d |",matriz[i][j].nminas);
				matriz[i][j].showme=1;  //Ya se mostró.

			}

		}
		printf("\n");

	}
}




void clorox (int i, int j, tipocasilla** matriz,int filas,int columnas){ //Función para abrir las casillas laterales cuando la casilla que se escribe es no tiene minas alrededor.
	if ((matriz[i][j].tipo == 'C')&& (matriz[i][j].nminas==0)){ //Cada uno de los if's dice que mientras no haya una mina alredor destape las casillas laterales y les cambie el estado para luego dibujarlas.
				if (matriz[i-1][j-1].tipo != 'm'){
					matriz[i-1][j-1].showme=1;
					matriz[i-1][j-1].estadoCasilla=NO_TAPADA;
				}
				if (matriz[i-1][j].tipo != 'm'){
					matriz[i-1][j].showme=1;
					matriz[i-1][j].estadoCasilla=NO_TAPADA;
				}
				if (matriz[i-1][j+1].tipo != 'm'){
					matriz[i-1][j+1].showme=1;
					matriz[i-1][j+1].estadoCasilla=NO_TAPADA;
				}
				if (matriz[i][j-1].tipo != 'm'){
					matriz[i][j-1].showme=1;
					matriz[i][j-1].estadoCasilla=NO_TAPADA;
				}
				if (matriz[i][j+1].tipo != 'm'){
					matriz[i][j+1].showme=1;
					matriz[i][j+1].estadoCasilla=NO_TAPADA;
				}
				if (matriz[i+1][j-1].tipo != 'm'){
					matriz[i+1][j-1].showme=1;
					matriz[i+1][j-1].estadoCasilla=NO_TAPADA;
				}
				if (matriz[i+1][j].tipo != 'm'){
					matriz[i+1][j].showme=1;
					matriz[i+1][j].estadoCasilla=NO_TAPADA;
				}
				if (matriz[i+1][j+1].tipo != 'm'){
					matriz[i+1][j+1].showme=1;
					matriz[i+1][j+1].estadoCasilla=NO_TAPADA;
				}
	}
}

void alv(tipocasilla** matriz,int filas,int columnas){  //Función con la que el jugador pierde y se cambian las minas y el estado para destaparlas cuando se dibuje.
	for (int i=1;i<filas-1;i++){
		for (int j=1;j<columnas-1;j++){
			if (matriz[i][j].tipo=='m'){
				matriz[i][j].tipo='X';
				matriz[i][j].estadoCasilla=NO_TAPADA;
			} 
		}
	}
}
int Cqn(int filas,int columnas,tipocasilla** matriz,int num,struct timeval ti,struct timeval tf,int juefi,int jueco){ //Función con la que gana
	double tiempo;
	int cont=0;  //Contador que evalua si puso las banderas donde habian minas y a partir de eso retorna un valor.
	int contf=0; //Contador que evalua si la bandera ha sido puesta en la posición corecta
	for (int i=1;i<filas-1;i++){
		for (int j=1;j<columnas-1;j++){
			if ((matriz[i][j].tipo=='m')&&(matriz[i][j].etiqueta=='F')){
				cont++;
			}
			if ((matriz[i][j].etiqueta=='F')&&(matriz[i][j].tipo != 'm')){
				contf=1;
			}
		}
	}
	if ((cont==num)&&(contf==0)){
		printf("\n*******¡¡¡WIIII GANASTE!!!*******\n__________________________________\n\n");
		gettimeofday(&tf,NULL); //Se finaliza de cronometrar el tiempo
		tiempo=((tf.tv_sec - ti.tv_sec));
		if (tiempo >=100){
			double time=tiempo/60;
			printf("Su tiempo fue: %f min\n\n__________________________________\n\n",time);
		}
		else {
			double time=tiempo;
			printf("Su tiempo fue: %f seg\n\n__________________________________\n\n",time);			
		}

		return -1;
	}

	else if ((cont==num)&&(contf==1)){
			printf("\n*******PERDISTE UwU*******\n__________________________________\n\n");
			gettimeofday(&tf,NULL); //Se finaliza de cronometrar el tiempo
			tiempo=((tf.tv_sec - ti.tv_sec));
			if (tiempo >=100){
				double time=tiempo/60;
				printf("Su tiempo fue: %f min\n\n__________________________________\n\n",time);
			}
			else {
				double time=tiempo;
				printf("Su tiempo fue: %f seg\n\n__________________________________\n\n",time);			
			}
			return -1;

	}
	else{
		return 0;
	}
}
void jugar (int filas,int columnas, tipocasilla** matriz,int juefi,int jueco, int num,struct timeval ti,struct timeval tf){ //Funcion con la que el jugador juega en el cmd
	double tiempo;
	int can=0;
	while(can>=0){ //Mientras no pierda (número negativo) que siga preguntando donde quiere poner la fila y la columna
		printf("\nEliga una de las siguientes opciones\n**************************************\n\n 1.Destapar\n 2.Poner bandera \n 3.Quitar bandera\n\n");
		int np;
		scanf("%d",&np);
		int juefi, jueco;
		printf("\nEscriba una fila: "); //La fila que el jugador escoge
		scanf("%d",&juefi);
		printf("Escriba una columna: "); //La columna que el jugador escoge
		scanf("%d",&jueco);
		if ((np==1)&&(juefi>0 && juefi <filas && jueco>0 && jueco<columnas)&& (matriz[juefi][jueco].tipo!='m')){ //La opcion 1 es para destapar casillas, esta condicion dice que no sea una mina para que pueda seguir jugando.
			matriz[juefi][jueco].estadoCasilla=NO_TAPADA;
			clorox(juefi,jueco,matriz,filas,columnas);
			dibujar(filas,columnas,matriz,juefi,jueco);
			

		}
		else if ((np==1)&&(juefi>0 && juefi <filas && jueco>0 && jueco<columnas)&& (matriz[juefi][jueco].tipo=='m')){ //Opcion de destapar pero es una mina y pierde.
			printf("\n*******PERDISTE UwU*******\n__________________________________\n\n");
			alv(matriz,filas,columnas);
			dibujar(filas,columnas,matriz,juefi,jueco);
			gettimeofday(&tf,NULL); //Se finaliza de cronometrar el tiempo
			tiempo=((tf.tv_sec - ti.tv_sec));
			if (tiempo >=100){
				double time=tiempo/60;
				printf("Su tiempo fue: %f min\n\n__________________________________\n\n",time);
			}
			else {
				double time=tiempo;
				printf("Su tiempo fue: %f seg\n\n__________________________________\n\n",time);			
			}
			break;

		}
		else if ((np==2)&&(juefi>0 && juefi <filas && jueco>0 && jueco<columnas)){ //La opción (np) 2 es para poner una bandera
			matriz[juefi][jueco].etiqueta='F';
			matriz[juefi][jueco].estadoCasilla=NO_TAPADA;
			dibujar(filas,columnas,matriz,juefi,jueco);

		}
		can=Cqn(filas,columnas,matriz,num,ti,tf,juefi,jueco); //Se evalua siempre y si retorna -1 significa que ganó y sale del while y acaba el juego
		if (np==3){
			if (matriz[juefi][jueco].etiqueta=='F'){ //Esto certifica que haya puesto una bandera donde no habia mina y por consiguiente pierde, si no sigue jugando
				matriz[juefi][jueco].etiqueta='N';
				matriz[juefi][jueco].estadoCasilla=TAPADA;
				dibujar(filas,columnas,matriz,juefi,jueco);
			}
		
		} 
	}

}

void MinarCampo(int filin,int colin,tipocasilla** matriz,int filas,int columnas,int v){ //Asigna las minas a lo largo del tablero
	srand(time(NULL));
	for (int i=0; i <v; i++){ //Pone el numero de minas en el tablero
		int mfilas=rand()%filas;
		int mcolumnas=rand()%columnas;
		if (matriz[mfilas][mcolumnas].tipo != 'm'&& mfilas>0 && mfilas<filas-1 && mcolumnas>0 && mcolumnas<columnas-1 && (colin !=mcolumnas || filin != mfilas)){ //Certifica que la persona no pierda a la primera es decir que no se ponga bomba en la fila y columan inicial y que las bombas solo se pongan en el tablero y no en la amtriz aumentada, y que no se sobre escriban las bombas.
			matriz[mfilas][mcolumnas].tipo ='m';
		}
		else { //Si puso una bomba donde ya habia una se resta uno para que se ponga en otro sitio.
			i=i-1;
		}
	}	
	for (int i =1; i <filas-1; i++){ //Asigna los numeros que tienen bombas alrededor.
		
		for (int j=1; j < columnas-1; j++){
			int contminas=0;
			
			if (matriz[i][j].tipo!='m'){
			if (matriz[i-1][j-1].tipo == 'm'){
				contminas++;
			}
			if (matriz[i-1][j].tipo == 'm'){
				contminas++;
			}
			if (matriz[i-1][j+1].tipo == 'm'){
				contminas++;
			}
			if (matriz[i][j-1].tipo == 'm'){
				contminas++;
			}
			if (matriz[i][j+1].tipo == 'm'){
				contminas++;
			}
			if (matriz[i+1][j-1].tipo == 'm'){
				contminas++;
			}
			if (matriz[i+1][j].tipo == 'm'){
				contminas++;
			}
			if (matriz[i+1][j+1].tipo == 'm'){
				contminas++;
			}
		}

		matriz[i][j].nminas=contminas;
		}
	}	
}



tipocasilla **creartablero(int filas,int columnas){ //Crea el tablero con la matriz aumentada
	tipocasilla **matriz;
	matriz=(tipocasilla**)malloc(filas*sizeof(tipocasilla*));
	for (int i=0;i<filas;i++){
		matriz[i]=(tipocasilla*)malloc(columnas*sizeof(tipocasilla));

		for (int j=0;j<columnas;j++){
			matriz[i][j].estadoCasilla=TAPADA;
			matriz[i][j].tipo='C';
			matriz[i][j].showme=0;
			matriz[i][j].etiqueta='N';
		}
	}
	return matriz;
}



void main(int argc, char* argv[]){
	tipocasilla **tablero; //El tablero o la matriz donde se va a jugar
	printf("\n NIVEL PLS:\n************\n\n1.Easy \n2.Medio\n3.Hardcore \n4.Personalizado\n\n"); //El nivel de dificultad.
	int lvl;
	scanf("%d",&lvl);
	int filas;
	int columnas;
	int num;
	if (lvl==4){ //Opcion cuatro (Personalizado)
		printf("\nEscriba el numero de filas: ");
		scanf("%d",&filas);
		filas=filas+2;
		printf("Escriba el numero de columnas: ");
		scanf("%d",&columnas);
		columnas=columnas+2;
		printf("Escriba un numero de minas: ");
		scanf("%d",&num);
	}
	if(lvl==3){ //Opcion tres (Dificil)
		filas=18;
		columnas=32;
		num=99;
	}
	if(lvl==2){ //Opcion dos (Medio)
		filas=18;
		columnas=18;
		num=40;
	}
	if (lvl==1){// Opcion uno (Facil)
		filas=10;
		columnas=10;
		num=10;
	}
	int filin=0;
	int colin=0;
	int juefi=0;
	int jueco=0;
	printf("Escriba una fila inicial: ");
	scanf("%d",&filin);
	printf("Escriba una columna inicial: ");
	scanf("%d",&colin);
	struct timeval ti,tf; // Estructura contenida por la libreria <sys/time.h> que incluye segundos y microsegundos
	tablero=creartablero(filas,columnas);
	tablero[filin][colin].showme=1;
	tablero[filin][colin].estadoCasilla=NO_TAPADA;
	MinarCampo(filin,colin,tablero,filas,columnas,num);
	clorox(filin,colin,tablero,filas,columnas);
	dibujar(filas,columnas,tablero,juefi,jueco);
	gettimeofday (&ti,NULL); //Se incia a cronometrar el tiempo
	jugar (filas,columnas,tablero,juefi,jueco,num,ti,tf);

}
