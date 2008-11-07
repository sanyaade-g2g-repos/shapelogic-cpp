/*
 * SLImage.h
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#ifndef SLIMAGE_H_
#define SLIMAGE_H_

#include <boost/gil/typedefs.hpp>

class Fl_Image;

/** This is a wrapper class around the real representation of the image.
 *
 * This should be an interface
 */
class SLImage {
public:
	SLImage() {}
	virtual ~SLImage() {}

	/** Returns the width of this image in pixels. */
	virtual int getWidth() const = 0;

	/** Returns the height of this image in pixels. */
	virtual int getHeight() const = 0;

//	virtual void setRoi(Rectangle roi) = 0;
//
//	virtual void setRoi(int x, int y, int rwidth, int rheight) = 0;
//
//	virtual Rectangle getRoi() = 0;

	virtual int getPixelCount() const = 0;

	/** Returns a reference to this image's pixel array. The
	array type (byte[], short[], float[] or int[]) varies
	depending on the image type. */
	virtual unsigned char * getPixels() const = 0;

	/** Sets a new pixel array for the image. The length of the array must be equal to width*height.
	Use setSnapshotPixels(null) to clear the snapshot buffer. */
	virtual void setPixels(unsigned char * pixels) = 0;

	/** Returns true if this image uses an inverting LUT
	that displays zero as white and 255 as black. */
	virtual bool isInvertedLut() const = 0;

	/** Returns the number of color channels in the image. The color channels can be
	*  accessed by toFloat(channelNumber, fp) and written by setPixels(channelNumber, fp).
	* @return 1 for grayscale images, 3 for RGB images
	*/
	virtual int getNChannels() const = 0;

	virtual bool isEmpty() const = 0;

	virtual bool isGray() const = 0;

	virtual bool isGray8() const = 0;

	virtual bool isGray16() const = 0;

	virtual bool isRgb() const = 0;

//	virtual Rectangle getActiveRectangle() = 0;

	virtual int getLineStride() const = 0;

//-------------New members now part of base class SLImage

	virtual Fl_Image * getFlImage() const = 0;

	virtual unsigned char * getBuffer() const = 0;

	virtual SLImage * copy() const = 0;

	virtual boost::gil::rgb8_view_t make_rgb8_view_t() const = 0;

	virtual boost::gil::gray8_view_t make_gray8_view_t() const = 0;

};

#endif /* SLIMAGE_H_ */
