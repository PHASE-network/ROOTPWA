//-----------------------------------------------------------
//
// Description:
//    Final-state mass-dependence of mass dependent fit
//
//
// Author List:
//      Sebastian Neubert    TUM            (original author)
//
//
//-----------------------------------------------------------

#ifndef MASSDEPFITFSMD_HH
#define MASSDEPFITFSMD_HH

#include <iostream>
#include <limits>
#include <vector>

namespace libconfig {
	class Setting;
}
namespace ROOT {
	namespace Math {
		class Minimizer;
	}
}
class TFormula;

namespace rpwa {

	namespace massDepFit {

		class fsmd {

		public:

			fsmd();
			~fsmd();

			bool init(const libconfig::Setting* configComponent,
			          const std::vector<double>& massBinCenters,
			          const bool debug);

			bool update(const libconfig::Setting* configComponent,
			            const ROOT::Math::Minimizer* minimizer,
			            const bool debug) const;

			size_t getNrParameters() const { return _nrParameters; }
			size_t getParameters(double* par) const;
			size_t setParameters(const double* par);

			double getParameter(const size_t idx) const { return _parameters[idx]; }
			bool getParameterFixed(const size_t idx) const { return _parametersFixed[idx]; }
			double getParameterLimitLower(const size_t idx) const { return _parametersLimitLower[idx]; }
			bool getParameterLimitedLower(const size_t idx) const { return _parametersLimitedLower[idx]; }
			double getParameterLimitUpper(const size_t idx) const { return _parametersLimitUpper[idx]; }
			bool getParameterLimitedUpper(const size_t idx) const { return _parametersLimitedUpper[idx]; }
			double getParameterStep(const size_t idx) const { return _parametersStep[idx]; }

			double val(const double mass,
			           const size_t idxMass = std::numeric_limits<size_t>::max()) const;

			std::ostream& print(std::ostream& out) const;

		private:

			TFormula* _function;

			bool _functionFixed;

			size_t _nrParameters;

			std::vector<double> _parameters;
			std::vector<bool> _parametersFixed;
			std::vector<double> _parametersLimitLower;
			std::vector<bool> _parametersLimitedLower;
			std::vector<double> _parametersLimitUpper;
			std::vector<bool> _parametersLimitedUpper;
			std::vector<std::string> _parametersName;
			std::vector<double> _parametersStep;

			std::vector<double> _values;
		};

	} // end namespace massDepFit

} // end namespace rpwa


inline
std::ostream&
operator<< (std::ostream& out, const rpwa::massDepFit::fsmd& fsmd)
{
	return fsmd.print(out);
}


#endif // MASSDEPFITFSMD_HH