/*
 * FltkImage.cpp
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#include "FltkImage.h"
#include <FL/Fl_Image.H>


FltkImage::FltkImage(Fl_Image * image) : SLImage(), _flImage(image) {

}

FltkImage::~FltkImage() {
	delete _flImage;
}



/** Returns the width of this image in pixels. */
int FltkImage::getWidth() {
	if (0 !=_flImage)
		return _flImage->w();
	return 0;
}

/** Returns the height of this image in pixels. */
int FltkImage::getHeight() {
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

int FltkImage::getPixelCount() {
	return getWidth() * getHeight();
}

/** Returns a reference to this image's pixel array. The
array type (byte[], short[], float[] or int[]) varies
depending on the image type. */
unsigned char * FltkImage::getPixels() {
    return 0;
}

/** Sets a new pixel array for the image. The length of the array must be equal to width*height.
Use setSnapshotPixels(null) to clear the snapshot buffer. */
void FltkImage::setPixels(unsigned char * pixels) {

}

/** Returns true if this image uses an inverting LUT
that displays zero as white and 255 as black. */
bool FltkImage::isInvertedLut() {
    return false;
}

/** Returns the number of color channels in the image. The color channels can be
*  accessed by toFloat(channelNumber, fp) and written by setPixels(channelNumber, fp).
* @return 1 for grayscale images, 3 for RGB images
*/
int FltkImage::getNChannels() {
	return 3;
}

bool FltkImage::isEmpty() {
	return false;
}

bool FltkImage::isGray() {
	return false;
}

bool FltkImage::isGray8() {
	return false;
}

bool FltkImage::isGray16() {
	return false;
}

bool FltkImage::isRgb() {
	return true;
}

//Rectangle FltkImage::getActiveRectangle() {
//
//}

int FltkImage::getLineStride() {
    return 0;
}

Fl_Image * FltkImage::getFlImage() {
	return _flImage;
}

unsigned char * FltkImage::getBuffer() {
	if (0 == _flImage)
		return 0;
	return (unsigned char *) *_flImage->data();
}

FltkImage * FltkImage::copy() {
	Fl_Image * copyOfFlImage = _flImage->copy();
	FltkImage * result = new FltkImage(copyOfFlImage);
	return result;
}
