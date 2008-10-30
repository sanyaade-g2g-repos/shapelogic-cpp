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
#include <iostream>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Scroll.H>

using namespace std;

static const string DRAW("pointDraw");
static const string SHOW_PIXEL("showPixel");
static int imageBoxCount = 0;

ImageBox::ImageBox(int x, int y, int w, int h, const char *l) :
	Fl_Box(x,y,w,h,l) {
	_brushType = DRAW.c_str();
	imageBoxCount++;
	instanceNo = imageBoxCount;
	cout << "ImageBox::ImageBox() # " << instanceNo << " created.\n ";
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
	if ( e == FL_PUSH ) {
		if (DRAW==_brushType) {
			pointDraw();
			refresh();
			return 1; //In order to get drag
		}
		else
			showPixel();
	}
	else if ( e == FL_DRAG ) {
		if (DRAW==_brushType) {
			pointDraw();
			refresh(true);
		}
	}
	else if ( e == FL_RELEASE ) {
		if (DRAW==_brushType) {
			pointDraw();
			refresh();
		}
	}
	int returnValue = Fl_Box::handle(e);
//	cout << "returnValue:" << returnValue << endl;
	return (returnValue);
}

void ImageBox::pointDraw() {
	Fl_Image * image = getImage(); //this->image();
	if (image != NULL) {
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
}

void ImageBox::showPixel() {
	cout << "event_x,event_y: ";
	cout <<
		Fl::event_x() << ", " <<
		Fl::event_y() <<
		" Hit on box: " <<
		Fl::event_x() - _scroll->x() + _scroll->hscrollbar.value() << ", " <<
		Fl::event_y() - _scroll->y() + _scroll->scrollbar.value() << "\n";
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
