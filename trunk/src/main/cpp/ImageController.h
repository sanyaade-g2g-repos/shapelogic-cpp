/*
 * ImageController.h
 *
 *  Created on: Oct 6, 2008
 *      Author: Sami Badawi
 */

#ifndef IMAGECONTROLLER_H_
#define IMAGECONTROLLER_H_

class Fl_Image;
#include <string>

class ImageController {
public:
	ImageController();
	virtual ~ImageController();

//Image operations
	virtual void open(const char * filename);

	virtual void run(const char * name, const char * arg);
	virtual void clear();
	virtual void fill();
	virtual void invert();
	virtual void undo();

	virtual void startOperation();

//Getter and setter methods
	virtual Fl_Image * getCurrentImage();

	unsigned char _foreground[3];
	unsigned char _background[3];
private:
	Fl_Image * _currentImage;
	Fl_Image * _lastImage;
	std::string _filename;
};

#endif /* IMAGECONTROLLER_H_ */
