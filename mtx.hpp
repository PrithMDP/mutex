#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <string>

namespace lock{
struct mtx
{
    std::atomic<int> counter{0};

    bool try_lock()
    {
        int expected = 0;
        return counter.compare_exchange_strong(expected,1,std::memory_order_acquire);
    }

    void lock()
    {
        int expected = 0;
        while(!counter.compare_exchange_strong(expected,1,std::memory_order_acquire))
        {
            expected = 0; 
        }
    }
    
    void unlock()
    {
        counter.store(0,std::memory_order_release);
    }
    
};
}
