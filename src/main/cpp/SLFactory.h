/*
 * SLFactory.h
 *
 *  This is the main factory for ShapeLogic C++.
 *
 *  This might be split into more specialized factory if the need arise.
 *
 *  Created on: Nov 7, 2008
 *      Author: Sami Badawi
 */

#ifndef SLFACTORY_H_
#define SLFACTORY_H_

class SLImage;
class FltkImage;
class OpenCVImage;

class SLFactory {
public:
	SLFactory();
	virtual ~SLFactory();

	//Get the instance used in the GUI
	static SLFactory * getInstance();

	const char * getImageType () const;
	void setImageType(const char * imageType);

	SLImage * makeSLImage(const char * filename) const;

	FltkImage * makeFltkImage(const char * filename) const;

	OpenCVImage * makeOpenCVImage(const char * filename) const;

	bool saveImageAs(SLImage * image, const char *filename);

protected:
	const char * _imageType;

	static SLFactory * INSTANCE;
};

#endif /* SLFACTORY_H_ */
