/*
 * ImageController.cpp
 *
 *  Created on: Oct 6, 2008
 *      Author: Sami Badawi
 */

#include "ImageController.h"

#include "GILOperation.h"
#include "OpenCVOperations.h"
#include "SLImage.h"
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
	_nextImage = NULL;
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
	else if (command == "AdaptiveThreshold") adaptiveThreshold();
	else if (command == "Blur") blur();
	else if (command == "Brush") setBrush(arg);
	else if (command == "Clear") clear();
	else if (command == "Dilate") dilate();
	else if (command == "Erode") erode();
	else if (command == "Fill")	fill();
	else if (command == "Flip_Horizontally") flipHorizontally();
	else if (command == "Flip_Vertically") flipVertically();
	else if (command == "Gray8") gray8();
	else if (command == "Invert") invert();
	else if (command == "Canny_Edge") cannyEdge();
	else if (command == "Open")	open(arg);
	else if (command == "Quit") quit();
	else if (command == "RGB8") rgb8();
	else if (command == "Save") save();
	else if (command == "Save_As") saveAs(arg);
	else if (command == "Signed_Gradient") signedGradient();
	else if (command == "Sobel_X") sobelX();
	else if (command == "Sobel_XY") sobelXY();
	else if (command == "Sobel_Y") sobelY();
	else if (command == "Swap_RB") swapRB();
	else if (command == "Threshold") threshold();
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
	image->setFilename(filename);
	delete _lastImage;
	_lastImage = _currentImage;
	_currentImage = image;
}

void ImageController::saveAs(const char *filename) {
	bool success = SLFactory::getInstance()->saveImageAs(_currentImage, filename);
	if (!success) {
		std::string message = "The file could not be written ";
		message += filename;
		fl_message(message.c_str());
	}
}

void ImageController::save() {
	saveAs(getFilename());
}

Fl_Image * ImageController::getCurrentImage() {
	return _currentImage->getFlImage();
}

const char * ImageController::getFilename() {
	if (_currentImage)
		return _currentImage->getFilename();
	return "";
}

void ImageController::startOperation() {
	  delete _lastImage;
	  _lastImage = NULL;
	  if (_directOperation) {
		  _lastImage = _currentImage->copy();
	  }
	  else {
		  _nextImage = _currentImage->makeSimilarImage();
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
	uchar * data      = (uchar *)_currentImage->getPixels();

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
	uchar * data      = (uchar *)_currentImage->getPixels();

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
	uchar * data      = (uchar *)_currentImage->getPixels();

	// invert the image
	for(int j=0;j<height;j++) for(int i=0;i<width;i++) for(int k=0;k<channels;k++) {
		int index = (i+j*width) * channels+k;
		data[index]= _foreground[k];
	}
	endOperation();
}

void ImageController::signedGradient() {
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
	string message = "ShapeLogic C++ 0.5\n"
			"Author Sami Badawi\n"
			"http://www.shapelogic.org\n"
			"Compile date: ";
	message += __DATE__;
	strcpy(messageBuffer, message.c_str());
	fl_message(messageBuffer);
}

void ImageController::cannyEdge() {
	if (_currentImage->isRgb())
		gray8();
	_directOperation = false;
	startOperation();
	OpenCVOperations::cannyEdge(_currentImage, _nextImage);
	endOperation();
}

void ImageController::flipHorizontally() {
	_directOperation = false;
	startOperation();
	OpenCVOperations::flipHorizontally(_currentImage, _nextImage);
	endOperation();
}

void ImageController::flipVertically() {
	_directOperation = false;
	startOperation();
	OpenCVOperations::flipVertically(_currentImage, _nextImage);
	endOperation();
}

void ImageController::swapRB() {
	_directOperation = false;
	startOperation();
	OpenCVOperations::swapRB(_currentImage, _nextImage);
	endOperation();
}

//turn image into type gray 8 bit
void ImageController::gray8() {
	if (_currentImage->isGray())
		return;
	delete _lastImage;
	_lastImage = NULL;
	_nextImage = _currentImage->createImage(_currentImage->getWidth(),
			_currentImage->getHeight(), 1, _currentImage->getDepth());
	GILOperation::rgbToGray(_currentImage, _nextImage);
	_lastImage = _currentImage;
	_currentImage = _nextImage;
	_nextImage = NULL;
}

void ImageController::rgb8() {
	if (_currentImage->isRgb())
		return;
	delete _lastImage;
	_lastImage = NULL;
	_nextImage = _currentImage->createImage(_currentImage->getWidth(),
			_currentImage->getHeight(), 3, _currentImage->getDepth());
	GILOperation::grayToRgb(_currentImage, _nextImage);
	_lastImage = _currentImage;
	_currentImage = _nextImage;
	_nextImage = NULL;
}

void ImageController::threshold() {
	_directOperation = false;
	startOperation();
	OpenCVOperations::threshold(_currentImage, _nextImage, 127.);
	endOperation();
}

void ImageController::adaptiveThreshold() {
	if (_currentImage->isRgb())
		gray8();
	_directOperation = false;
	startOperation();
	OpenCVOperations::adaptiveThreshold(_currentImage, _nextImage);
	endOperation();
}

void ImageController::dilate() {
	_directOperation = false;
	startOperation();
	OpenCVOperations::dilate(_currentImage, _nextImage);
	endOperation();
}

void ImageController::erode() {
	_directOperation = false;
	startOperation();
	OpenCVOperations::erode(_currentImage, _nextImage);
	endOperation();
}

