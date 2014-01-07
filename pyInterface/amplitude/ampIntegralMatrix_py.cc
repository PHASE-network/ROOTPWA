#include "ampIntegralMatrix_py.h"

namespace bp = boost::python;

namespace {

/*
	const bp::list ampIntegralMatrix_waveDescriptions(const rpwa::ampIntegralMatrix& self) {
		return bp::list(self());
	};
*/
	const rpwa::waveDescription& ampIntegralMatrix_waveDesc1(const rpwa::ampIntegralMatrix& self, const unsigned int waveIndex) {
		return *(self.waveDesc(waveIndex));
	};

	const rpwa::waveDescription& ampIntegralMatrix_waveDesc2(const rpwa::ampIntegralMatrix& self, const std::string& waveName) {
		return *(self.waveDesc(waveName));
	};

	std::complex<double> ampIntegralMatrix_element1(const rpwa::ampIntegralMatrix& self,
	                                                const unsigned int waveIndexI,
	                                                const unsigned int waveIndexJ)
	{
		return self.element(waveIndexI, waveIndexJ);
	};

	std::complex<double> ampIntegralMatrix_element2(const rpwa::ampIntegralMatrix& self,
	                                                const std::string& waveNameI,
	                                                const std::string& waveNameJ)
	{
		return self.element(waveNameI, waveNameJ);
	};

	bool ampIntegralMatrix_integrate(rpwa::ampIntegralMatrix& self,
	                                 const bp::object& pyBinAmpFileNames,
	                                 const bp::object& pyRootAmpFileNames,
	                                 const unsigned long maxNmbEvents,
	                                 const std::string& weightFileName)
	{
		bp::list pyListBinAmpFileNames = bp::extract<bp::list>(pyBinAmpFileNames);
		std::vector<std::string> binAmpFileNames(bp::len(pyListBinAmpFileNames), "");
		for(int i = 0; i < bp::len(pyListBinAmpFileNames); ++i) {
			binAmpFileNames[i] = bp::extract<std::string>(pyListBinAmpFileNames[i]);
		}
		bp::list pyListRootAmpFileNames = bp::extract<bp::list>(pyRootAmpFileNames);
		std::vector<std::string> rootAmpFileNames(bp::len(pyListRootAmpFileNames), "");
		for(int i = 0; i < bp::len(pyListRootAmpFileNames); ++i) {
			rootAmpFileNames[i] = bp::extract<std::string>(pyListRootAmpFileNames[i]);
		}
		return self.integrate(binAmpFileNames, rootAmpFileNames, maxNmbEvents, weightFileName);
	};

	bool ampIntegralMatrix_writeAscii(const rpwa::ampIntegralMatrix& self, const std::string& outFileName) {
		return self.writeAscii(outFileName);
	};

	bool ampIntegralMatrix_readAscii(rpwa::ampIntegralMatrix& self, const std::string& inFileName) {
		return self.readAscii(inFileName);
	};

	int ampIntegralMatrix_Write(const rpwa::ampIntegralMatrix& self, std::string name) {
		return self.Write(name.c_str());
	};

}

void rpwa::py::exportAmpIntegralMatrix() {

	bp::class_<rpwa::ampIntegralMatrix>("ampIntegralMatrix")

		.def(bp::init<rpwa::ampIntegralMatrix&>())

		.def(bp::self_ns::str(bp::self))
		.def(bp::self == bp::self)
		.def(bp::self != bp::self)
		.def(bp::self + bp::self)
		.def(bp::self - bp::self)
		.def(bp::self * double())
		.def(bp::self / double())
		.def(double() * bp::self)
		.def(bp::self += bp::self)
		.def(bp::self -= bp::self)
		.def(bp::self *= double())
		.def(bp::self /= double())

		.def("clear", &rpwa::ampIntegralMatrix::clear)
		.def("nmbWaves", &rpwa::ampIntegralMatrix::nmbWaves)
		.def("nmbEvents", &rpwa::ampIntegralMatrix::nmbEvents)
		.def("setNmbEvents", &rpwa::ampIntegralMatrix::setNmbEvents)
		.def("containsWave", &rpwa::ampIntegralMatrix::containsWave)
		.def("waveIndex", &rpwa::ampIntegralMatrix::waveIndex)
		.def(
			"waveName"
			, &rpwa::ampIntegralMatrix::waveName
			, bp::return_value_policy<bp::return_by_value>()
		)
//		Disabled because of missing == operator in rpwa::waveDescription
//		See also http://stackoverflow.com/questions/10680691/why-do-i-need-comparison-operators-in-boost-python-vector-indexing-suite
//		.def("waveDescriptions", &ampIntegralMatrix_waveDescriptions)
		.def(
			"waveDesc"
			, &ampIntegralMatrix_waveDesc1
			, bp::return_value_policy<bp::copy_const_reference>()
		)
		.def(
			"waveDesc"
			, &ampIntegralMatrix_waveDesc2
			, bp::return_value_policy<bp::copy_const_reference>()
		)
		.def("allWavesHaveDesc", &rpwa::ampIntegralMatrix::allWavesHaveDesc)

//		Commenting this until it is decided how the boost::multi_array should be handled in python
//		.def("matrix", &rpwa::ampIntegralMatrix::matrix)

		.def("element", &ampIntegralMatrix_element1)
		.def("element", &ampIntegralMatrix_element2)

		.def("integrate"
		     , &ampIntegralMatrix_integrate
		     , (bp::arg("pyBinAmpFileNames"),
		         bp::arg("pyRootAmpFileNames"),
		         bp::arg("maxNmbEvents")=0,
		         bp::arg("weightFileName")="")
		)

		.def("renormalize", &rpwa::ampIntegralMatrix::renormalize)
		.def("writeAscii", &ampIntegralMatrix_writeAscii)
		.def("readAscii", &ampIntegralMatrix_readAscii)

		.def("Write", &ampIntegralMatrix_Write)

		.add_static_property("debugAmpIntegralMatrix", &rpwa::ampIntegralMatrix::debug, &rpwa::ampIntegralMatrix::setDebug);

};