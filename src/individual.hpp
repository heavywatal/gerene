/*! @file individual.hpp
    @brief Interface of Individual class
*/
#pragma once
#ifndef GRN_INDIVIDUAL_HPP_
#define GRN_INDIVIDUAL_HPP_

#include <iosfwd>

#include <boost/program_options.hpp>

namespace grn {

/*! @brief Individual class
*/
class Individual {
  public:
    //! write
    std::ostream& write(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Individual&);
    //! options description for Individual class
    static boost::program_options::options_description options_desc();
    //! unit test
    static void test();

  private:
};

} // namespace grn

#endif /* GRN_INDIVIDUAL_HPP_ */
