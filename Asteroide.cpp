#include "Asteroide.hpp"
#include <stdio.h>

Asteroide::Asteroide(int n):numVertices(n){
	oX=400,oY=0;
	Vector2D direccion(1+rand()%10,1+rand()%10);
	double anguloCentral=(360/numVertices);
	double angulo=0;
	radio=20+rand()%80;
	velocidad=((100-radio)/3)+1;
	arg=0;
	switch(rand()%4){
		case 0:
			oX=-105;
			oY=-105+rand()%755;
			break;
		case 1:
			oX=950;
			oY=-105+rand()%755;
			break;
		case 2:
			oX=-105+rand()%955;
			oY=-105;
			break;
		case 3:
			oX=-105+rand()%955;
			oY=755;
			break;
	}

	for(int i=0 ; i<numVertices ; i++){
		int argumento=angulo+(rand()%(int)(anguloCentral));
		switch(rand()%4){
			case 0:
				vectores.push_back(Vector2D(3+rand()%3+radio*cos(argumento*PI/180),radio*sin(argumento*PI/180)));
				break;
			case 1:
				vectores.push_back(Vector2D(-3-rand()%3+radio*cos(argumento*PI/180),radio*sin(argumento*PI/180)));
				break;
			case 2:
				vectores.push_back(Vector2D(radio*cos(argumento*PI/180),3+rand()%3+radio*sin(argumento*PI/180)));
				break;
			case 3:
				vectores.push_back(Vector2D(radio*cos(argumento*PI/180),-3-rand()%3+radio*sin(argumento*PI/180)));
				break;
		}
		//vectores.push_back(Vector2D(radio*cos(angulo*PI/180)+oX,radio*sin(angulo*PI/180)+oY));
		angulo+=anguloCentral;
	}
	
	switch(rand()%4){
		case 0:
			dirX=-(velocidad*direccion.normaliza().getX());
			dirY=-(velocidad*direccion.normaliza().getY());
			break;
		case 1:
			dirX=-(velocidad*direccion.normaliza().getX());
			dirY=velocidad*direccion.normaliza().getY();
			break;
		case 2:
			dirX=velocidad*direccion.normaliza().getX();
			dirY=-(velocidad*direccion.normaliza().getY());
			break;
		case 3:
			dirX=velocidad*direccion.normaliza().getX();
			dirY=velocidad*direccion.normaliza().getY();
			break;
	}
	movLineal = radio*velocidad;
	resistencia = radio*6;
}

int Asteroide::obtenerNumVertices(){
	return numVertices;
}

double Asteroide::obtenerX(int v){
	return vectores[v].getX()+oX;
}

double Asteroide::obtenerY(int v){
	return vectores[v].getY()+oY;
}

double Asteroide::obtenerOx(){
	return oX;
}

double Asteroide::obtenerOy(){
	return oY;
}

double Asteroide::obtenerRadio(){
	return radio;
}

double Asteroide::movimientoLineal(){
	return movLineal;
}

Vector2D Asteroide::obtenerDireccion(){
	Vector2D direccion(dirX,dirY);
	return 	direccion;
}

void Asteroide::cambiarDireccion(Vector2D vDir){
	Vector2D direccion(dirX+vDir.getX(),dirY+vDir.getY());
	dirX=velocidad*direccion.normaliza().getX();
	dirY=velocidad*direccion.normaliza().getY();
}

void Asteroide::mover(){
	oX=oX+dirX;
	oY=oY+dirY;
}
Vector2D Asteroide::rotar(int v){
	Vector2D v2(vectores[v].rotar(arg).getX()+oX, vectores[v].rotar(arg).getY()+oY);
	return v2;	
}

void Asteroide::ajustarAngulo(){
	arg+=(velocidad/5)+1;
	if(arg>=360){
		arg=0;
	}
}

bool Asteroide::visible(){
	if(oX<-200){
		return false;
	}else if(oX>1000){
		return false;
	}else if(oY<-200){
		return false;
	}else if(oY>1000){
		return false;
	}else{
		return true;
	}
}
void Asteroide::cambiaBala(double moviLineal, int x, int y, Vector2D direccion)
{
	//movimientoLineal equivale al poder de la bala
	movLineal = moviLineal;
	numVertices = 25;
	double anguloCentral=(360/numVertices);
	double angulo=0;
	radio = 8*moviLineal/800;
	oX = x;
	oY = y;
	resistencia = -1;
	velocidad=((150-radio)/3)+1;
	vectores.clear();
	for(int i=0 ; i<numVertices ; i++){
		vectores.push_back(Vector2D(radio*cos(angulo*PI/180),radio*sin(angulo*PI/180)));
		angulo+=anguloCentral;
	}
	dirX=(velocidad*direccion.normaliza().getX());
	dirY=(velocidad*direccion.normaliza().getY());
}
double Asteroide::bajaResistencia(double valor)
{
	resistencia = resistencia -valor;
	return resistencia;
}