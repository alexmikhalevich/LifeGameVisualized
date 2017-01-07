#include <vector>
#include <fstream>
#include <string>
#include <omp.h>

#define VCELLS 50
#define HCELLS 50

typedef std::vector<std::vector<bool>> State;

class CField {
	private:
		State m_state;
		void _init_state(State& state, size_t sizex, size_t sizey);
		int _neighbours(size_t x, size_t y) const;
	public:
		CField(const std::string& input);
		CField();
		void step();
		void write_state(const std::string& output) const;
		void add_element(size_t x, size_t y);
		void delete_element(size_t x, size_t y);
		bool cell_state(size_t x, size_t y);
		void get_state(State& state) const;
};
