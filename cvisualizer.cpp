#include "cvisualizer.h"

CVisualizer::~CVisualizer() {
	if(m_field) delete m_field;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void CVisualizer::_init() {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
	}
	int ret = SDL_GetDesktopDisplayMode(0, &m_displayMode);
	m_window = SDL_CreateWindow("Life game", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(m_window == NULL) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	}
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(m_renderer == NULL) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	}
	m_field = new CField();
	_clear();
}

void CVisualizer::_clear() {
	std::cout << "clear" << std::endl;
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	SDL_RenderClear(m_renderer);
}

void CVisualizer::_add_rect(int x, int y) {
	std::cout << "add rect" << std::endl;
	m_field->add_element(x / CELL_SIZE, y / CELL_SIZE);
}

void CVisualizer::_delete_rect(int x, int y) {
	std::cout << "delete rect" << std::endl;
	m_field->delete_element(x / CELL_SIZE, y / CELL_SIZE);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	_draw_rect(x / CELL_SIZE, y / CELL_SIZE);
}

void CVisualizer::_draw_rect(size_t x, size_t y) {
	std::cout << "draw rect" << std::endl;
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x * CELL_SIZE; 
	rect->y = y * CELL_SIZE;
	rect->w = CELL_SIZE;
	rect->h = CELL_SIZE;
	SDL_RenderDrawRect(m_renderer, rect);
	SDL_RenderFillRect(m_renderer, rect);
	delete rect;
}

void CVisualizer::_redraw(bool do_step) {
	State state;
	if(do_step) m_field->step();
	m_field->get_state(state);
	_clear();
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	size_t xsize = state.size();
	size_t ysize = state[0].size();
	for(size_t x = 0; x < xsize; ++x) 
		for(size_t y = 0; y < ysize; ++y) 
			if(state[x][y]) _draw_rect(x, y); 
	SDL_RenderPresent(m_renderer);
}

void CVisualizer::init() {
	_init();
	SDL_Event event;
	bool quit = false;
	bool process = false;
	unsigned int last_time = 0, current_time;
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) 
				quit = true;
			else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				if(!m_field->cell_state(event.button.x / CELL_SIZE, event.button.y / CELL_SIZE))
					_add_rect(event.button.x, event.button.y);
				else
					_delete_rect(event.button.x, event.button.y);
			}
			else if(event.type == SDL_KEYDOWN) {
				if(event.key.keysym.sym == SDLK_RETURN) 
					process = true;
			}
		}
		current_time = SDL_GetTicks();
		if(current_time > last_time + SLEEP_TIME) {
			last_time = current_time;
			_redraw(process);
		}
	}
}
