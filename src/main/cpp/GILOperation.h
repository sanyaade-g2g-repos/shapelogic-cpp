/*
 * GILOperation.h
 *
 *  Created on: Oct 10, 2008
 *      Author: Sami Badawi
 */

#ifndef GILOPERATION_H_
#define GILOPERATION_H_

class SLImage;

class GILOperation {
public:
	static void fltkBlur(SLImage * input, SLImage * output);
	static void fltkGradient(SLImage * input, SLImage * output);
	static void fltkSobelX(SLImage * input, SLImage * output);
	static void fltkSobelY(SLImage * input, SLImage * output);
	static void fltkSobelXY(SLImage * input, SLImage * output);
	static void rgbToGray(SLImage * input, SLImage * output);

	static bool saveJpg(const char * filename, SLImage * input);
	static bool saveAnyImage(const char * filename, SLImage * input);

	/** For testing directly on files. */
	static void xLuminosityGradient(const char * inputFile, const char * outputFile);
};

#endif /* GILOPERATION_H_ */
