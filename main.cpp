#include <iostream>
#include <SDL2/SDL.h>
#include "Board.hpp"
#include "BoardRenderer.hpp"

#define FRAMERATE 60
#define MS_PER_FRAME (1000 / FRAMERATE)


static SDL_Window* window;
static SDL_Renderer* renderer;
static bool running = true;
static BoardRenderer *boardRenderer;

uint8_t init() {	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	window = SDL_CreateWindow(
		"Blacktris",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	Board b(10, 20);
	boardRenderer = new BoardRenderer(renderer, b, 150, 400);
	std::cout << "SDL initialized" << std::endl;
	SDL_SetRenderDrawColor(renderer, 0x2c, 0x2c, 0x2c, 0xff);
	SDL_RenderClear(renderer);
	return 0;
}

void quit() {
	std::cout << "Quitting..." << std::endl;
	running = false;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


void processInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			quit();
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				quit();
			}
		}
	}
}

void update() {
	// TODO
}

void render() {

	SDL_Rect boardSpace = {20, 20, 150, 400};
	boardRenderer->render();
	SDL_RenderCopy(renderer, boardRenderer->_boardTexture, NULL, &boardSpace);
	SDL_RenderPresent(renderer);
}

uint32_t delay(uint32_t lastTick) {
		uint32_t currentTick = SDL_GetTicks();
		uint32_t deltaTime = currentTick - lastTick;
		uint32_t frameTime = MS_PER_FRAME - deltaTime;
		if (frameTime > 0)
		{
			SDL_Delay( frameTime);
			return currentTick + frameTime;
		}
		return currentTick;
}


uint8_t loop() {

	uint32_t lastTick = SDL_GetTicks();
	uint32_t currentTick;
	uint32_t deltaTime;
	
	while (running) {
		//SDL_RenderClear(renderer);
		processInput();
		update();
		render();
		lastTick = delay(lastTick);
	}
	return 0;
}



int main(int argc, char* argv[]) {
	if (init() != 0) {
		return 1;
	}
	loop();

	return 0;
}