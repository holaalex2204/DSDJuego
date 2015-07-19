salida: main.cpp Game.o
	g++ -std=c++11 main.cpp Game.o Asteroide.o Nave.o Vector2D.o -o salida -lSDL2
Game.o: Game.cpp Asteroide.o Nave.o Game.hpp
	g++ Game.cpp -c
Asteroide.o: Asteroide.cpp Vector2D.o Asteroide.hpp
	g++ Asteroide.cpp -c
Nave.o: Nave.cpp Vector2D.o Nave.hpp
	g++ Nave.cpp -c
Vector2D.o: Vector2D.cpp Vector2D.hpp
	g++ Vector2D.cpp -c
clean:
	rm *.o -f
run: salida
	clear
	./salida 10