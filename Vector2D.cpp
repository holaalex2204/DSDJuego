#include "Vector2D.hpp"
#include <stdio.h>

Vector2D::Vector2D(float xx, float yy):m_x(xx),m_y(yy){}
Vector2D::Vector2D(void):m_x(0),m_y(0){}
double Vector2D::getX(){return m_x;}
double Vector2D::getY(){return m_y;}
void Vector2D::setX(float xx){m_x=m_x+xx;}
void Vector2D::setY(float yy){m_y=m_y+yy;}
float Vector2D::length(){
	return pow(pow(m_x,2)+pow(m_y,2),0.5);
}
Vector2D Vector2D::normaliza(){
	float len=length();
	return Vector2D(m_x/len, m_y/len);
}
Vector2D Vector2D::rotar(int angulo){
	return Vector2D(m_x*cos(angulo*PI/180)-m_y*sin(angulo*PI/180), m_x*sin(angulo*PI/180)+m_y*cos(angulo*PI/180));
}