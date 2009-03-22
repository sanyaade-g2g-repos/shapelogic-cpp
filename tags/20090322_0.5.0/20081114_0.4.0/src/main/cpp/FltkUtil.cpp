/*
 * FltkUtil.cpp
 *
 *  Created on: Sep 25, 2008
 *      Author: Sami Badawi
 */

#include "FltkUtil.h"
#include <FL/Fl_File_Chooser.H>
#include <string>

static std::string filename("");
static std::string directory(".");

const char * FltkUtil::singleFileDialog(bool onlyExisting) {
	int dialogType = Fl_File_Chooser::SINGLE;
	if (!onlyExisting)
		dialogType = Fl_File_Chooser::CREATE;
	Fl_File_Chooser chooser(directory.c_str(),			// directory
			"*",			// filter
			dialogType, 	// chooser type
			"ShapeLogic file chooser");	// title
	chooser.show();

	// Block until user picks something.
	//     (The other way to do this is to use a callback())
	//
	while(chooser.shown()) {
		Fl::wait();
	}
	directory = chooser.directory();
	filename = chooser.value();
	return filename.c_str();
}
