/*
 * BaseImage.h
 *
 * The idea with this class is that it should be able to provide images of all
 * the classes FLTK, GIL and OpenCV.
 *
 * To begin with I will attempt to only have one image buffer stored at the
 * same time.
 *
 *  Created on: Now 11, 2008
 *      Author: Sami Badawi
 */

#ifndef BASEIMAGE_H_
#define BASEIMAGE_H_

#include "SLImage.h"

#include <boost/gil/typedefs.hpp>
#include <string>

class Fl_Image;

class BaseImage : public SLImage {
public:

	BaseImage(Fl_Image * flImage = 0);
	virtual ~BaseImage();

//	virtual void setRoi(Rectangle roi) = 0;
//
//	virtual void setRoi(int x, int y, int rwidth, int rheight) = 0;
//
//	virtual Rectangle getRoi() = 0;

	virtual int getPixelCount() const;

	/** Sets a new pixel array for the image. The length of the array must be equal to width*height.
	Use setSnapshotPixels(null) to clear the snapshot buffer. */
	virtual void setPixels(unsigned char * pixels);

	/** Returns true if this image uses an inverting LUT
	that displays zero as white and 255 as black. */
	virtual bool isInvertedLut() const;

	virtual bool isEmpty() const;

	virtual bool isGray() const;

	virtual bool isGray8() const;

	virtual bool isGray16() const;

	virtual bool isRgb() const;

//	virtual Rectangle getActiveRectangle();

	virtual int getLineStride() const;

//-------------New members now part of base class SLImage

	virtual boost::gil::rgb8_view_t make_rgb8_view_t() const;

	virtual boost::gil::gray8_view_t make_gray8_view_t() const;

	virtual const char * getFilename() const;

	virtual void setFilename(const char * filename);

	virtual BaseImage * makeSimilarImage() const;

protected:
	mutable Fl_Image * _flImage;

	std::string _filename;
};

#endif /* BASEIMAGE_H_ */
