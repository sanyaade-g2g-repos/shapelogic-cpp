/*
 * GILOperation.h
 *
 *  Created on: Oct 10, 2008
 *      Author: Sami Badawi
 */

#ifndef GILOPERATION_H_
#define GILOPERATION_H_

#include <boost/gil/typedefs.hpp>

class FltkImage;

class GILOperation {
public:
	static void fltkBlur(FltkImage * input, FltkImage * output);
	static void fltkGradient(FltkImage * input, FltkImage * output);
	static void fltkSobelX(FltkImage * input, FltkImage * output);
	static void fltkSobelY(FltkImage * input, FltkImage * output);
	static void fltkSobelXY(FltkImage * input, FltkImage * output);
	static void xLuminosityGradient(const char * inputFile, const char * outputFile);
	static boost::gil::rgb8_view_t make_rgb8_view_t(FltkImage * input);
	static bool saveJpg(const char * filename, FltkImage * input);
	static bool saveAnyImage(const char * filename, FltkImage * input);
};

#endif /* GILOPERATION_H_ */
