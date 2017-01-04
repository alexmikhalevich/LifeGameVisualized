#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <thread>
#include "cvisualizer.h"

int main(int argc, char** argv) {
	omp_set_num_threads(omp_get_max_threads());
	CVisualizer* visualizer = new CVisualizer(); 
	visualizer->init();
	delete visualizer;
	return 0;
}
