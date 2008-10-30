/*
 * ImageController.h
 *
 *  Created on: Oct 6, 2008
 *      Author: Sami Badawi
 */

#ifndef IMAGECONTROLLER_H_
#define IMAGECONTROLLER_H_

class Fl_Image;
//class Fl_Shared_Image;
#include <string>

class ImageController {
public:
	ImageController();
	virtual ~ImageController();
	//Singelton like instance that is used for the screen
	static ImageController * getInstance();

//Image operations

	virtual void run(const char * name, const char * arg);

	virtual void about();
	virtual void blur();
	virtual void clear();
	virtual void edge();
	virtual void fill();
	virtual void invert();
	virtual void open(const char * filename);
	virtual void quit();
	virtual void save();
	virtual void saveAs(const char * filename);
	virtual void sobelX();
	virtual void sobelXY();
	virtual void sobelY();
	virtual void undo();

	virtual void startOperation();
	virtual void endOperation();

//Getter and setter methods
	virtual Fl_Image * getCurrentImage();
	virtual std::string getFilename();

	unsigned char _foreground[3];
	unsigned char _background[3];
private:
	Fl_Image * _currentImage;
	Fl_Image * _lastImage;
	Fl_Image * _nextImage;
	std::string _filename;
    bool _directOperation;
    static ImageController * _instance;
};

#endif /* IMAGECONTROLLER_H_ */
