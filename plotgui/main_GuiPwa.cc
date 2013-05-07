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
//    along with rootpwa.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// File and Version Information:
// $Rev:: 862                         $: revision of last commit
// $Author:: schmeing                 $: author of last commit
// $Date:: 2012-07-06 13:54:31 +0200 #$: date of last commit
//
// Description:
//      Main file for pwa gui
//
//
// Author List:
//      Stephan Schmeing          TUM            (original author)
//
//
//-------------------------------------------------------------------------

#include <iostream>

#include "reportingUtils.hpp"

#include "GuiPwaMain.h"

using namespace std;
using namespace rpwa;

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	GuiPwaMain *widget = new GuiPwaMain;

	widget->show();
	return app.exec();
}