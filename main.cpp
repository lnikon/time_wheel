#include "list/list.hpp"
#include "ring_buffer/ring_buffer.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    constexpr auto size = 5;
    RingBuffer<int> rb(size);

    rb.push( 1 + 3 * 4);
    rb.push(9);
    rb.push(4);

    rb.pop();
    rb.pop();

    rb.push(-123);

    std::cout << std::endl;

    return 0;
}
