/*! @file population.cpp
    @brief Implementation of Population class
*/
#include "population.hpp"
#include "individual.hpp"

#include <wtl/debug.hpp>
#include <wtl/iostr.hpp>
#include <wtl/prandom.hpp>
#include <sfmt.hpp>

#include <iostream>

namespace grn {

//! Program options
/*! @ingroup params
    @return Program options description

    Command line option | Symbol         | Variable
    ------------------- | -------------- | -------------------------------
*/
boost::program_options::options_description Population::options_desc() {
    namespace po = boost::program_options;
    po::options_description desc{"Individual"};
    desc.add_options()
    ;
    return desc;
}

std::ostream& Population::write(std::ostream& ost) const {HERE;
    return ost;
}

//! shortcut Population::write(ost)
std::ostream& operator<<(std::ostream& ost, const Population& pop) {
    return pop.write(ost);
}

void Population::test() {HERE;
    Population x;
    std::cout << x << std::endl;
}

} // namespace grm
