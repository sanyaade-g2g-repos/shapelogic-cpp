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
	for (int i=0; i<3; i++) {
		_forground[i] = 0;
		_background[i] = 255;
	}
}

ImageController::~ImageController() {
	delete _currentImage;
	delete _lastImage;
}

void ImageController::run(const char *name, const char *arg) {
	std::string command(name);
	if (command == "Invert")	invert();
	else if (command == "Fill")	fill();
	else if (command == "Clear")	clear();
	else if (command == "Undo")	undo();
}

void ImageController::undo() {
	Fl_Image * tempImage = _currentImage;
	_currentImage =_lastImage;
	_lastImage = tempImage;
}

void ImageController::open(const char *filename) {
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

Fl_Image * ImageController::getCurrentImage() {
	return _currentImage;
}

void ImageController::invert() {
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

void ImageController::clear() {
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
	    data[index]= _background[k];
	  }
	  _currentImage->uncache();
}

void ImageController::fill() {
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
	    data[index]= _forground[k];
	  }
	  _currentImage->uncache();
}
