#include<iostream>
#include<string>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<dos.h>

using namespace std;
int f,c,num; //auxiliares ..F guarda la posicion actual de la fila;C la posicion actual de la columna                                                
float matriz[6][5] ={{0,0,0,0,0},
					 {0,1,1,1,0},
					 {0,1,0,1,0},
					 {0,1,1,1,0},
					 {0,1,1,1,0},//4.2derrota 4.3 victoria
					 {0,0,0,0,0}};
int axis[100][2];//Registra el movimiento hecho por el robot
int movimiento(int m);//funcion movimiento de los robots exploradores
int movRey();//funcion de movimiento del robot rey
void valores();//Funcion de perdida
void valp();//Funcion de recompenza


int main(){
	srand(time(NULL));//Semilla de los numeros aleatorios
	
	//for(int q=0;q<100;q++) for(int w=0;w<2;w++) axis[q][w]=-1;
	//******
	int robots;
	int fin;//auxiliar
	int deaths=0,wins=0;//contadores de muertes y victorias
	char coor[25];//String char auxiliar para el registro del camino(Almcena un movimiento)
	char log[1000]="";//String principal donde se almacena el camino de cada robot(Almacena todos los movimientos)
	cout<<"Cuantos robots Exploradores desea enviar: ";
	cin>>robots;
	char mov[robots][1000];//almacena el string de movimientos de cada robot
	char rmov[1][100];//Almacena el movimiento del rey
    for(int i=0;i<robots;i++){//Se comienza han colocar los robots exploradores
    	for(int q=0;q<100;q++) for(int w=0;w<2;w++) axis[q][w]=-1; //Registro axis -- inicializamos el vector en -1,un valor que jamas se utilizara
    	int xc=0;
    	//el robot comienza en la posicion de salida (1,1)
    	f=1;
    	c=1;
    		do{
    			num=1+rand()%(5-1);//Se genera un numero aleatoria entre 1-4 cada uno representa una direccion de movimiento(arriba,abajo....)
    			movimiento(num);//Se llama a la funcion movimiento del robot (Robot explorador)
    			//Almacena el movimiento
				sprintf(coor,"%i",f);
    			strcat(log,"[");
    			strcat(log,coor);
    			strcat(log,",");
    			sprintf(coor,"%i",c);
    			strcat(log,coor);
    			strcat(log,"]");
    			
    			axis[xc][0]=f;//Registra la posicion de la fila en la matriz
    			axis[xc][1]=c;//Registra la posicion de la columna
    			if(xc<50) xc++;
    		if((f==4&&c==2)||(f==4&&c==3)) fin=1;//Condicional de victoria y derrota (4,3 y 4,2 respectivamente)
			}while(fin!=1);	
		fin=0;//se reinicia la condicion
		printf("Robot No. [%d] ",i);
		if(f==4&&c==3){//Evalua si el robot salio victorioso
			wins++;
			valp();//Si fue victorioso activa la funcion recompenza
		 	cout<<"---->Ganador"<<endl;
		 	strcat(log,"\nGanador ");}
		if(f==4&&c==2){//Evalua si el robot perdio
			valores();//Si perdio activa la funcion de descuento o perdida
			deaths++;
			cout<<"---->Muerto"<<endl;
			strcat(log,"\nMuerto ");
			}
			strcat(mov[i],log);//Guarda el camino recorrido 
			strcpy(log,"");
	}
		
		int oc,r,on=0;//auxiliares
		while(on==0){
		cout<<"\n1.-Ver historial\n2.-Soltar al REY\n0.-Salir"<<endl;
		cin>>oc;
		switch(oc){
			case 0:
				on=1;
			break;
			case 1:
				cout<<"No. Robot: ";//Se puede observar el recorrido de cualquier robot
				cin>>r;
				cout<<endl;
				cout<<mov[r];
			break;
			case 2:
				int abucle=0;//auxiliar antibucle
				f=1;//filas
				c=1;//columnas
				do{
				movimiento(movRey());//Se convoca al robot especial que usara la matriz ya modifica por las funciones recompenza/perdida
				//Se almacena su recorrido para demostracion grafica
				sprintf(coor,"%i",f);
    			strcat(log,"[");
    			strcat(log,coor);
    			strcat(log,",");
    			sprintf(coor,"%i",c);
    			strcat(log,coor);
    			strcat(log,"]");
				system("cls");
    			printf("[%d,%d]",f,c);
    			// Impresion Grafica
    			for(int x=0;x<6;x++){
    				cout<<endl;
    				for(int y=0;y<5;y++){
    					if(f==x && c==y) printf("[x]");
    					else {
						if(matriz[x][y]==0) printf("[*]");
					    else{
						if(x==4&&y==2) printf("[D]");
						else{
						if(x==4&&y==3) printf("[V]");
						else printf("[ ]");
						} 
						}	}
					}
				//******************
			}
				abucle++;//contador de movimientos(Si llega a un tal numero considera que se ha entrado en bucle)
				matriz[f][c]=matriz[f][c]*0.4;//Dificulta que entre en bucle,Reduce el valor del paso anterior,(Parametro)
				if((f==4&&c==2)||(f==4&&c==3)||abucle==15) fin=1;//detecta si el Rey Gano,murio o entro en bucle
				}while(fin!=1);
			    
			    
				cout<<endl;
				if(abucle==15){//Si entra en bucle
					cout<<"Es necesaria mas Exploracion"<<endl;
					main();//recusion en caso de bucle
				}
				 //Conclusion de los exploradores;Si gano;Si perdio
				if(f==4&&c==3) {
				cout<<"El rey llego al destino"<<endl;
				cout<<log<<endl;
				}
				else {
				cout<<"El rey ha muerto"<<endl;
				cout<<log<<endl;
				}
				
				on=1;
				break;
		}}
		//resultado del experimento
		cout<<"\n"<<deaths<<" Robot(s) murieron por el rey"<<endl;
		cout<<"Robots Sobrevivientes "<<wins<<endl;
		//Impresion de la matriz final con los indices nuevos
		for(int x=0;x<6;x++){
    				cout<<endl;
    				for(int y=0;y<5;y++){
    				printf("[%f]",matriz[x][y]);
					}
	}}
 //Fuciones para el cambio de valores
 void valores(){
 	int x=0;
 	while(axis[x][1]!=-1){
 	matriz[axis[x][0]][axis[x][1]]=(matriz[axis[x][0]][axis[x][1]])*0.9;//Si el robot pierde multiplica cada casilla que recorrio por 0.9
	x++;
	}
 }
 void valp(){
 	int x=0;
 	while(axis[x][1]!=-1){
 	matriz[axis[x][0]][axis[x][1]]=(matriz[axis[x][0]][axis[x][1]])+0.04;//Si el robot gana otorga ha cada casilla una de recompenza de 0.04
	x++;
	}
 }
 //Funciones de Movimientos
int movRey(){
	int eleccion;
	int faux=f;
	int caux=c;
	//Compara las cuatro direcciones de movimiento y regresa un numero dependiento de cual es la mayor 1-4
	//despues ingresa este numero en la funcion "movimiento"
	if(matriz[faux-1][c]>matriz[faux+1][c] && matriz[faux-1][c]>matriz[faux][c-1] && matriz[faux-1][c]>matriz[faux][c+1]) return 1;
	if(matriz[faux+1][c]>matriz[faux-1][c] && matriz[faux+1][c]>matriz[faux][c-1] && matriz[faux+1][c]>matriz[faux][c+1]) return 2;
	if(matriz[faux][c-1]>matriz[faux][c+1] && matriz[faux][c-1]>matriz[faux+1][c] && matriz[faux][c-1]>matriz[faux-1][c]) return 4;
	if(matriz[faux][c+1]>matriz[faux][c-1] && matriz[faux][c+1]>matriz[faux+1][c] && matriz[faux][c+1]>matriz[faux-1][c]) return 3;
}
int movimiento(int m){//Funcion movimiento principal
	//arriba
	if(m == 1){
		f--;
		if(matriz[f][c]==0) f++;
	}
	//abajo
		if(m == 2){
		f++;
		if(matriz[f][c]==0) f--;
	}
	//derecha
		if(m == 3){
		c++;
		if(matriz[f][c]==0) c--;
	}
	//izquierda
		if(m == 4){
		c--;
		if(matriz[f][c]==0) c++;
	}
	return 0;
}
