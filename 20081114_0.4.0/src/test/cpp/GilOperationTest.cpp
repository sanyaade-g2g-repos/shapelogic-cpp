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
#include <FltkImage.h>
#include <OpenCVImage.h>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Bitmap.H>
#include <FL/Fl_Pixmap.H>
#include <iostream>
#include <string>

namespace {
using namespace std;
using namespace boost::gil;

//TODO have a way to find the top directory and give address relative to that
const string testImageDir("./src/test/resources/images/particles/");

TEST(GILOperation, xGradientFile) {
	//There is a problem with using relative path, you can call bjam from either
	//shapelogic-cpp or shapelogic-cpp/src/test, and they will be the current dir
	string inputFilename = testImageDir + "embryos6.jpg";
	string outputFilename = testImageDir + "embryos6out.jpg";
	GILOperation::xLuminosityGradient(inputFilename.c_str(), outputFilename.c_str());
}

TEST(GILOperation, xSobelImage) {
	string inputFilename = testImageDir + "embryos6.jpg";
	OpenCVImage * image = OpenCVImage::NULL_OBJECT->load(inputFilename.c_str());
	EXPECT_EQ(3, image->getNChannels()) << "gray image does not have 1 channel";

	EXPECT_EQ(3, num_channels<boost::gil::rgb8_view_t>::value);
	OpenCVImage * imageOut = image->copy();
	GILOperation::fltkSobelX(image, imageOut);
	rgb8_view_t view = image->make_rgb8_view_t();
	int fistByte = view.row_begin(0)[0][0];
	EXPECT_EQ(191, fistByte);
	EXPECT_EQ(image->getHeight(), imageOut->getHeight());
	EXPECT_EQ(image->getWidth(), imageOut->getWidth());
	EXPECT_EQ(image->getNChannels(), imageOut->getNChannels());
	delete imageOut;
	delete image;
}

TEST(GILOperation, xSobelImageGrayGif) {
	string inputFilename = testImageDir + "spot1Noise10.gif";
	OpenCVImage * image = OpenCVImage::NULL_OBJECT->load(inputFilename.c_str());
	ASSERT_EQ(NULL, image) << "OpenCV does not open gif";
//	EXPECT_EQ(1, image->getNChannels()) << "gray image does not have 1 channel";
}

TEST(GILOperation, xSobelImageGrayPng) {
	string inputFilename = testImageDir + "spot1Noise10.png";
	OpenCVImage * image = OpenCVImage::NULL_OBJECT->load(inputFilename.c_str());
	EXPECT_EQ(3, image->getNChannels()) << "gray image does not have 1 channel";
	OpenCVImage * imageOut = image->copy();
	GILOperation::fltkSobelX(image, imageOut);
	delete imageOut;
}

}
