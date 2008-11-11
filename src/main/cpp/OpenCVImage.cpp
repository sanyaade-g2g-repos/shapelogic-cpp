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

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

using namespace boost::gil;

//--------------static
const OpenCVImage * OpenCVImage::NULL_OBJECT = new OpenCVImage(NULL);

//-------------Constructor and Destructor

OpenCVImage::OpenCVImage(IplImage * image) : SLImage() {
	_iplImage = image;
	_flImage = NULL;
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

//void OpenCVImage::setRoi(Rectangle roi) {
//
//}
//
//void OpenCVImage::setRoi(int x, int y, int rwidth, int rheight) {
//
//}
//
//Rectangle OpenCVImage::getRoi() {
//
//}

int OpenCVImage::getPixelCount() const {
	return getWidth() * getHeight();
}

/** Returns a reference to this image's pixel array. The
array type (byte[], short[], float[] or int[]) varies
depending on the image type. */
unsigned char * OpenCVImage::getPixels() const { //TODO should this be replaced by getBuffer()
	if (0 == _iplImage)
		return 0;
	return (unsigned char *) _iplImage->imageData;
}

/** Sets a new pixel array for the image. The length of the array must be equal to width*height.
Use setSnapshotPixels(null) to clear the snapshot buffer. */
void OpenCVImage::setPixels(unsigned char * pixels) {

}

/** Returns true if this image uses an inverting LUT
that displays zero as white and 255 as black. */
bool OpenCVImage::isInvertedLut() const {
    return false;
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

bool OpenCVImage::isEmpty() const {
	return 0 == _iplImage;
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

bool OpenCVImage::isRgb() const {
	if (0 !=_iplImage)
		return 3 <= _iplImage->nChannels;
	return true;
}

//Rectangle OpenCVImage::getActiveRectangle() {
//
//}

int OpenCVImage::getLineStride() const {
    return getWidth();
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

rgb8_view_t OpenCVImage::make_rgb8_view_t() const {
	rgb8_view_t view =
		interleaved_view(
				getWidth(),
				getHeight(),
				(rgb8_view_t::value_type *)(getPixels()),
				getWidth()*getNChannels());
	return view;
}

gray8_view_t OpenCVImage::make_gray8_view_t() const {
	gray8_view_t view =
		interleaved_view(
				getWidth(),
				getHeight(),
				(gray8_view_t::value_type *)(getPixels()),
				getWidth());
	return view;
}

const char * OpenCVImage::getFilename() const {
	return _filename.c_str();
}

void OpenCVImage::setFilename(const char * filename) {
	_filename = filename;
}

OpenCVImage * OpenCVImage::makeSimilarImage() const {
	return copy(); //TODO change to make an empty image
}

OpenCVImage * OpenCVImage::load(char const * filename) const {
	IplImage * iplImage =cvLoadImage(filename);
	if (0 == iplImage)
		return NULL;
	OpenCVImage * image = new OpenCVImage(iplImage);
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
	IplImage* image = cvCreateImage(cvSize(width, height),IPL_DEPTH_8U,1);
	return new OpenCVImage(image);
}

//-------------Special for OpenCVImage

void OpenCVImage::swapRB() {
	cvConvertImage( _iplImage, _iplImage,CV_CVTIMG_SWAP_RB );
}

_IplImage * OpenCVImage::getIplImage() const {
	return _iplImage;
}

