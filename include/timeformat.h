#pragma once
#include "stdafx.h"

using namespace std::chrono;

template <typename Container, typename Fun>
inline void tuple_for_each(const Container& c, Fun fun)
{
    for (auto& e : c)
        fun(std::get<0>(e), std::get<1>(e), std::get<2>(e));
}
 
inline std::string formatDuration(seconds time)
{
    using T = std::tuple<seconds, int, const char *>;
    
    constexpr T formats[] = {
        T{hours(1), 2, ""},
        T{minutes(1), 2, ":"},
        T{seconds(1), 2, ":"}
    };
    
    std::ostringstream o;
    tuple_for_each(formats, [&time, &o](auto denominator, auto width, auto separator) {
        o << separator << std::setw(width) << std::setfill('0') << (time / denominator);
        time = time % denominator;
    });
    return o.str();
}