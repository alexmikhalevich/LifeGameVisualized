#include <vector>
#include <fstream>
#include <string>
#include <omp.h>

#define VCELLS 100
#define HCELLS 100

typedef std::vector<std::vector<bool>> State;

class CField {
	private:
		State m_state;
		void _init_state(State& state, size_t sizex, size_t sizey);
		int _neighbours(size_t x, size_t y) const;
	public:
		CField(const std::string& input);
		CField();
		void step(State& result_state);
		void write_state(const std::string& output) const;
		void add_element(size_t x, size_t y);
		void delete_element(size_t x, size_t y);
		bool cell_state(size_t x, size_t y);
};
