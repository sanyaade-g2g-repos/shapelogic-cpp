/*
 * ImageController.cpp
 *
 *  Created on: Oct 6, 2008
 *      Author: Sami Badawi
 */

#include "ImageController.h"
#include "GILOperation.h"
#include "SLStringUtil.h"
#include <string>
#include <cstdlib>
#include <FL/Fl_Bitmap.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Shared_Image.H> // Image I/O
#include <FL/fl_ask.H>

using namespace std;

ImageController::ImageController() {
	fl_register_images();
	_currentImage = NULL;
	_lastImage = NULL;
	for (int i=0; i<3; i++) {
		_foreground[i] = 0;
		_background[i] = 255;
	}
}

ImageController::~ImageController() {
	delete _currentImage;
	delete _lastImage;
}

void ImageController::run(const char *name, const char *arg) {
	std::string command(name);
	if (command == "About") about();
	else if (command == "Blur") blur();
	else if (command == "Clear") clear();
	else if (command == "Edge")	edge();
	else if (command == "Fill")	fill();
	else if (command == "Invert") invert();
	else if (command == "Open")	open(arg);
	else if (command == "Quit") quit();
	else if (command == "Save") save();
	else if (command == "Save_As") saveAs(arg);
	else if (command == "Sobel_X") sobelX();
	else if (command == "Sobel_XY") sobelXY();
	else if (command == "Sobel_Y") sobelY();
	else if (command == "Undo")	undo();
}

void ImageController::undo() {
	Fl_Image * tempImage = _currentImage;
	_currentImage =_lastImage;
	_lastImage = tempImage;
}

void ImageController::open(const char *filename) {
	if (SLStringUtil::empty(filename))
		return;
	Fl_Shared_Image *sharedImage = Fl_Shared_Image::get(filename);
	//	  Fl_Image * image = new Fl_JPEG_Image(filename);
	Fl_Image * image = sharedImage->copy();
	sharedImage->release();
	if ( image->h() == 0 ) {
		delete image;
		return;
	}
	delete _lastImage;
	_lastImage = _currentImage;
	_currentImage = image;
	_filename = filename;
}

void ImageController::saveAs(const char *filename) {
	if (SLStringUtil::empty(filename))
		return;
	GILOperation::saveAnyImage(filename, _currentImage);
	if (false) {
		std::string message = "The file could not be written ";
		message += filename;
		fl_message(message.c_str());
	}
}

void ImageController::save() {
	saveAs(_filename.c_str());
}

Fl_Image * ImageController::getCurrentImage() {
	return _currentImage;
}

void ImageController::startOperation() {
	  delete _lastImage;
	  _lastImage = NULL;
	  if (_directOperation) {
		  _lastImage = _currentImage->copy();
	  }
	  else {
		  //Create a new image with the same properties
		  const uchar* buffer = new uchar[_currentImage->w() * _currentImage->h() * _currentImage->d()];
		  if (_currentImage->d() == 1)
			  _nextImage = new Fl_Bitmap(buffer,_currentImage->w(), _currentImage->h());
		  else
			  _nextImage = new Fl_RGB_Image(buffer,_currentImage->w(), _currentImage->h(), _currentImage->d());
	  }
}

void ImageController::endOperation() {
	  if (_directOperation) {

	  }
	  else {
		  _lastImage = _currentImage;
		  _currentImage = _nextImage;
		  _nextImage = NULL;
	  }
}

void ImageController::invert() {
	_directOperation = true;
	startOperation();
	int height    = _currentImage->h();
	int width     = _currentImage->w();
	int channels  = _currentImage->d();
	uchar * data      = (uchar *)_currentImage->data()[0];

	// invert the image
	for(int j=0;j<height;j++) for(int i=0;i<width;i++) for(int k=0;k<channels;k++) {
		int index = (i+j*width) * channels+k;
		data[index]=255-data[index];
	}
	endOperation();
}

void ImageController::clear() {
	_directOperation = true;
	startOperation();
	int height    = _currentImage->h();
	int width     = _currentImage->w();
	int channels  = _currentImage->d();
	uchar * data      = (uchar *)_currentImage->data()[0];

	// invert the image
	for(int j=0;j<height;j++) for(int i=0;i<width;i++) for(int k=0;k<channels;k++) {
		int index = (i+j*width) * channels+k;
		data[index]= _background[k];
	}
	endOperation();
}

void ImageController::fill() {
	_directOperation = true;
	startOperation();
	int height    = _currentImage->h();
	int width     = _currentImage->w();
	int channels  = _currentImage->d();
	uchar * data      = (uchar *)_currentImage->data()[0];

	// invert the image
	for(int j=0;j<height;j++) for(int i=0;i<width;i++) for(int k=0;k<channels;k++) {
		int index = (i+j*width) * channels+k;
		data[index]= _foreground[k];
	}
	endOperation();
}

void ImageController::edge() {
	_directOperation = false;
	startOperation();
	GILOperation::fltkGradient(_currentImage, _nextImage);
	endOperation();
}

void ImageController::sobelX() {
	_directOperation = false;
	startOperation();
	GILOperation::fltkSobelX(_currentImage, _nextImage);
	endOperation();
}

void ImageController::sobelY() {
	_directOperation = false;
	startOperation();
	GILOperation::fltkSobelY(_currentImage, _nextImage);
	endOperation();
}

void ImageController::sobelXY() {
	_directOperation = false;
	startOperation();
	GILOperation::fltkSobelXY(_currentImage, _nextImage);
	endOperation();
}

void ImageController::blur() {
	_directOperation = false;
	startOperation();
	GILOperation::fltkBlur(_currentImage, _nextImage);
	endOperation();
}

void ImageController::quit() {
	exit(0);
}

void ImageController::about() {
	string message = "ShapeLogic C++ 0.1\nAuthor Sami Badawi\nMIT license\nCompile date: ";
	message += __DATE__;
	fl_message(message.c_str());
}

