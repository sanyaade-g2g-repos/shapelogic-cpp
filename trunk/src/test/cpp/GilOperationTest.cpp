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
#include <FL/Fl_JPEG_Image.H>
#include <iostream>

namespace {
using namespace std;
using namespace boost::gil;

TEST(GILOperation, xGradientFile) {
	//There is a problem with using relative path, you can call bjam from either
	//shapelogic-cpp or shapelogic-cpp/src/test, and they will be the current dir
	const char * inputFilename = "/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/embryos6.jpg";
	const char * outputFilename = "/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/embryos6out.jpg";
	GILOperation::xLuminosityGradient(inputFilename, outputFilename);
}


TEST(GILOperation, xGradientImage) {
	const char * inputFilename = "/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/embryos6.jpg";
	Fl_Image * image = new Fl_JPEG_Image(inputFilename);
	EXPECT_EQ(3, image->d());
	EXPECT_EQ(3, num_channels<boost::gil::rgb8_view_t>::value);
	Fl_RGB_Image * rgbImage = dynamic_cast<Fl_RGB_Image *>(image);
	EXPECT_TRUE(rgbImage != NULL);
	rgb8_view_t view = GILOperation::make_rgb8_view_t(image);
	int fistByte = view.row_begin(0)[0][0];
	EXPECT_EQ(191, fistByte);
	Fl_Image * imageOut = image->copy();
	EXPECT_EQ(image->h(), imageOut->h());
	EXPECT_EQ(image->w(), imageOut->w());
	EXPECT_EQ(image->d(), imageOut->d());
	image->uncache();
	imageOut->uncache();
	delete imageOut;
	delete image;
	cerr << "Done with test.\n";
}

}
