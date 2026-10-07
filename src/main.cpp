#include <iostream>

#include "engine_info.hpp"

int main()
{
    std::cout << chess::engine_name() << " by " << chess::engine_author()
              << '\n';
    return 0;
}
