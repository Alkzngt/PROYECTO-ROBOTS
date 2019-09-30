#include<iostream>
#include<string>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<dos.h>

using namespace std;

int f,c,num;                                                       //Eslabon ganador
float matriz[6][5] ={{0,0,0,0,0},{0,1,1,1,0},{0,1,0,1,0},{0,1,1,1,0},{0,1,1,1,0},{0,0,0,0,0}};//4.2derrota 4.3 victoria
int axis[100][2];
int movimiento(int m);
int movRey();
void valores();
void valp();


int main(){
	srand(time(NULL));
	//Registro axis
	
	
	for(int q=0;q<100;q++) for(int w=0;w<2;w++) axis[q][w]=-1;
	//******
	int robots;
	int fin;
	int deaths=0,wins=0;
	char coor[25];
	char log[1000]="";
	cout<<"Cuantos robots Exploradores desea enviar: ";
	cin>>robots;
	char mov[robots][1000];
	char rmov[1][100];
    for(int i=0;i<robots;i++){
    	for(int q=0;q<100;q++) for(int w=0;w<2;w++) axis[q][w]=-1;
    	int xc=0;
    	f=1;
    	c=1;
    		do{
    			num=1+rand()%(5-1);
    			movimiento(num);
    			sprintf(coor,"%i",f);
    			strcat(log,"[");
    			strcat(log,coor);
    			strcat(log,",");
    			sprintf(coor,"%i",c);
    			strcat(log,coor);
    			strcat(log,"]");
    			
    			axis[xc][0]=f;
    			axis[xc][1]=c;
    			if(xc<50) xc++;
    		/*	if(robots==1){
    				system("cls");
    				printf("[%d,%d]",f,c);
    			for(int x=0;x<6;x++){
    				cout<<endl;
    				for(int y=0;y<5;y++){
    					if(f==x && c==y) printf("[x]");
    					else printf("[%.4f]",matriz[x][y]);
					}
				}Sleep(20);
    			cout<<endl;
				}*/
    			
    			
    		if((f==4&&c==2)||(f==4&&c==3)) fin=1;
			}while(fin!=1);
		fin=0;
		printf("Robot No. [%d] ",i);
		if(f==4&&c==3){
			wins++;
			valp();
		 	cout<<"---->Ganador"<<endl;
		 	strcat(log,"\nGanador ");}
		if(f==4&&c==2){
			valores();
			deaths++;
			cout<<"---->Muerto"<<endl;
			strcat(log,"\nMuerto ");
			}
			strcat(mov[i],log);
			strcpy(log,"");
	}
		
		int oc,r,on=0;
		while(on==0){
		cout<<"\n1.-Ver historial\n2.-Soltar al REY\n0.-Salir"<<endl;
		cin>>oc;
		switch(oc){
			case 0:
				on=1;
			break;
			case 1:
				cout<<"No. Robot: ";
				cin>>r;
				cout<<endl;
				cout<<mov[r];
			break;
			case 2:
				int abucle=0;
				f=1;
				c=1;
				do{
				movimiento(movRey());
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
				abucle++;//contador de movimientos
				matriz[f][c]=matriz[f][c]*0.9;//Dificulta que entre en bucle
				if((f==4&&c==2)||(f==4&&c==3)||abucle==15) fin=1;
				}while(fin!=1);
			    
			    
				cout<<endl;
				if(abucle==15){
					cout<<"Es necesaria mas Exploracion"<<endl;
					main();//recusion en caso de bucle
				}
				 //Conclusion de los exploradores
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
 	matriz[axis[x][0]][axis[x][1]]=(matriz[axis[x][0]][axis[x][1]])*0.9;
	x++;
	}
 }
 void valp(){
 	int x=0;
 	while(axis[x][1]!=-1){
 	matriz[axis[x][0]][axis[x][1]]=(matriz[axis[x][0]][axis[x][1]])+0.04;
	x++;
	}
 }
 //Funciones de Movimientos
int movRey(){
	int eleccion;
	int faux=f;
	int caux=c;
	if(matriz[faux-1][c]>matriz[faux+1][c] && matriz[faux-1][c]>matriz[faux][c-1] && matriz[faux-1][c]>matriz[faux][c+1]) return 1;
	if(matriz[faux+1][c]>matriz[faux-1][c] && matriz[faux+1][c]>matriz[faux][c-1] && matriz[faux+1][c]>matriz[faux][c+1]) return 2;
	if(matriz[faux][c-1]>matriz[faux][c+1] && matriz[faux][c-1]>matriz[faux+1][c] && matriz[faux][c-1]>matriz[faux-1][c]) return 4;
	if(matriz[faux][c+1]>matriz[faux][c-1] && matriz[faux][c+1]>matriz[faux+1][c] && matriz[faux][c+1]>matriz[faux-1][c]) return 3;
}
int movimiento(int m){
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
