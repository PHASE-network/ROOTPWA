/** @addtogroup generators
 * @{
 */


#ifndef TPWWEIGHT_HH
#define TPWWEIGHT_HH

// Base Class Headers ----------------


// Collaborating Class Headers -------
#include <string>
#include <vector>
#include <map>
#include <complex>
#include <event.h>
#include <Tgamp.h>

#include <integral.h>
// Collaborating Class Declarations --


/** @brief Calculates the partial wave weight for a given event  
 *  @author Sebastian Neubert TUM (original author)
 *
 */
class TPWWeight {
public:

  // Constructors/Destructors ---------
  TPWWeight(){}
  ~TPWWeight(){}


  // Accessors -----------------------


  // Modifiers -----------------------
  /** @brief Add a partial wave to model
   *   
   *  keyfilename = name of gamp keyfile describing this wave
   *  amp         = production amplitude for this wave
   *  vectori     = index of production vector 
   *                (different indices are added incoherently)
   */
  void addWave(const std::string& keyfilename, 
	       const std::complex<double>& amp,
	       unsigned int vectori=0);

  void loadIntegrals(const std::string& filename);
  
  // Operations ----------------------
  /** @brief Calculate weight for an event
   */ 
  double weight(event& e);



private:

  // Private Data Members ------------
  std::vector<std::vector<std::string> > m_waves;
  std::vector<std::vector<std::complex<double> > > m_amps;

  std::vector<Tgamp> m_gamp;
  std::map<string,double> m_relphase;
  integral m_normInt;

  // Private Methods -----------------

};

#endif
/* @} **/
