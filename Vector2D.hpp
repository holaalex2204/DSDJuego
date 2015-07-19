#ifndef __VECTOR2D_HPP__
#define __VECTOR2D_HPP__

#include <cmath>
const double PI = acos(-1.0);

class Vector2D{
	private:
		float m_x;
		float m_y;
	public:
		Vector2D(float, float);
		Vector2D(void);
		double getX();
		double getY();
		void setX(float);
		void setY(float);
		float length();
		Vector2D normaliza();
		Vector2D rotar(int);
		//Sobrecarga para adición de 2 vectores
		Vector2D operator+(const Vector2D& v2) const {
			return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
		}
		
		friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2){
			v1.m_x += v2.m_x;
			v1.m_y += v2.m_y;
			return v1;
		}
		//Sobrecara para multiplicar un vector por un escalar
		Vector2D operator*(float scalar){
			return Vector2D(m_x * scalar, m_y * scalar);
		}
		
		Vector2D& operator*=(float scalar){
			m_x *= scalar;
			m_y *= scalar;
			return *this;
		}
};

#endif