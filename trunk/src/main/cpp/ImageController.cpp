/*
 * ImageController.cpp
 *
 *  Created on: Oct 6, 2008
 *      Author: Sami Badawi
 */

#include "ImageController.h"
#include <string>
#include <FL/Fl_JPEG_Image.H>

ImageController::ImageController() {
	_currentImage = NULL;
	_lastImage = NULL;
}

ImageController::~ImageController() {
	delete _currentImage;
	delete _lastImage;
}

void ImageController::run(const char *name, const char *arg)
{
	std::string command(name);
	if (command == "Invet")	invert();
}

void ImageController::undo()
{
	delete _currentImage;
	_currentImage =_lastImage;
	_lastImage = NULL;
}

void ImageController::open(const char *filename)
{
	  Fl_Image * image = new Fl_JPEG_Image(filename);
	  if ( image->h() == 0 ) {
	     delete image;
	     return;
	   }
	   if (_lastImage) delete _lastImage;
	   _lastImage = _currentImage;
	   _currentImage = image;
	   _filename = filename;
}

Fl_Image * ImageController::getCurrentImage()
{
	return _currentImage;
}

void ImageController::invert()
{
	  delete _lastImage;
	  _lastImage = _currentImage->copy();
	// get the image data
	  int height    = _currentImage->h();
	  int width     = _currentImage->w();
	  int channels  = _currentImage->d();
	  uchar * data      = (uchar *)_currentImage->data()[0];

	  // invert the image
	  for(int j=0;j<height;j++) for(int i=0;i<width;i++) for(int k=0;k<channels;k++) {
	    int index = (i+j*width) * channels+k;
	    data[index]=255-data[index];
	  }
	  _currentImage->uncache();
}
