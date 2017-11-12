/*! @file individual.hpp
    @brief Interface of Individual class
*/
#pragma once
#ifndef GRN_INDIVIDUAL_HPP_
#define GRN_INDIVIDUAL_HPP_

#include <iosfwd>
#include <vector>
#include <memory>

#include <boost/program_options.hpp>

namespace grn {

class Gene;

/*! @brief Individual class
*/
class Individual {
  public:
    Individual();
    //! write
    std::ostream& write(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Individual&);
    //! options description for Individual class
    static boost::program_options::options_description options_desc();
    //! unit test
    static void test();

  private:
    std::vector<std::shared_ptr<Gene>> genes_;
};

} // namespace grn

#endif /* GRN_INDIVIDUAL_HPP_ */
