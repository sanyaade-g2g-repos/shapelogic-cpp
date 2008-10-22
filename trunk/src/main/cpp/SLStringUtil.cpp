/*
 * SLStringUtil.cpp
 *
 *  Created on: Oct 22, 2008
 *      Author: Sami Badawi
 */

#include "SLStringUtil.h"

using namespace std;

string SLStringUtil::fileExtension(const char *filename) {
	std::string filenameString(filename);
	int pos = filenameString.find_last_of('.');
	if (pos<0)
		return "";
	else
		return filenameString.substr(pos+1);
}

string SLStringUtil::preFileExtension(const char *filename) {
	std::string filenameString(filename);
	int pos = filenameString.find_last_of('.');
	if (pos<0)
		return filename;
	else
		return filenameString.substr(0,pos+1);
}

bool SLStringUtil::isJpeg(const char *filename) {
	string extension = fileExtension(filename);
	string extensionLower = extension; //.tolower(); //TODO fix to lower case
	if (extensionLower == "jpg") return true;
	if (extensionLower == "jpeg") return true;
	return false;
}

