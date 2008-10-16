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
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Bitmap.H>
#include <FL/Fl_Pixmap.H>
#include <iostream>
#include <string>

namespace {
using namespace std;
using namespace boost::gil;

const string testImageDir("/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/");

TEST(GILOperation, xGradientFile) {
	//There is a problem with using relative path, you can call bjam from either
	//shapelogic-cpp or shapelogic-cpp/src/test, and they will be the current dir
	string inputFilename = testImageDir + "embryos6.jpg";
	string outputFilename = testImageDir + "embryos6out.jpg";
	GILOperation::xLuminosityGradient(inputFilename.c_str(), outputFilename.c_str());
}

TEST(GILOperation, xSobelImage) {
	string inputFilename = testImageDir + "embryos6.jpg";
	Fl_Image * image = new Fl_JPEG_Image(inputFilename.c_str());
	EXPECT_EQ(3, image->d());
	EXPECT_EQ(3, num_channels<boost::gil::rgb8_view_t>::value);
	Fl_RGB_Image * rgbImage = dynamic_cast<Fl_RGB_Image *>(image);
	EXPECT_TRUE(rgbImage != NULL);
	Fl_Image * imageOut = rgbImage->copy();
	GILOperation::fltkSobelX(image, imageOut);
	rgb8_view_t view = GILOperation::make_rgb8_view_t(image);
	int fistByte = view.row_begin(0)[0][0];
	EXPECT_EQ(191, fistByte);
	EXPECT_EQ(image->h(), imageOut->h());
	EXPECT_EQ(image->w(), imageOut->w());
	EXPECT_EQ(image->d(), imageOut->d());
	delete imageOut;
	delete image;
}

TEST(GILOperation, xSobelImageGrayGif) {
	string inputFilename = testImageDir + "spot1Noise10.gif";
	Fl_Image * image = new Fl_GIF_Image(inputFilename.c_str());
	EXPECT_EQ(1, image->d());
	Fl_Pixmap * pixmapImage = dynamic_cast<Fl_Pixmap *>(image); //GIF is a Fl_Pixmap with LUT not a gray bitmap
	EXPECT_TRUE(pixmapImage != NULL);
//TODO fix. This did not work got and assert failure
//	Fl_Image * imageOut = pixmapImage->copy();
//	GILOperation::fltkSobelX(image, imageOut);
//	delete imageOut;
	delete image;
}

TEST(GILOperation, xSobelImageGrayPng) {
	string inputFilename = testImageDir + "spot1Noise10.png";
	Fl_Image * image = new Fl_PNG_Image(inputFilename.c_str());
	EXPECT_EQ(3, image->d()) << "gray image does not have 1 channel";
	Fl_RGB_Image * rgbImage = dynamic_cast<Fl_RGB_Image *>(image); //PNG is a Fl_RGB_Pixmap even if it is a gray image
	EXPECT_TRUE(rgbImage != NULL) << "png image is not of type Fl_RGB_Image";
	Fl_Image * imageOut = rgbImage->copy();
	GILOperation::fltkSobelX(image, imageOut);
	delete imageOut;
	delete image;
}

}
