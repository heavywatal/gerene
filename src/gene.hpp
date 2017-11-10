/*! @file individual.hpp
    @brief Interface of Gene class
*/
#pragma once
#ifndef GRN_GENE_HPP_
#define GRN_GENE_HPP_

#include <iosfwd>
#include <unordered_map>

#include <boost/program_options.hpp>

namespace grn {

/*! @brief Gene class
*/
class Gene {
  public:
    //! write
    std::ostream& write(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Gene&);
    //! options description for Gene class
    static boost::program_options::options_description options_desc();
    //! unit test
    static void test();

  private:
    std::unordered_map<unsigned int, double> cis_;
    std::unordered_map<unsigned int, double> cod_;
};

} // namespace grn

#endif /* GRN_GENE_HPP_ */
