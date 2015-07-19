#ifndef __Nave_HPP__
#define __Nave_HPP__

#include "Vector2D.hpp"
#include <iostream>
#include <stdlib.h>

class Nave{
	private:
		int oX,oY;
		int filas,columnas;
		int **cubierta=NULL;//[19][25];
		Vector2D direccion;
	public:
		Nave();
		int getV(int,int);
		int getX();
		int getY();
		void setX(int);
		void setY(int);
		void girar(int);
		int getFilas();
		int getColumnas();
		void dispara();
};

#endif
