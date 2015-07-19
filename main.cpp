#include "Game.hpp"

int main(int argc, char* argv[]){
	if(argc==2){
		Game g_game(atoi(argv[1]));
		g_game.init();
		
		while(g_game.isRunning()){
			g_game.running();
			g_game.handleEvents();
			g_game.update();
			g_game.render();
		}g_game.clean();
		
	}return 0;
}