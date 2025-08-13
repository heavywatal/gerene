/*! @file individual.hpp
    @brief Interface of Gene class
*/
#pragma once
#ifndef GRN_GENE_HPP_
#define GRN_GENE_HPP_

#include <iosfwd>
#include <vector>
#include <unordered_map>

namespace grn {

//! @brief Parameters for Gene class
/*! @ingroup params
*/
struct GeneParams {
    //! Number of cis-regulatory elements
    unsigned NUM_CRES = 20u;
};

/*! @brief Gene class
*/
class Gene {
  public:
    //! Alias
    using param_type = GeneParams;
    //! regulatory gene
    Gene();
    //! phenotypic gene
    Gene(const std::vector<unsigned int>& coding_funcs);

    //! write
    std::ostream& write(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Gene&);

    //! Set #PARAM_
    static void param(const param_type& p);
    //! Get #PARAM_
    static const param_type& param() {return PARAM_;}

  private:
    //! Parameters shared among instances
    static param_type PARAM_;

    static constexpr size_t NUM_FUNCTIONS_ = 1u;

    std::unordered_map<unsigned int, double> cis_;
    std::unordered_map<unsigned int, double> cod_;
};

} // namespace grn

#endif /* GRN_GENE_HPP_ */
