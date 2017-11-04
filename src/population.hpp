/*! @file population.hpp
    @brief Interface of Population class
*/
#pragma once
#ifndef GRN_POPULATION_HPP_
#define GRN_POPULATION_HPP_

#include <iosfwd>

#include <boost/program_options.hpp>

namespace grn {

/*! @brief Population class
*/
class Population {
  public:
    //! write
    std::ostream& write(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Population&);
    //! options description for Individual class
    static boost::program_options::options_description options_desc();
    //! unit test
    static void test();

  private:
};

} // namespace grn

#endif /* GRN_POPULATION_HPP_ */
