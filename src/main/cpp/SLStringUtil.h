/*
 * SLStringUtil.h
 *
 *  Created on: Oct 22, 2008
 *      Author: Sami Badawi
 */

#ifndef SLSTRINGUTIL_H_
#define SLSTRINGUTIL_H_
#include <string>

class SLStringUtil {
public:
	static std::string fileExtension(const char *filename);
	static bool isJpeg(const char *filename);
	static bool isPng(const char *filename);
	static bool isTiff(const char *filename);
	static std::string preFileExtension(const char *filename);
	static std::string toLower(const char * input);
	static bool empty(const char * input);
};

#endif /* SLSTRINGUTIL_H_ */
