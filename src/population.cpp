/*! @file population.cpp
    @brief Implementation of Population class
*/
#include "population.hpp"

#include <wtl/debug.hpp>
#include <wtl/iostr.hpp>
#include <wtl/random.hpp>
#include <sfmt.hpp>

#include <iostream>

namespace grn {

Population::Population(const size_t n)
: individuals_(n) {HERE;
}

std::ostream& Population::write(std::ostream& ost) const {HERE;
    return ost << individuals_;
}

//! shortcut Population::write(ost)
std::ostream& operator<<(std::ostream& ost, const Population& pop) {
    return pop.write(ost);
}

} // namespace grm
