#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "cvisualizer.h"

#ifdef MULTITHREAD
#define MAX_THREADS 12
#endif

int main(int argc, char** argv) {
	size_t time = 0;
	size_t etalon = 0;
	if(argc < 3) {
		std::cout << "Missing arguments!" << std::endl;
		return -1;
	}
	for(int i = 1; i < argc; ++i) {
		if(strcmp(argv[i], "--time") == 0 || strcmp(argv[i], "-t") == 0)
			time = atoi(argv[++i]);
	}
	std::ofstream out_time("out.dat");
	std::ofstream out_eff("eff.dat");

	omp_set_num_threads(omp_get_max_threads());
	CField* field = new CField("state.dat");
	CVisualizer* visualizer = new CVisualizer(); 
	State cur_state;
	double begin, end;
	while(time != 0) {
		begin = omp_get_wtime();
		field->step(cur_state);
		visualizer->redraw(cur_state);
		--time;
		end = omp_get_wtime();
		std::chrono::duration<double, std::milli> timespan = 1000 - (end - begin) * 1000;
		std::this_thread::sleep_for(timespan);
	}
	field->write_state("life.dat");
	delete field;
	return 0;
}
