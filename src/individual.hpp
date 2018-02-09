/*! @file individual.hpp
    @brief Interface of Individual class
*/
#pragma once
#ifndef GRN_INDIVIDUAL_HPP_
#define GRN_INDIVIDUAL_HPP_

#include <iosfwd>
#include <vector>
#include <memory>

namespace boost {namespace program_options {class options_description;}}

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
    static size_t NUM_GENES_;

    std::vector<std::shared_ptr<Gene>> genes_;
};

} // namespace grn

#endif /* GRN_INDIVIDUAL_HPP_ */
