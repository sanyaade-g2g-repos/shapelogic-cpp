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

#include <FL/Fl_Shared_Image.H> // Image I/O

#include <cstring> //strcmp

using namespace std;

SLFactory * SLFactory::INSTANCE = 0;

SLFactory::SLFactory() {
	_imageType = "OpenCV";
	fl_register_images(); //TODO make conditional
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
		return OpenCVImage::NULL_OBJECT->load(filename);
	return FltkImage::NULL_OBJECT->load(filename);
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
