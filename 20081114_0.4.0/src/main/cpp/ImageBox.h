/*
 * ImageBox.h
 *
 * The purpose of ImageBox is to add an event handler to the Fl_Box that is
 * used to display the main image.
 *
 *  Created on: Oct 28, 2008
 *      Author: Sami Badawi
 */

#ifndef IMAGEBOX_H_
#define IMAGEBOX_H_

#include <FL/Fl_Box.H>
#include <ctime>

class Fl_Scroll;
class Fl_Image;
class ImageController;

class ImageBox : public Fl_Box {
	 Fl_Scroll * _scroll;
	 const char * _brushType;

public:
	ImageBox(int x, int y, int w, int h, const char *l=0);
	virtual ~ImageBox();

	Fl_Image * getImage();
	virtual void setScroll(Fl_Scroll *val);
	virtual void setBrushType(const char * brushType);
	virtual int handle(int e);

//Handler methods returns true if the operation was successful
    virtual bool pointDraw();
    virtual bool showPixel();
    virtual bool sampleColor();

    virtual void refresh(bool timedependent = false);

    int instanceNo; //TODO take out
    time_t _timeOfLastRefreshInSeconds;
};

#endif /* IMAGEBOX_H_ */
