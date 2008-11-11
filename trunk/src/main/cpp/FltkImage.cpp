/*
 * FltkImage.cpp
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#include "FltkImage.h"
#include "SLStringUtil.h"

#include <boost/gil/extension/dynamic_image/image_view_factory.hpp> //for interleaved_view()

#include <FL/Fl_Image.H>
#include <FL/Fl_Shared_Image.H>

using namespace boost::gil;

//--------------static
const FltkImage * FltkImage::NULL_OBJECT = new FltkImage(NULL);

FltkImage::FltkImage(Fl_Image * flImage) : BaseImage(flImage) {

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

/** Returns the number of color channels in the image. The color channels can be
*  accessed by toFloat(channelNumber, fp) and written by setPixels(channelNumber, fp).
* @return 1 for grayscale images, 3 for RGB images
*/
int FltkImage::getNChannels() const {
	if (0 !=_flImage)
		return _flImage->d();
	return 0;
}

/** Returns the depth of each channels. */
int FltkImage::getDepth() const {
	return 8; //Fltk only handles one depth 8 bits
}

/** Returns a reference to this image's pixel array. The
array type (byte[], short[], float[] or int[]) varies
depending on the image type. */
unsigned char * FltkImage::getPixels() const {
	if (0 == _flImage)
		return 0;
	return (unsigned char *) *_flImage->data();
}

/** Returns true if this image uses an inverting LUT
that displays zero as white and 255 as black. */
bool FltkImage::isInvertedLut() const {
    return false;
}

bool FltkImage::isGray() const {
	return 1 == getNChannels();
}

bool FltkImage::isGray8() const {
	return 1 == getNChannels();
}

bool FltkImage::isGray16() const {
	return false;
}

Fl_Image * FltkImage::getFlImage() const {
	return _flImage;
}

FltkImage * FltkImage::copy() const {
	Fl_Image * copyOfFlImage = _flImage->copy();
	FltkImage * result = new FltkImage(copyOfFlImage);
	result->setFilename(getFilename());
	return result;
}

FltkImage * FltkImage::makeSimilarImage() const {
	return copy(); //TODO change to make an empty image
}

FltkImage * FltkImage::load(char const * filename) const {
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

bool FltkImage::saveAs(const char *filename) {
	return false; //There are no save in FLTK
}

FltkImage * FltkImage::createImage(int width, int height, int nChannels, int depth) const {
	uchar * buffer = new uchar[width * height * nChannels];
	Fl_RGB_Image * image = new Fl_RGB_Image(buffer, width, height, nChannels);
	return new FltkImage(image);
}
