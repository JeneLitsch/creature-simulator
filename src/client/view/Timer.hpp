#include <cstdint>
struct speed {
    double base;
    double duration;
};

class Timer {
	public:
		Timer(uint16_t &base): base(base) {
			this->time = 1.0/static_cast<double>(base);
		}
		// Returns true every x seconds
		bool operator()(double dt) {
			this->time -= dt;
			bool finished = time <= 0.0; 
			if(finished) {
				this->time = 1.0/static_cast<double>(base);
			}
			return finished;
		}
	private:
        uint16_t& base;
		double time;
	};
