#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <string>
#include "mtx.hpp"


lock::mtx lk;
size_t g_int;

void inc(size_t i)
{
    lk.lock();
    g_int += i;
    lk.unlock();
}



void test_sum(size_t iters)
{
    std::vector<std::thread> vec;                                                                
    for(size_t i = 1; i <= iters; ++i)
    {
        vec.push_back(std::thread(inc,i));
    }
    
    for(auto & x : vec)
    {
        x.join();
    }
    auto expected_val = (iters * (iters + 1)) / 2; 
    if(g_int != expected_val)
    {
        std::cout << "ERROR| Expected " << expected_val << " | FOUND " << g_int << std::endl;
    }

}

int main(int argc, char* argv[])
{
    size_t iters = std::stoi(argv[1]);
    test_sum(iters);
    return 0;
}

