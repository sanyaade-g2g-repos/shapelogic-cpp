/*
 * ImageController.h
 *
 *  Created on: Oct 6, 2008
 *      Author: Sami Badawi
 */

#ifndef IMAGECONTROLLER_H_
#define IMAGECONTROLLER_H_

class Fl_Image;
class SLImage;

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
	virtual void setBrush(const char * brush);
	virtual const char * getBrush();
	virtual void clear();
	virtual void fill();
	virtual void flipHorizontally();
	virtual void flipVertically();
	virtual void gray8();
	virtual void invert();
	virtual void laplace();
	virtual void open(const char * filename);
	virtual void quit();
	virtual void rgb8();
	virtual void save();
	virtual void saveAs(const char * filename);
	virtual void signedGradient();
	virtual void sobelX();
	virtual void sobelXY();
	virtual void sobelY();
	virtual void swapRB();
	virtual void undo();

	virtual void startOperation();
	virtual void endOperation();

//Getter and setter methods
	virtual Fl_Image * getCurrentImage();
	virtual const char * getFilename();

	unsigned char _foreground[3];
	unsigned char _background[3];
private:
	SLImage * _currentImage;
	SLImage * _lastImage;
	SLImage * _nextImage;
    bool _directOperation;
	const char * _brush;

	static ImageController * _instance;
};

#endif /* IMAGECONTROLLER_H_ */
