/*! @file population.hpp
    @brief Interface of Population class
*/
#pragma once
#ifndef GRN_POPULATION_HPP_
#define GRN_POPULATION_HPP_

#include "individual.hpp"

#include <iosfwd>
#include <vector>

namespace grn {

/*! @brief Population class
*/
class Population {
  public:
    //! default constructor
    Population() = default;
    Population(const size_t);

    //! write
    std::ostream& write(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Population&);

  private:
    std::vector<Individual> individuals_;
};

} // namespace grn

#endif /* GRN_POPULATION_HPP_ */
