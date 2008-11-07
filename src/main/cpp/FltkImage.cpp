/*
 * FltkImage.cpp
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#include "FltkImage.h"
#include <FL/Fl_Image.H>
#include <boost/gil/extension/dynamic_image/image_view_factory.hpp> //for interleaved_view()

using namespace boost::gil;

FltkImage::FltkImage(Fl_Image * image) : SLImage(), _flImage(image) {

}

FltkImage::~FltkImage() {
	delete _flImage;
}

/** Returns the width of this image in pixels. */
int FltkImage::getWidth() const {
	if (0 !=_flImage)
		return _flImage->w();
	return 0;
}

/** Returns the height of this image in pixels. */
int FltkImage::getHeight() const {
	if (0 !=_flImage)
		return _flImage->h();
	return 0;
}

//void FltkImage::setRoi(Rectangle roi) {
//
//}
//
//void FltkImage::setRoi(int x, int y, int rwidth, int rheight) {
//
//}
//
//Rectangle FltkImage::getRoi() {
//
//}

int FltkImage::getPixelCount() const {
	return getWidth() * getHeight();
}

/** Returns a reference to this image's pixel array. The
array type (byte[], short[], float[] or int[]) varies
depending on the image type. */
unsigned char * FltkImage::getPixels() const {
	if (0 == _flImage)
		return 0;
	return (unsigned char *) *_flImage->data();
}

/** Sets a new pixel array for the image. The length of the array must be equal to width*height.
Use setSnapshotPixels(null) to clear the snapshot buffer. */
void FltkImage::setPixels(unsigned char * pixels) {

}

/** Returns true if this image uses an inverting LUT
that displays zero as white and 255 as black. */
bool FltkImage::isInvertedLut() const {
    return false;
}

/** Returns the number of color channels in the image. The color channels can be
*  accessed by toFloat(channelNumber, fp) and written by setPixels(channelNumber, fp).
* @return 1 for grayscale images, 3 for RGB images
*/
int FltkImage::getNChannels() const {
	return _flImage->d();
}

bool FltkImage::isEmpty() const {
	return false;
}

bool FltkImage::isGray() const {
	return false;
}

bool FltkImage::isGray8() const {
	if (0 !=_flImage)
		return 1 == _flImage->d();
	return false;
}

bool FltkImage::isGray16() const {
	return false;
}

bool FltkImage::isRgb() const {
	if (0 !=_flImage)
		return 3 <= _flImage->d();
	return true;
}

//Rectangle FltkImage::getActiveRectangle() {
//
//}

int FltkImage::getLineStride() const {
    return 0;
}

Fl_Image * FltkImage::getFlImage() const {
	return _flImage;
}

FltkImage * FltkImage::copy() const {
	Fl_Image * copyOfFlImage = _flImage->copy();
	FltkImage * result = new FltkImage(copyOfFlImage);
	return result;
}

rgb8_view_t FltkImage::make_rgb8_view_t() const {
	rgb8_view_t view =
		interleaved_view(
				getWidth(),
				getHeight(),
				(rgb8_view_t::value_type *)(getPixels()),
				getWidth()*getNChannels());
	return view;
}

gray8_view_t FltkImage::make_gray8_view_t() const {
	gray8_view_t view =
		interleaved_view(
				getWidth(),
				getHeight(),
				(gray8_view_t::value_type *)(getPixels()),
				getWidth());
	return view;
}


const char * FltkImage::getFilename() const {
	return _filename.c_str();
}

void FltkImage::setFilename(const char * filename) {
	_filename = filename;
}

