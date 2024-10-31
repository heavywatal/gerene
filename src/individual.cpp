/*! @file individual.cpp
    @brief Implementation of Individual class
*/
#include "individual.hpp"
#include "gene.hpp"

#include <wtl/debug.hpp>
#include <wtl/iostr.hpp>
#include <wtl/random.hpp>

#include <iostream>

namespace grn {

Individual::param_type Individual::PARAM_;

Individual::Individual() {
    const size_t dimensions = 2u;
    genes_.reserve(PARAM_.NUM_GENES);
    for (size_t i=0; i<dimensions; ++i) {
        genes_.emplace_back(std::make_shared<Gene>(std::vector<unsigned int>{0u}));
    }
    for (size_t i=dimensions; i<PARAM_.NUM_GENES; ++i) {
        genes_.emplace_back(std::make_shared<Gene>());
    }
}

std::ostream& Individual::write(std::ostream& ost) const {
    for (const auto& g: genes_) {
        ost << *g << "\t";
    }
    return ost;
}

//! shortcut Individual::write(ost)
std::ostream& operator<<(std::ostream& ost, const Individual& x) {
    return x.write(ost);
}

} // namespace grn
