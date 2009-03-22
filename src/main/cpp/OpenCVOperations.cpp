/*
 * OpenCVOperation.cpp
 *
 *  Created on: Nov 9, 2008
 *      Author: Sami Badawi
 */

#include "OpenCVOperations.h"

#include "OpenCVImage.h"

#include <cv.h>
#include <highgui.h>

void OpenCVOperations::cannyEdge(SLImage * input, SLImage * output) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
	cvCanny (iplInput->getIplImage(), iplOutput->getIplImage(), 30., 50.);

}

void OpenCVOperations::flipHorizontally(SLImage * input, SLImage * output) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
	cvFlip( iplInput->getIplImage(), iplOutput->getIplImage(), 1); //over 0 means horizontally

}

void OpenCVOperations::flipVertically(SLImage * input, SLImage * output) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
	cvConvertImage( iplInput->getIplImage(), iplOutput->getIplImage(), CV_CVTIMG_FLIP );

}

void OpenCVOperations::swapRB(SLImage * input, SLImage * output) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
	cvConvertImage( iplInput->getIplImage(), iplOutput->getIplImage(),CV_CVTIMG_SWAP_RB );

}

void OpenCVOperations::threshold(SLImage * input, SLImage * output, double thresholdValue) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
	cvThreshold( iplInput->getIplImage(), iplOutput->getIplImage(), thresholdValue,
	                  255., CV_THRESH_BINARY);
}

void OpenCVOperations::adaptiveThreshold(SLImage * input, SLImage * output) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
	cvAdaptiveThreshold( iplInput->getIplImage(), iplOutput->getIplImage(), 255.);
}

void OpenCVOperations::dilate(SLImage * input, SLImage * output) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
	cvDilate( iplInput->getIplImage(), iplOutput->getIplImage());
}

void OpenCVOperations::erode(SLImage * input, SLImage * output) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
	cvErode( iplInput->getIplImage(), iplOutput->getIplImage());
}

