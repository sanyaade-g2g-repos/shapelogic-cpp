/*
 * ImageBox.cpp
 *
 * The purpose of ImageBox is to add an event handler to the Fl_Box that is
 * used to display the main image.
 *
 *  Created on: Oct 28, 2008
 *      Author: Sami Badawi
 */

#include "ImageBox.h"
#include "ImageController.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Scroll.H>
#include <FL/fl_ask.H>

using namespace std;

static int imageBoxCount = 0;

ImageBox::ImageBox(int x, int y, int w, int h, const char *l) :
	Fl_Box(x,y,w,h,l) {
	imageBoxCount++;
	instanceNo = imageBoxCount;
	_brushType = "";
//	cout << "ImageBox::ImageBox() # " << instanceNo << " created.\n ";
}

ImageBox::~ImageBox() {
}

void ImageBox::setScroll(Fl_Scroll *val) {
    _scroll = val;
}

void ImageBox::setBrushType(const char * brushType) {
    _brushType = brushType;
}

Fl_Image *  ImageBox::getImage() {
	return ImageController::getInstance()->getCurrentImage();
}

int ImageBox::handle(int e) {
	_brushType = ImageController::getInstance()->getBrush();
	bool pen = (0 == strcmp("Pen",_brushType) );
	bool pointInfo = (0 == strcmp("Point_info",_brushType) );
	bool doSampleColor = (0 == strcmp("Sample_color",_brushType));
	if ( e == FL_PUSH ) {
		if (pen) {
			pointDraw();
			refresh();
			return 1; //In order to get drag
		}
		else if (pointInfo)
			showPixel();
		else if (doSampleColor)
			sampleColor();
	}
	else if ( e == FL_DRAG ) {
		if (pen) {
			pointDraw();
			refresh(true);
		}
	}
	else if ( e == FL_RELEASE ) {
		if (pen) {
			pointDraw();
			refresh();
		}
	}
	int returnValue = Fl_Box::handle(e);
	return (returnValue);
}

void ImageBox::pointDraw() {
	Fl_Image * image = getImage(); //this->image();
	if (image == NULL)
		return;
	int x = Fl::event_x() - _scroll->x() + _scroll->hscrollbar.value();
	int y = Fl::event_y() - _scroll->y() + _scroll->scrollbar.value();
	int width     = image->w();
	int channels  = image->d();
	uchar * data      = (uchar *)image->data()[0];
	if (3 == channels) {
		int index = ((width * y) + x)*3;
		for (int i = 0; i < channels; i++)
			data[index+i] = ImageController::getInstance()->_foreground[i];
	}
	else if (1 == channels) {
		int index = ((width * y) + x);
		data[index] = ImageController::getInstance()->_foreground[0];
	}
}

void ImageBox::showPixel() {
	Fl_Image * image = getImage(); //this->image();
	if (image == NULL)
		return;
	int x = Fl::event_x() - _scroll->x() + _scroll->hscrollbar.value();
	int y = Fl::event_y() - _scroll->y() + _scroll->scrollbar.value();
	int width     = image->w();
	int channels  = image->d();
	uchar * data      = (uchar *)image->data()[0];
	ostringstream stringStream;
	stringStream << "Frame x,y: ";
	stringStream <<
		Fl::event_x() << ", " <<
		Fl::event_y() <<
		" Image x,y: " << x << ", " << y << endl <<
		"Color: ";
	if (3 == channels) {
		int index = ((width * y) + x)*3;
		for (int i = 0; i < channels; i++)
			stringStream << (int)data[index+i] << ", ";
	}
	else if (1 == channels) {
		int index = ((width * y) + x);
		stringStream << (int)data[index];
	}
	stringStream << endl;
	fl_message(stringStream.str().c_str());
}

void ImageBox::sampleColor() {
	Fl_Image * image = getImage(); //this->image();
	if (image == NULL)
		return;
	int x = Fl::event_x() - _scroll->x() + _scroll->hscrollbar.value();
	int y = Fl::event_y() - _scroll->y() + _scroll->scrollbar.value();
	int width     = image->w();
	int channels  = image->d();
	uchar * data      = (uchar *)image->data()[0];
	if (3 == channels) {
		int index = ((width * y) + x)*3;
		for (int i = 0; i < channels; i++)
			ImageController::getInstance()->_foreground[i] = data[index+i];
	}
	else if (1 == channels) {
		int index = ((width * y) + x);
		for (int i = 0; i < 3; i++)
			ImageController::getInstance()->_foreground[i] = data[index];
	}
}

void ImageBox::refresh(bool timedependent) {
	bool doRefresh = true;
	if (timedependent) {
		time_t now = time(NULL);
		if (now == _timeOfLastRefreshInSeconds)
			doRefresh = false;
		_timeOfLastRefreshInSeconds = now;
	}
	if (doRefresh) {
		if (NULL != getImage())
			getImage()->uncache();
		_scroll->parent()->redraw();
	}
}
