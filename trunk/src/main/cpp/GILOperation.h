/*
 * GILOperation.h
 *
 *  Created on: Oct 10, 2008
 *      Author: Sami Badawi
 */

#ifndef GILOPERATION_H_
#define GILOPERATION_H_

#include <boost/gil/typedefs.hpp>

class Fl_Image;

class GILOperation {
public:
	static void fltkGradient(Fl_Image * input, Fl_Image * output);
	static void fltkSobelX(Fl_Image * input, Fl_Image * output);
	static void fltkSobelY(Fl_Image * input, Fl_Image * output);
	static void fltkSobelXY(Fl_Image * input, Fl_Image * output);
	static void xLuminosityGradient(const char * inputFile, const char * outputFile);
	static boost::gil::rgb8_view_t make_rgb8_view_t(Fl_Image * input);
};

#endif /* GILOPERATION_H_ */
