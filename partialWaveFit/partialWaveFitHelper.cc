///////////////////////////////////////////////////////////////////////////
//
//    Copyright 2015 Sebastian Uhl (TUM)
//
//    This file is part of ROOTPWA
//
//    ROOTPWA is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    ROOTPWA is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with ROOTPWA. If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
//
// Description:
//      helper functions related to the fitResult class
//
//-------------------------------------------------------------------------


#include <iostream>
#include <string>

#include "partialWaveFitHelper.h"
#include "reportingUtils.hpp"


int
rpwa::partialWaveFitHelper::getReflectivity(const std::string& name)
{
	size_t waveNamePos = 0;  // position at which the wave name starts
	// check whether name is a production amplitude (parameter) or a wave name
	if (name[0] == 'V') {
		waveNamePos = name.find("_");
		if (waveNamePos == std::string::npos) {
			printErr << "cannot parse parameter/wave name '" << name << "'. "
			         << "appears to be parameter name, but does not contain '_'. Aborting..." << std::endl;
			throw;
		}
		waveNamePos += 1;
	}

	int refl = 0;
	if (name.substr(waveNamePos) != "flat") {
		if (name[waveNamePos] == '[') {
			// new naming convention "[IG,JPC,ME]=..."
			// * the C might not be present
			const size_t startQn = waveNamePos + 1;
			const size_t endQn = name.find(']', startQn);
			if (endQn == std::string::npos) {
				printErr << "cannot parse parameter/wave name '" << name.substr(waveNamePos) << "'. "
				         << "could not find closing bracket ']' around quantum numbers. Aborting..." << std::endl;
				throw;
			}
			const size_t firstSplit = name.find(',', startQn);
			const size_t secondSplit = name.find(',', firstSplit+1);
			if (firstSplit == std::string::npos || secondSplit == std::string::npos || endQn < secondSplit) {
				printErr << "cannot parse parameter/wave name '" << name.substr(waveNamePos) << "'. "
				         << "could not find two separators ','. Aborting..." << std::endl;
				throw;
			}
			if (endQn - secondSplit < 3) {
				printErr << "cannot parse parameter/wave name '" << name.substr(waveNamePos) << "'. "
				         << "spin-projection and reflectivity not correctly specified. Aborting..." << std::endl;
				throw;
			}
			if (name[endQn - 1] == '-')
				refl= -1;
			else if (name[endQn - 1] == '+')
				refl= +1;
			else {
				printErr << "cannot parse parameter/wave name '" << name << "'. "
				         << "cannot not determine reflectivity. Aborting..." << std::endl;
				throw;
			}
		} else {
			// old naming convention "IGJPCME..."
			if (name[waveNamePos + 6] == '-')
				refl= -1;
			else if (name[waveNamePos + 6] == '+')
				refl= +1;
			else {
				printErr << "cannot parse parameter/wave name '" << name << "'. "
				         << "cannot not determine reflectivity. Aborting..." << std::endl;
				throw;
			}
		}
	}

	return refl;
}
