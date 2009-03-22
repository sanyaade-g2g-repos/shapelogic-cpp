/*
 * BaseImage.cpp
 *
 *  Created on: Nov 11, 2008
 *      Author: Sami Badawi
 */

#include "BaseImage.h"
#include "SLStringUtil.h"

#include <boost/gil/extension/dynamic_image/image_view_factory.hpp> //for interleaved_view()

#include <FL/Fl_Image.H>
#include <FL/Fl_Shared_Image.H>

using namespace boost::gil;


BaseImage::BaseImage(Fl_Image * flImage) : SLImage(), _flImage(flImage) {

}

BaseImage::~BaseImage() {
}

int BaseImage::getWidthStep() const {
	return getWidth() * getNChannels();
}

//void BaseImage::setRoi(Rectangle roi) {
//
//}
//
//void BaseImage::setRoi(int x, int y, int rwidth, int rheight) {
//
//}
//
//Rectangle BaseImage::getRoi() {
//
//}

int BaseImage::getPixelCount() const {
	return getWidth() * getHeight();
}

/** Sets a new pixel array for the image. The length of the array must be equal to width*height.
Use setSnapshotPixels(null) to clear the snapshot buffer. */
void BaseImage::setPixels(unsigned char * pixels) {

}

/** Returns true if this image uses an inverting LUT
that displays zero as white and 255 as black. */
bool BaseImage::isInvertedLut() const {
    return false;
}


bool BaseImage::isEmpty() const {
	return NULL == getPixels();
}

bool BaseImage::isGray() const {
	return 1 == getNChannels();
}

bool BaseImage::isGray8() const {
	return 1 == getNChannels() && 8 == getDepth();
}

bool BaseImage::isGray16() const {
	return 1 == getNChannels() && 16 == getDepth();
}

bool BaseImage::isRgb() const {
	return 3 <= getNChannels();
}

//Rectangle BaseImage::getActiveRectangle() {
//
//}

int BaseImage::getLineStride() const {
    return getWidth();
}

rgb8_view_t BaseImage::make_rgb8_view_t() const {
	rgb8_view_t view =
		interleaved_view(
				getWidth(),
				getHeight(),
				(rgb8_view_t::value_type *)(getPixels()),
				getWidthStep() );
	return view;
}

gray8_view_t BaseImage::make_gray8_view_t() const {
	gray8_view_t view =
		interleaved_view(
				getWidth(),
				getHeight(),
				(gray8_view_t::value_type *)(getPixels()),
				getWidthStep() );
	return view;
}


const char * BaseImage::getFilename() const {
	return _filename.c_str();
}

void BaseImage::setFilename(const char * filename) {
	_filename = filename;
}

BaseImage * BaseImage::makeSimilarImage() const {
	BaseImage * image = (BaseImage *) createImage(getWidth(), getHeight(),getNChannels(), getDepth());
	image->setFilename(getFilename());
	return image;
}
