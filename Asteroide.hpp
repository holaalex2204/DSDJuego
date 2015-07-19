#ifndef __ASTEROIDE_HPP__
#define __ASTEROIDE_HPP__

#include <vector>
#include <stdlib.h>
#include "Vector2D.hpp"

class Asteroide{
	private:
		std::vector<Vector2D> vectores;
		Vector2D direccion;
		double radio;
		float oX;
		float oY;
		int numVertices;
		int dirX;
		int dirY;
		int velocidad;
		int arg;
		double movLineal;
		double resistencia;
	public:
		Asteroide(int);
		int obtenerNumVertices();
		double obtenerX(int);
		double obtenerY(int);
		double obtenerOx();
		double obtenerOy();
		double obtenerRadio();
		Vector2D obtenerDireccion();
		void mover();
		Vector2D rotar(int);
		bool visible();
		void ajustarAngulo();
		double movimientoLineal();
		void cambiarDireccion(Vector2D);
		void cambiaBala(double , int , int , Vector2D);
		double bajaResistencia(double);
};

#endif
