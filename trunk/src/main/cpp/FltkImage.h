/*
 * FltkImage.h
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

#ifndef FLTKIMAGE_H_
#define FLTKIMAGE_H_

#include "BaseImage.h"

class Fl_Image;

class FltkImage : public BaseImage {
public:

	const static FltkImage * NULL_OBJECT;

	FltkImage(Fl_Image * flImage);
	virtual ~FltkImage();

	/** Returns the width of this image in pixels. */
	virtual int getWidth() const;

	/** Returns the height of this image in pixels. */
	virtual int getHeight() const;

	/** Returns the number of color channels in the image. The color channels can be
	*  accessed by toFloat(channelNumber, fp) and written by setPixels(channelNumber, fp).
	* @return 1 for gray scale images, 3 for RGB images
	*/
	virtual int getNChannels() const;

	/** Returns the depth of each channels. */
	virtual int getDepth() const;

	/** Returns a reference to this image's pixel array. The
	array type (byte[], short[], float[] or int[]) varies
	depending on the image type. */
	virtual unsigned char * getPixels() const;

	/** Returns true if this image uses an inverting LUT
	that displays zero as white and 255 as black. */
	virtual bool isInvertedLut() const;

	virtual bool isGray() const;

	virtual bool isGray8() const;

	virtual bool isGray16() const;

//-------------New members now part of base class SLImage

	virtual Fl_Image * getFlImage() const;

	virtual FltkImage * copy() const;

	virtual FltkImage * makeSimilarImage() const;

	virtual FltkImage * load(char const * filename) const;

	virtual bool saveAs(const char *filename);

	virtual FltkImage * createImage(int width, int height, int nChannels, int depth = 0) const;

protected:

};

#endif /* FLTKIMAGE_H_ */
