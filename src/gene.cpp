/*! @file gene.cpp
    @brief Implementation of Gene class
*/
#include "gene.hpp"

#include <wtl/debug.hpp>
#include <wtl/iostr.hpp>
#include <wtl/random.hpp>
#include <sfmt.hpp>
#include <boost/program_options.hpp>

#include <iostream>

namespace grn {

size_t Gene::NUM_CRES_ = 20u;

//! Program options
/*! @ingroup params
    @return Program options description

    Command line option | Symbol         | Variable
    ------------------- | -------------- | -------------------------------
    `-L,--cres`         | \f$L\f$        | NUM_CRES_
*/
boost::program_options::options_description Gene::options_desc() {
    namespace po = boost::program_options;
    po::options_description desc{"Gene"};
    desc.add_options()
      ("cres,L", po::value(&NUM_CRES_)->default_value(NUM_CRES_))
    ;
    return desc;
}

Gene::Gene() {
    cis_.reserve(NUM_CRES_);
    for (size_t i=0; i<NUM_CRES_; ++i) {
        cis_.emplace(wtl::sfmt64()(), wtl::generate_canonical(wtl::sfmt64()));
    }
    cod_.reserve(NUM_FUNCTIONS_);
    for (size_t i=0; i<NUM_FUNCTIONS_; ++i) {
        cod_.emplace(wtl::sfmt64()(), wtl::generate_canonical(wtl::sfmt64()));
    }
}

Gene::Gene(const std::vector<unsigned int>& coding_funcs) {
    cis_.reserve(NUM_CRES_);
    for (size_t i=0; i<NUM_CRES_; ++i) {
        cis_.emplace(wtl::sfmt64()(), wtl::generate_canonical(wtl::sfmt64()));
    }
    cod_.reserve(coding_funcs.size());
    for (const auto x: coding_funcs) {
        cod_.emplace(x, wtl::generate_canonical(wtl::sfmt64()));
    }
}

std::ostream& Gene::write(std::ostream& ost) const {
    return ost << std::make_pair(cis_, cod_);
}

//! shortcut Gene::write(ost)
std::ostream& operator<<(std::ostream& ost, const Gene& x) {
    return x.write(ost);
}

} // namespace grn
