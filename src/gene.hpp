/*! @file individual.hpp
    @brief Interface of Gene class
*/
#pragma once
#ifndef GRN_GENE_HPP_
#define GRN_GENE_HPP_

#include <iosfwd>
#include <unordered_map>

namespace boost {namespace program_options {class options_description;}}

namespace grn {

/*! @brief Gene class
*/
class Gene {
  public:
    //! regulatory gene
    Gene();
    //! phenotypic gene
    Gene(const std::vector<unsigned int>& coding_funcs);

    //! write
    std::ostream& write(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Gene&);
    //! options description for Gene class
    static boost::program_options::options_description options_desc();

  private:
    static size_t NUM_CRES_;
    static constexpr size_t NUM_FUNCTIONS_ = 1u;

    std::unordered_map<unsigned int, double> cis_;
    std::unordered_map<unsigned int, double> cod_;
};

} // namespace grn

#endif /* GRN_GENE_HPP_ */
