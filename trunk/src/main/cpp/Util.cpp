/*
 * Util.cpp
 *
 *  Created on: Sep 25, 2008
 *      Author: Sami Badawi
 */

#include "Util.h"
#include <FL/Fl_File_Chooser.H>
#include <string>

static std::string filename("");
static std::string directory(".");

const char * Util::singleFileDialog() {
	  Fl_File_Chooser chooser(directory.c_str(),			// directory
			    "*",			// filter
			    Fl_File_Chooser::SINGLE, 	// chooser type
			    "ShapeLogic file chooser");	// title
	  chooser.show();

	// Block until user picks something.
	//     (The other way to do this is to use a callback())
	//
	  while(chooser.shown())
	  { Fl::wait(); }
	  directory = chooser.directory();
	  filename = chooser.value();
	  return filename.c_str();
}

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}
