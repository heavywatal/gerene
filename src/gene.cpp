/*! @file gene.cpp
    @brief Implementation of Gene class
*/
#include "gene.hpp"

#include <wtl/debug.hpp>
#include <wtl/iostr.hpp>
#include <wtl/random.hpp>

#include <iostream>

namespace grn {

Gene::param_type Gene::PARAM_;

Gene::Gene() {
    cis_.reserve(PARAM_.NUM_CRES);
    for (size_t i=0; i<PARAM_.NUM_CRES; ++i) {
        cis_.emplace(wtl::mt64()(), wtl::generate_canonical(wtl::mt64()));
    }
    cod_.reserve(NUM_FUNCTIONS_);
    for (size_t i=0; i<NUM_FUNCTIONS_; ++i) {
        cod_.emplace(wtl::mt64()(), wtl::generate_canonical(wtl::mt64()));
    }
}

Gene::Gene(const std::vector<unsigned int>& coding_funcs) {
    cis_.reserve(PARAM_.NUM_CRES);
    for (size_t i=0; i<PARAM_.NUM_CRES; ++i) {
        cis_.emplace(wtl::mt64()(), wtl::generate_canonical(wtl::mt64()));
    }
    cod_.reserve(coding_funcs.size());
    for (const auto x: coding_funcs) {
        cod_.emplace(x, wtl::generate_canonical(wtl::mt64()));
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
