/*! @file individual.hpp
    @brief Interface of Individual class
*/
#pragma once
#ifndef GRN_INDIVIDUAL_HPP_
#define GRN_INDIVIDUAL_HPP_

#include <iosfwd>
#include <vector>
#include <memory>

namespace grn {

class Gene;

//! @brief Parameters for Individual class
/*! @ingroup params
*/
struct IndividualParams {
    //! Number of genes
    unsigned NUM_GENES = 20u;
};

/*! @brief Individual class
*/
class Individual {
  public:
    //! Alias
    using param_type = IndividualParams;
    Individual();
    //! write
    std::ostream& write(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Individual&);

    //! Set #PARAM_
    static void param(const param_type& p);
    //! Get #PARAM_
    static const param_type& param() {return PARAM_;}

  private:
    //! Parameters shared among instances
    static param_type PARAM_;

    std::vector<std::shared_ptr<Gene>> genes_;
};

} // namespace grn

#endif /* GRN_INDIVIDUAL_HPP_ */
