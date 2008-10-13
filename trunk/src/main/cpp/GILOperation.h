/*
 * GILOperation.h
 *
 *  Created on: Oct 10, 2008
 *      Author: Sami Badawi
 */

#ifndef GILOPERATION_H_
#define GILOPERATION_H_

class Fl_Image;

class GILOperation {
public:
	GILOperation();
	virtual ~GILOperation();

	static void fltkGradient(Fl_Image * input, Fl_Image * output);
	static void xLuminosityGradient(const char * inputFile, const char * outputFile);
};

#endif /* GILOPERATION_H_ */
