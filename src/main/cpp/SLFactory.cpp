/*
 * SLFactory.cpp
 *
 *  Created on: Nov 7, 2008
 *      Author: Sami Badawi
 */

#include "FltkImage.h"
#include "SLFactory.h"
#include "SLStringUtil.h"

#include <FL/Fl_Bitmap.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Shared_Image.H> // Image I/O

#include <cstring> //strcmp

using namespace std;

SLFactory * SLFactory::INSTANCE = 0;

SLFactory::SLFactory() {
	_imageType = "";
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
		return 0;
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

//OpenCVImage * SLFactory::makeOpenCVImage(const char * filename) const {
//	return 0;
//}

SLImage * SLFactory::makeSimilarImage(const SLImage * image) const {
	if (0 == strcmp("OpenCV",_imageType))
		return 0;
	return makeSimilarFltkImage(image);
}

FltkImage * SLFactory::makeSimilarFltkImage(const SLImage * image) const {
	  Fl_Image * nextFlImage = 0;
	  int bufferSize = image->getWidth() * image->getHeight() * image->getNChannels();
	  const uchar* buffer = new uchar[bufferSize];
	  if (image->isGray())
		  nextFlImage = new Fl_Bitmap(buffer,image->getWidth(), image->getHeight());
	  else
		  nextFlImage = new Fl_RGB_Image(buffer,image->getWidth(), image->getHeight(), image->getNChannels());
	  return new FltkImage(nextFlImage);
}
