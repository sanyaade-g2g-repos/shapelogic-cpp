/*
 * OpenCVImage.h
 *
 * The idea with this class is that it should be able to provide images of all
 * the classes FLTK, GIL and OpenCV.
 *
 * To begin with I will attempt to only have one image buffer stored at the
 * same time.
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#ifndef OPENCVIMAGE_H_
#define OPENCVIMAGE_H_

#include "SLImage.h"

#include <boost/gil/typedefs.hpp>
#include <string>

class Fl_Image;
struct _IplImage;

class OpenCVImage : public SLImage {
public:
	OpenCVImage(_IplImage * _image);
	virtual ~OpenCVImage();

	/** Returns the width of this image in pixels. */
	virtual int getWidth() const;

	/** Returns the height of this image in pixels. */
	virtual int getHeight() const;

//	virtual void setRoi(Rectangle roi) = 0;
//
//	virtual void setRoi(int x, int y, int rwidth, int rheight) = 0;
//
//	virtual Rectangle getRoi() = 0;

	virtual int getPixelCount() const;

	/** Returns a reference to this image's pixel array. The
	array type (byte[], short[], float[] or int[]) varies
	depending on the image type. */
	virtual unsigned char * getPixels() const;

	/** Sets a new pixel array for the image. The length of the array must be equal to width*height.
	Use setSnapshotPixels(null) to clear the snapshot buffer. */
	virtual void setPixels(unsigned char * pixels);

	/** Returns true if this image uses an inverting LUT
	that displays zero as white and 255 as black. */
	virtual bool isInvertedLut() const;

	/** Returns the number of color channels in the image. The color channels can be
	*  accessed by toFloat(channelNumber, fp) and written by setPixels(channelNumber, fp).
	* @return 1 for gray scale images, 3 for RGB images
	*/
	virtual int getNChannels() const;

	virtual bool isEmpty() const;

	virtual bool isGray() const;

	virtual bool isGray8() const;

	virtual bool isGray16() const;

	virtual bool isRgb() const;

//	virtual Rectangle getActiveRectangle();

	virtual int getLineStride() const;

//-------------New members now part of base class SLImage

	virtual Fl_Image * getFlImage() const;

	virtual OpenCVImage * copy() const;

	virtual boost::gil::rgb8_view_t make_rgb8_view_t() const;

	virtual boost::gil::gray8_view_t make_gray8_view_t() const;

	virtual const char * getFilename() const;

	virtual void setFilename(const char * filename);

	virtual OpenCVImage * makeSimilarImage() const;

	virtual _IplImage * getIplImage() const;

	virtual OpenCVImage * load(char const * filename) const;

	virtual bool saveAs(const char *filename);

	//-------------Special for OpenCVImage

	virtual void swapRB();

protected:
	//Now a secondary image, without separated buffer, should be instantiated lazily
	mutable Fl_Image * _flImage;

	//Primary image
	_IplImage * _iplImage;

	std::string _filename;
};

#endif /* OPENCVIMAGE_H_ */
