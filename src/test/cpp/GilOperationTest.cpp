/*
 * BoostTest.cpp
 *
 * This file contains test of Boost
 *
 *  Created on: Oct 9, 2008
 *      Author: Sami Badawi
 */

#include <gtest/gtest.h>
#include <boost/lambda/lambda.hpp>
#include <GILOperation.h>
#include <FL/Fl_JPEG_Image.H>
#include <iostream>

namespace {
using namespace std;

//Fl_Image * image = NULL;
//Fl_Image * imageOut = NULL;

// Test the lambda expression in Boost
TEST(GILOperation, xGradientFile) {
	const char * inputFilename = "/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/embryos6.jpg";
	const char * outputFilename = "/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/embryos6out.jpg";
	GILOperation::xLuminosityGradient(inputFilename, outputFilename);
}


TEST(GILOperation, xGradientImage) {
	const char * inputFilename = "/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/embryos6.jpg";
	const char * outputFilename = "/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/embryos6out.jpg";
	Fl_Image * image = new Fl_JPEG_Image(inputFilename);
//	imageOut = new Fl_Image(image->w(), image->h(), image->d());;
	EXPECT_EQ(3, image->d());
	Fl_RGB_Image * rgbImage = dynamic_cast<Fl_RGB_Image *>(image);
	EXPECT_TRUE(rgbImage != NULL);
	Fl_Image * imageOut = image->copy();
	EXPECT_EQ(image->h(), imageOut->h());
	EXPECT_EQ(image->w(), imageOut->w());
	EXPECT_EQ(image->d(), imageOut->d());
//	GILOperation::fltkGradient(image,imageOut);
	cerr << "Done with GILOperation::fltkGradient().\n";
//	const char * data = image->data()[0];
//	const unsigned char * dataOut = (const unsigned char *) imageOut->data()[0];
//	EXPECT_EQ(208, *dataOut);
	image->uncache();
	imageOut->uncache();
	delete imageOut;
	delete image;
	cerr << "Done with test.\n";
}

}
