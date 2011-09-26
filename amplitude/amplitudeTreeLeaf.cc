///////////////////////////////////////////////////////////////////////////
//
//    Copyright 2010
//
//    This file is part of rootpwa
//
//    rootpwa is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    rootpwa is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with rootpwa. If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// File and Version Information:
// $Rev::                             $: revision of last commit
// $Author::                          $: author of last commit
// $Date::                            $: date of last commit
//
// Description:
//      TTree leaf persistency storage class for amplitude information
//      needed by fit program
//
//
// Author List:
//      Boris Grube          TUM            (original author)
//
//
//-------------------------------------------------------------------------


#include "TClass.h"

#include "reportingUtils.hpp"
#include "amplitudeTreeLeaf.h"

	
using namespace std;
using namespace rpwa;


#ifdef USE_STD_COMPLEX_TREE_LEAFS
ClassImp(amplitudeTreeLeaf);
#endif


bool amplitudeTreeLeaf::_debug = false;


amplitudeTreeLeaf::amplitudeTreeLeaf()
	: TObject      (),
	  _incohSubAmps()
{
	amplitudeTreeLeaf::Class()->IgnoreTObjectStreamer();  // don't store TObject's fBits and fUniqueID
}


amplitudeTreeLeaf::~amplitudeTreeLeaf()
{ }


void amplitudeTreeLeaf::clear()
{
	_incohSubAmps.clear();
}


amplitudeTreeLeaf&
amplitudeTreeLeaf::operator =(const amplitudeTreeLeaf& amp)
{
	if (this != &amp) {
		TObject::operator =(amp);
		_incohSubAmps     = amp._incohSubAmps;
	}
	return *this;
}


amplitudeTreeLeaf&
amplitudeTreeLeaf::operator +=(const amplitudeTreeLeaf& amp)
{
	const unsigned int nmbSubAmps = nmbIncohSubAmps();
	if (nmbSubAmps != amp.nmbIncohSubAmps()) {
		printErr << "cannot add " << *this << endl
		         << "and " << amp << endl
		         << "because the two amplitudes have different number of incoherent sub-amplitudes. "
		         << "aborting." << endl;
		throw;
	}
	for (unsigned int i = 0; i < nmbSubAmps; ++i)
		_incohSubAmps[i] += amp.incohSubAmp(i);
	return *this;
}


amplitudeTreeLeaf&
amplitudeTreeLeaf::operator -=(const amplitudeTreeLeaf& amp)
{
	const unsigned int nmbSubAmps = nmbIncohSubAmps();
	if (nmbSubAmps != amp.nmbIncohSubAmps()) {
		printErr << "cannot subtract " << amp << endl
		         << "from " << *this << endl
		         << "because the two amplitudes have different number of incoherent sub-amplitudes. "
		         << "aborting." << endl;
		throw;
	}
	for (unsigned int i = 0; i < nmbSubAmps; ++i)
		_incohSubAmps[i] -= amp.incohSubAmp(i);
	return *this;
}


amplitudeTreeLeaf&
amplitudeTreeLeaf::operator *=(const double factor)
{
	for (unsigned int i = 0; i < nmbIncohSubAmps(); ++i)
		_incohSubAmps[i] *= factor;
	return *this;
}


amplitudeTreeLeaf&
amplitudeTreeLeaf::operator /=(const double factor)
{
	for (unsigned int i = 0; i < nmbIncohSubAmps(); ++i)
		_incohSubAmps[i] /= factor;
	return *this;
}


amplitudeTreeLeaf&
amplitudeTreeLeaf::operator *=(const complex<double> factor)
{
	for (unsigned int i = 0; i < nmbIncohSubAmps(); ++i)
		_incohSubAmps[i] *= factor;
	return *this;
}


amplitudeTreeLeaf&
amplitudeTreeLeaf::operator /=(const complex<double> factor)
{
	for (unsigned int i = 0; i < nmbIncohSubAmps(); ++i)
		_incohSubAmps[i] /= factor;
	return *this;
}


ostream&
amplitudeTreeLeaf::print(ostream& out) const
{
	out << "amplitude tree leaf:"  << endl;
	const unsigned int nmbSubAmps = nmbIncohSubAmps();
	if (nmbSubAmps > 1) {
		out << "    number of incoherent sub-amps ... " << nmbSubAmps << endl;
		out << "    amplitude value(s):" << endl;
		for (unsigned int i = 0; i < nmbSubAmps; ++i)
			out << "        [" << setw(4) << i << "] = " << maxPrecisionDouble(_incohSubAmps[i]) << endl;
	} else if (nmbSubAmps == 1)
		out << "    amplitude ... " << _incohSubAmps[0] << endl;
	else
		out << "    no amplitude value" << endl;
	return out;
}
