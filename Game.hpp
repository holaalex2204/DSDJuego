#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <vector>
#include "Asteroide.hpp"
#include "Nave.hpp"

class Game{
	private:
		static int N_FIGURAS;
		int numAsteroides;
		Nave nave1;
		std::vector <Asteroide> asteroides;
		bool ejecutandose;
		int frames;
		int start_time;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Point p[];
		SDL_Event event;
		
	public:
		Game(int);
		~Game();
		void init();
		void render();
		void update();
		void handleEvents();
		void clean();
		bool running();
		bool isRunning();
};

#endif
