#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "cfield.h"

#define CELL_SIZE 10
#define WINDOW_WIDTH HCELLS * CELL_SIZE
#define WINDOW_HEIGHT VCELLS * CELL_SIZE
#define LINE_WIDTH 1
#define SLEEP_TIME 1000

class CVisualizer {
	private:
		SDL_DisplayMode m_displayMode;
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		CField* m_field;
		void _clear();
		void _draw_rect(size_t x, size_t y);
		void _add_rect(int x, int y);
		void _delete_rect(int x, int y);
		void _redraw(bool do_step);
		void _init();
	public:
		CVisualizer() {}
		~CVisualizer();
		void init();
};
