/*
 * SLStringUtil.cpp
 *
 *  Created on: Oct 22, 2008
 *      Author: Sami Badawi
 */

#include "SLStringUtil.h"
#include <algorithm>

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
	string extensionLower = toLower(extension.c_str());
	if (extensionLower == "jpg") return true;
	if (extensionLower == "jpeg") return true;
	return false;
}

bool SLStringUtil::isPng(const char *filename) {
	string extension = fileExtension(filename);
	string extensionLower = toLower(extension.c_str());
	if (extensionLower == "png") return true;
	return false;
}

bool SLStringUtil::isTiff(const char *filename) {
	string extension = fileExtension(filename);
	string extensionLower = toLower(extension.c_str());
	if (extensionLower == "tiff") return true;
	return false;
}

string SLStringUtil::toLower(const char * input) {
	string output(input);
	transform( output.begin(), output.end(), output.begin(), ::tolower );
	return output;
}

bool SLStringUtil::empty(const char * input) {
	if (NULL == input)
		return true;
	else if ('\0' == *input)
		return true;
	return false;
}
