/*
 * SLFactory.cpp
 *
 *  Created on: Nov 7, 2008
 *      Author: Sami Badawi
 */

#include "GILOperation.h"
#include "FltkImage.h"
#include "OpenCVImage.h"
#include "SLFactory.h"
#include "SLStringUtil.h"

#include <FL/Fl_Bitmap.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Shared_Image.H> // Image I/O

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#include <cmath> //for OpenCV
#include <cstring> //strcmp

using namespace std;

SLFactory * SLFactory::INSTANCE = 0;

SLFactory::SLFactory() {
	_imageType = "OpenCV";
	fl_register_images();
}

SLFactory::~SLFactory() {
}

SLFactory * SLFactory::getInstance() {
	if (0 == INSTANCE)
		INSTANCE = new SLFactory();
	return INSTANCE;
}

const char * SLFactory::getImageType () const {
	return _imageType;
}
void SLFactory::setImageType(const char * imageType) {
	_imageType = imageType;
}

SLImage * SLFactory::makeSLImage(const char * filename) const {
	if (0 == strcmp("OpenCV",_imageType))
		return makeOpenCVImage(filename);
	return makeFltkImage(filename);
}

FltkImage * SLFactory::makeFltkImage(const char * filename) const {
	if (SLStringUtil::empty(filename))
		return 0;
	Fl_Shared_Image *sharedImage = Fl_Shared_Image::get(filename);
	Fl_Image * image = sharedImage->copy();
	sharedImage->release();
	if ( image->h() == 0 ) {
		delete image;
		return 0;
	}
	FltkImage * result = new FltkImage(image);
	result->setFilename(filename);
	return result;
}

OpenCVImage * SLFactory::makeOpenCVImage(const char * filename) const {
	if (SLStringUtil::empty(filename))
		return 0;
	IplImage* img=cvLoadImage(filename);
	if(0 == img) {
		return 0;
	}
	OpenCVImage * openCVImage = new OpenCVImage(img);
	openCVImage->swapRB();
	return openCVImage;
}

bool SLFactory::saveImageAs(SLImage * image, const char *filename) {
	if (SLStringUtil::empty(filename))
		return false;
	bool saved = image->saveAs(filename);
	if (!saved && GILOperation::saveAnyImage(filename, image)) {
		image->setFilename(filename);
		saved = true;
	}
	return saved;
}
