/*
 * ImageController.cpp
 *
 *  Created on: Oct 6, 2008
 *      Author: Sami Badawi
 */

#include "ImageController.h"

#include "GILOperation.h"
#include "FltkImage.h"
#include "SLImage.h"
#include "SLStringUtil.h"
#include "SLFactory.h"

#include <string>
#include <cstdlib>
#include <FL/fl_ask.H>

using namespace std;

ImageController * ImageController::_instance = NULL;

static char messageBuffer[1024];

ImageController::ImageController() {
	_currentImage = NULL;
	_lastImage = NULL;
	for (int i=0; i<3; i++) {
		_foreground[i] = 0;
		_background[i] = 255;
	}
	_brush = "";
}

ImageController::~ImageController() {
	delete _currentImage;
	delete _lastImage;
}

ImageController * ImageController::getInstance() {
	if (_instance == NULL) {
		_instance = new ImageController();
	}
	return _instance;
}

void ImageController::run(const char *name, const char *arg) {
	std::string command(name);
	if (command == "About") about();
	else if (command == "Blur") blur();
	else if (command == "Brush") setBrush(arg);
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
	SLImage * tempImage = _currentImage;
	_currentImage =_lastImage;
	_lastImage = tempImage;
}

void ImageController::open(const char *filename) {
	SLImage * image = SLFactory::getInstance()->makeSLImage(filename);
	if ( 0 == image )
		return;
	delete _lastImage;
	_lastImage = _currentImage;
	_currentImage = image;
	_filename = filename;
}

void ImageController::saveAs(const char *filename) {
	if (SLStringUtil::empty(filename))
		return;
	if (GILOperation::saveAnyImage(filename, _currentImage))
		_filename = filename;
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
	return _currentImage->getFlImage();
}

string ImageController::getFilename() {
	return _filename;
}

void ImageController::startOperation() {
	  delete _lastImage;
	  _lastImage = NULL;
	  if (_directOperation) {
		  _lastImage = _currentImage->copy();
	  }
	  else {
		  _nextImage = SLFactory::getInstance()->makeSimilarImage(_currentImage);
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
	int height    = _currentImage->getHeight();
	int width     = _currentImage->getWidth();
	int channels  = _currentImage->getNChannels();
	uchar * data      = (uchar *)_currentImage->getBuffer();

	// invert the image
	for(int j=0;j<height;j++) for(int i=0;i<width;i++) for(int k=0;k<channels;k++) {
		int index = (i+j*width) * channels+k;
		data[index]=255-data[index];
	}
	endOperation();
}

void ImageController::setBrush(const char * brush) {
	_brush = brush;
}

const char * ImageController::getBrush() {
	return _brush;
}

void ImageController::clear() {
	_directOperation = true;
	startOperation();
	int height    = _currentImage->getHeight();
	int width     = _currentImage->getWidth();
	int channels  = _currentImage->getNChannels();
	uchar * data      = (uchar *)_currentImage->getBuffer();

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
	int height    = _currentImage->getHeight();
	int width     = _currentImage->getWidth();
	int channels  = _currentImage->getNChannels();
	uchar * data      = (uchar *)_currentImage->getBuffer();

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
	string message = "ShapeLogic C++ 0.3\n"
			"Author Sami Badawi\n"
			"http://www.shapelogic.org\n"
			"Compile date: ";
	message += __DATE__;
	strcpy(messageBuffer, message.c_str());
	fl_message(messageBuffer);
}

