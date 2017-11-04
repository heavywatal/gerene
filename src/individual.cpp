/*! @file individual.cpp
    @brief Implementation of Individual class
*/
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
boost::program_options::options_description Individual::options_desc() {
    namespace po = boost::program_options;
    po::options_description desc{"Individual"};
    desc.add_options()
    ;
    return desc;
}

std::ostream& Individual::write(std::ostream& ost) const {
    return ost;
}

//! shortcut Individual::write(ost)
std::ostream& operator<<(std::ostream& ost, const Individual& x) {
    return x.write(ost);
}

void Individual::test() {HERE;
    Individual x;
    std::cout << x << std::endl;
}

} // namespace grn
