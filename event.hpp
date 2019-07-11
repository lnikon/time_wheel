#pragma once

#include "signal_value.hpp"
#include "net.hpp"
#include <cstdint>

struct Event
{
    std::size_t time_{0};
    Net* pNet_{nullptr};
    SignalValue value_{SignalValue::DONTCARE};
};
