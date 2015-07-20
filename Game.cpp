#include "Game.hpp"
#include "Vector2D.hpp"
#include <algorithm>
int Game::N_FIGURAS = 1;
int movX=0,movY=0;
int potenciaBala =10;
Game::Game(int numFig){
	numAsteroides=numFig;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Proyecto Final", 250, 0, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

Game::~Game(){
	//delete this;
}

void Game::init(){
	frames=0;
	asteroides.clear();
	for(int i=0 ; i<N_FIGURAS ; i++){
		asteroides.push_back(9+rand()%15);
	} 
	p[N_FIGURAS+2];
	ejecutandose=true;
	start_time = SDL_GetTicks();
}

void Game::handleEvents(){
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_WINDOWEVENT) {
			if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
				ejecutandose=false;
			}
		}if(event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym==SDLK_UP) {
				nave1.girar(1);
				movX=0;
				movY=-5;	
			}else if (event.key.keysym.sym==SDLK_DOWN) {
				nave1.girar(2);
				movX=0;
				movY=5;
			}else if (event.key.keysym.sym==SDLK_RIGHT) {
				nave1.girar(3);
				movX=5;
				movY=0;	
			}else if (event.key.keysym.sym==SDLK_LEFT) {
				nave1.girar(4);
				movX=-5;
				movY=0;
			}else if (event.key.keysym.sym==SDLK_SPACE) {	
				if(potenciaBala>40)
				{
					asteroides.push_back(Asteroide(5));
					N_FIGURAS++;
					asteroides[(N_FIGURAS-1)].cambiaBala(potenciaBala,nave1.getX(),nave1.getY(),Vector2D(movX,movY));
					potenciaBala = 10;	
				}							
			}
		}
	}
}

void Game::clean(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::update(){
	/*frames++;
	if(frames >= 10) {
		printf("FPS %f\n", (float)frames/(SDL_GetTicks()-start_time)*1000);
		frames = 0;
		start_time = SDL_GetTicks();
	}*/
	potenciaBala +=10;
	if(potenciaBala>800){
		potenciaBala = 800;
	}
	for(int i=0; i < N_FIGURAS; ++i) {		
		asteroides[i].mover();
	} 

	//printf("%d - ",(int)asteroides.size());
	for(int i=0 ; i<(int)asteroides.size() ; i++){
		if(!asteroides[i].visible()){
			asteroides.erase(asteroides.begin()+i);
			N_FIGURAS--;
		}
	}//printf("%d\n",(int)asteroides.size());

	for(int i=0 ; i<(int)asteroides.size() ; i++){
		for(int j=i+1 ; j<(int)asteroides.size() ; j++){
			if(abs(asteroides[i].obtenerOx()-asteroides[j].obtenerOx())<=(asteroides[i].obtenerRadio()+asteroides[j].obtenerRadio())-10){
				if(abs(asteroides[i].obtenerOy()-asteroides[j].obtenerOy())<=(asteroides[i].obtenerRadio()+asteroides[j].obtenerRadio())-10){
					//printf("radio: %f\t", (asteroides[i].obtenerRadio()+asteroides[j].obtenerRadio()));
					//printf("x: %d\t-\t", abs(asteroides[i].obtenerOx()-asteroides[j].obtenerOx()));
					//printf("y: %d\n", abs(asteroides[i].obtenerOy()-asteroides[j].obtenerOy()));
					if(asteroides[i].bajaResistencia(0)==-1)
					{						
						if(asteroides[j].bajaResistencia(asteroides[i].movimientoLineal())<0)
						{
							asteroides.erase(asteroides.begin()+j);
							N_FIGURAS--;
						}	
						asteroides.erase(asteroides.begin()+i);
						N_FIGURAS--;					
						continue;
					}
					if(asteroides[j].bajaResistencia(0)==-1)
					{							
						if(asteroides[i].bajaResistencia(asteroides[j].movimientoLineal())<0)
						{
							asteroides.erase(asteroides.begin()+i);
							N_FIGURAS--;
							j--;
						}	
						asteroides.erase(asteroides.begin()+j);
						N_FIGURAS--;
						continue;
					}
					if(asteroides[i].movimientoLineal()>=asteroides[j].movimientoLineal()){
						asteroides[i].cambiarDireccion(asteroides[j].obtenerDireccion());
						asteroides.erase(asteroides.begin()+j);
						N_FIGURAS--;
					}else{
						asteroides[j].cambiarDireccion(asteroides[i].obtenerDireccion());
						asteroides.erase(asteroides.begin()+i);
						N_FIGURAS--;
					}
				}
			}
		}
	}
	while(N_FIGURAS<numAsteroides){
		asteroides.push_back(9+rand()%15);
		//asteroides.emplace_back(5+rand()%15);
		N_FIGURAS++;
	}
	nave1.setX(movX);
	nave1.setY(movY);
}

void Game::render(){
	int i,j;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for(i=0; i < N_FIGURAS; ++i) {
		//SDL_SetRenderDrawColor(renderer, rand()%255, rand()%255, rand()%255, 255);
		//printf("%f\n", asteroides[i].bajaResistencia(0));
		if(asteroides[i].bajaResistencia(0) < 0)
		{
			SDL_SetRenderDrawColor(renderer, 255,255, 0, 0);	
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 171, std::min((asteroides[i].bajaResistencia(0)*255/600),(double)255), 0, 0);	
		}		
		p[asteroides[i].obtenerNumVertices()];
		for(j=0; j < asteroides[i].obtenerNumVertices() ; ++j) {
			p[j].x = asteroides[i].rotar(j).getX();
			p[j].y = asteroides[i].rotar(j).getY();
		}asteroides[i].ajustarAngulo();
		SDL_Point points[1+asteroides[i].obtenerNumVertices()];
		for(j=0; j < asteroides[i].obtenerNumVertices() ; ++j) {
			points[j]=p[j];
		}points[j]=p[0];
		SDL_RenderDrawLines(renderer, points, 1+asteroides[i].obtenerNumVertices());
	}

		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		p[19*25];
		
		for(int i=0, k=0 ; i<nave1.getFilas() ; ++i) {
			for(j=0 ; j<nave1.getColumnas() ; j++,k++){
				if(nave1.getV(i,j)>0){
					p[k].x = nave1.getX()+nave1.getV(i,j);
					p[k].y = nave1.getY()+i;
				}else{
					p[k].x = 0;
					p[k].y = 0;
				}
			}
		}
		SDL_RenderDrawPoints(renderer, p, 19*25);
	
	SDL_RenderPresent(renderer);
	SDL_Delay(175);
	
}

bool Game::running(){}

bool Game::isRunning(){
	return ejecutandose;
}