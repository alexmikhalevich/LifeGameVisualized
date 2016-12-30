#include "cvisualizer.h"

CVisualizer::CVisualizer() {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
	}
	int ret = SDL_GetDesktopDisplayMode(0, &m_displayMode);
	m_window = SDL_CreateWindow("'Life' game", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(m_window == NULL) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	}
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(m_renderer == NULL) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	}
}

CVisualizer::~CVisualizer() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void CVisualizer::_clear() {
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255);
	SDL_RenderClear(m_renderer);
	for(int x = 0; x < WINDOW_WIDTH; x+= CELL_SIZE) 
		SDL_RenderDrawLine(m_renderer, x, 0, x, WINDOW_HEIGHT);
	for(int y= 0; y < WINDOW_HEIGHT; x += CELL_SIZE) {
		SDL_RenderDrawLine(m_renderer, 0, y, WINDOW_WIDTH, y);
}

void CVisualizer::redraw() {
	_clear();
}
