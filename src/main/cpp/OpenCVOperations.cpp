/*
 * OpenCVOperation.cpp
 *
 *  Created on: Nov 9, 2008
 *      Author: Sami Badawi
 */

#include "OpenCVOperations.h"

#include "OpenCVImage.h"

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

void OpenCVOperations::laplace(SLImage * input, SLImage * output) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
//	cvPyrUp(iplInput->getIplImage(), iplOutput->getIplImage());
	cvConvertImage( iplInput->getIplImage(), iplOutput->getIplImage(),CV_CVTIMG_SWAP_RB ); //TODO fix

}

void OpenCVOperations::flipHorizontally(SLImage * input, SLImage * output) {
	if (NULL == input || NULL == output)
		return;
	OpenCVImage * iplInput = dynamic_cast<OpenCVImage *>(input);
	OpenCVImage * iplOutput = dynamic_cast<OpenCVImage *>(output);
	if (0 == iplInput || 0 == iplOutput ||
			0 == iplInput->getIplImage() || 0 == iplOutput->getIplImage())
		return;
	cvConvertImage( iplInput->getIplImage(), iplOutput->getIplImage(), CV_CVTIMG_FLIP );

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
