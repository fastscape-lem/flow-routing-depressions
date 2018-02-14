#include "random_benchmark.hpp"
#include <chrono>

#include <xtensor/xtensor.hpp>
#include <xtensor/xrandom.hpp>

using namespace std::literals;


int main(int , char* [])
{

    //for (size_t x = 1; x<50000; x*=2)
    //for (size_t x = 1; x<5000; x+=1)
    //for (size_t x = 4096; x<4097; x*=2)
    //for (size_t x = 16*1024; x<=16*1024; x*=2)
	for (size_t x = 64; x <= 8 * 1024; x +=64) //128 iter max
    {
        std::cout << "Size " << x << std::endl;
        Benchmark::run("fastscape", x, x, 200, 2s, false);
    }
	char c;
	std::cin >> c;
}
