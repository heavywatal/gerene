/*! @file individual.cpp
    @brief Implementation of Individual class
*/
#include "individual.hpp"
#include "gene.hpp"

#include <wtl/debug.hpp>
#include <wtl/iostr.hpp>
#include <wtl/random.hpp>
#include <sfmt.hpp>

#include <iostream>

namespace grn {

size_t Individual::NUM_GENES_ = 20u;

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
      ("genes,V", po::value(&NUM_GENES_)->default_value(NUM_GENES_))
    ;
    return desc;
}

Individual::Individual() {
    const size_t dimensions = 2u;
    genes_.reserve(NUM_GENES_);
    for (size_t i=0; i<dimensions; ++i) {
        genes_.emplace_back(std::make_shared<Gene>(std::vector<unsigned int>{0u}));
    }
    for (size_t i=dimensions; i<NUM_GENES_; ++i) {
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

void Individual::test() {HERE;
    Individual x;
    std::cout << x << std::endl;
}

} // namespace grn
