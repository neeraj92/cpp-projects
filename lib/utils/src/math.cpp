#include "utils/math.h"
#include <limits>

namespace utils {

auto nearest_greater_power_of_2(std::size_t value) -> std::size_t
{
    // capping this when we cant round up
    if (value > std::numeric_limits<std::size_t>::max() / 2) {
        return std::numeric_limits<std::size_t>::max() / 2;
    }

    std::size_t return_value{1};

    while (return_value < value) {
        return_value *= 2;
    }

    return return_value;
}

}  // namespace utils
