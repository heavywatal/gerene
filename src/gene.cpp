/*! @file gene.cpp
    @brief Implementation of Gene class
*/
#include "gene.hpp"

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
boost::program_options::options_description Gene::options_desc() {
    namespace po = boost::program_options;
    po::options_description desc{"Gene"};
    desc.add_options()
    ;
    return desc;
}

Gene::Gene() {
}

Gene::Gene(const std::vector<unsigned int>& coding_funcs) {
}

std::ostream& Gene::write(std::ostream& ost) const {
    return ost << std::make_pair(cis_, cod_);
}

//! shortcut Gene::write(ost)
std::ostream& operator<<(std::ostream& ost, const Gene& x) {
    return x.write(ost);
}

void Gene::test() {HERE;
    Gene x;
    std::cout << x << std::endl;
}

} // namespace grn
