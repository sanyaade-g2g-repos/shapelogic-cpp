/*
 * OpenCVImage.cpp
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#include "OpenCVImage.h"
#include "SLStringUtil.h"

#include <boost/gil/extension/dynamic_image/image_view_factory.hpp> //for interleaved_view()

#include <FL/Fl_Image.H>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace boost::gil;

//--------------static
const OpenCVImage * OpenCVImage::NULL_OBJECT = new OpenCVImage(NULL);

//-------------Constructor and Destructor

OpenCVImage::OpenCVImage(IplImage * image) : BaseImage() {
	_iplImage = image;
}

OpenCVImage::~OpenCVImage() {
	cvReleaseImage(&_iplImage);
	if (_flImage) {
		_flImage->uncache();
//You can set buffer in the constructor but you cannot set it to something new later
//		*_flImage->data() = NULL;
//		delete _flImage;
	}
}

/** Returns the width of this image in pixels. */
int OpenCVImage::getWidth() const {
	if (0 !=_iplImage)
		return _iplImage->width;
	return 0;
}

/** Returns the height of this image in pixels. */
int OpenCVImage::getHeight() const {
	if (0 !=_iplImage)
		return _iplImage->height;
	return 0;
}

/** Returns the number of color channels in the image. The color channels can be
*  accessed by toFloat(channelNumber, fp) and written by setPixels(channelNumber, fp).
* @return 1 for grayscale images, 3 for RGB images
*/
int OpenCVImage::getNChannels() const {
	if (0 != _iplImage)
		return _iplImage->nChannels;
	return 0;
}

/** Returns the depth of each channels. */
int OpenCVImage::getDepth() const {
	if (0 != _iplImage)
		return _iplImage->depth;
	return 0;
}

int OpenCVImage::getWidthStep() const {
	if (0 != _iplImage)
		return _iplImage->widthStep;
	return getWidth() * getNChannels();
}

/** Returns a reference to this image's pixel array. The
array type (byte[], short[], float[] or int[]) varies
depending on the image type. */
unsigned char * OpenCVImage::getPixels() const { //TODO should this be replaced by getBuffer()
	if (0 == _iplImage)
		return 0;
	return (unsigned char *) _iplImage->imageData;
}

/** Returns true if this image uses an inverting LUT
that displays zero as white and 255 as black. */
bool OpenCVImage::isInvertedLut() const {
    return false;
}

bool OpenCVImage::isGray() const {
	if (0 !=_iplImage)
		return 1 == _iplImage->nChannels;
	return false;
}

bool OpenCVImage::isGray8() const {
	if (0 !=_iplImage)
		return 1 == _iplImage->nChannels;
	return false;
}

bool OpenCVImage::isGray16() const {
	return false;
}

Fl_Image * OpenCVImage::getFlImage() const {
	if (NULL ==_flImage) {
		_flImage = new Fl_RGB_Image(getPixels(),getWidth(), getHeight(),
				getNChannels(), _iplImage->widthStep);
	}
	return _flImage;
}

OpenCVImage * OpenCVImage::copy() const {
	IplImage * copyOfFlImage = cvCloneImage(_iplImage );
	OpenCVImage * result = new OpenCVImage(copyOfFlImage);
	result->setFilename(getFilename());
	return result;
}

OpenCVImage * OpenCVImage::load(char const * filename) const {
	IplImage * iplImage =cvLoadImage(filename);
	if (0 == iplImage)
		return NULL;
	OpenCVImage * image = new OpenCVImage(iplImage);
	image->swapRB();
	image->setFilename(filename);
	return image;
}

bool OpenCVImage::saveAs(const char *filename) {
	if (SLStringUtil::empty(filename) || isEmpty())
		return false;
	swapRB();
	bool success = cvSaveImage(filename, _iplImage);
	if (success) {
		setFilename(filename);
	}
	swapRB();
	return success;
}

OpenCVImage * OpenCVImage::createImage(int width, int height, int nChannels, int depth) const {
	IplImage* image = cvCreateImage(cvSize(width, height), depth, nChannels);
	return new OpenCVImage(image);
}

//-------------Special for OpenCVImage

void OpenCVImage::swapRB() {
	cvConvertImage( _iplImage, _iplImage,CV_CVTIMG_SWAP_RB );
}

_IplImage * OpenCVImage::getIplImage() const {
	return _iplImage;
}

