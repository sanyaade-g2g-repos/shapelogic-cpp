/*
 * FltkImage.h
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#ifndef FLTKIMAGE_H_
#define FLTKIMAGE_H_

#include "SLImage.h"

class Fl_Image;

class FltkImage : public SLImage {
public:
	FltkImage(Fl_Image * _image);
	virtual ~FltkImage();

	/** Returns the width of this image in pixels. */
	virtual int getWidth();

	/** Returns the height of this image in pixels. */
	virtual int getHeight() = 0;

//	virtual void setRoi(Rectangle roi) = 0;
//
//	virtual void setRoi(int x, int y, int rwidth, int rheight) = 0;
//
//	virtual Rectangle getRoi() = 0;

	virtual int getPixelCount();

	/** Returns a reference to this image's pixel array. The
	array type (byte[], short[], float[] or int[]) varies
	depending on the image type. */
	virtual unsigned char * getPixels();

	/** Sets a new pixel array for the image. The length of the array must be equal to width*height.
	Use setSnapshotPixels(null) to clear the snapshot buffer. */
	virtual void setPixels(unsigned char * pixels);

	/** Returns true if this image uses an inverting LUT
	that displays zero as white and 255 as black. */
	virtual bool isInvertedLut();

	/** Returns the number of color channels in the image. The color channels can be
	*  accessed by toFloat(channelNumber, fp) and written by setPixels(channelNumber, fp).
	* @return 1 for grayscale images, 3 for RGB images
	*/
	virtual int getNChannels();

	virtual bool isEmpty();

	virtual bool isGray();

	virtual bool isGray8();

	virtual bool isGray16();

	virtual bool isRgb();

//	virtual Rectangle getActiveRectangle();

	virtual int getLineStride();

protected:
	Fl_Image * _image;
};

#endif /* FLTKIMAGE_H_ */
