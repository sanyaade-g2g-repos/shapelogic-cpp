/*
 * OpenCVOperation.h
 *
 *  Created on: Nov 9, 2008
 *      Author: Sami Badawi
 */

#ifndef OPENCVOPERATIONS_H_
#define OPENCVOPERATIONS_H_

class SLImage;

class OpenCVOperations {
public:
	static void cannyEdge(SLImage * input, SLImage * output);
	static void flipHorizontally(SLImage * input, SLImage * output);
	static void flipVertically(SLImage * input, SLImage * output);
	static void swapRB(SLImage * input, SLImage * output);
};

#endif /* OPENCVOPERATIONS_H_ */
