/*
 * BoostTest.cpp
 *
 * This file contains test of SLStringUtil
 *
 *  Created on: Oct 22, 2008
 *      Author: Sami Badawi
 */

#include <gtest/gtest.h>
#include <boost/lambda/lambda.hpp>
#include <SLStringUtil.h>

namespace {
using namespace std;
using namespace boost::lambda;

// Test the lambda expression in Boost
TEST(SLStringUtil, dummy) {
	string fileName1 = "image.jpg";
	string fileName2 = "image.tiff";
	string preExtension = "image.";
	string extension = SLStringUtil::fileExtension(fileName1.c_str());
	string expretedJpg = "jpg";
	EXPECT_EQ(expretedJpg, extension);
	EXPECT_TRUE(SLStringUtil::isJpeg(fileName1.c_str()));
	EXPECT_FALSE(SLStringUtil::isJpeg(fileName2.c_str()));
	EXPECT_EQ(preExtension, SLStringUtil::preFileExtension(fileName1.c_str()));

}

TEST(SLStringUtil, toLowerTest) {
	string fileName1 = "IMAGE.JPG";
	string fileName2 = "image.jpg";
	EXPECT_EQ(fileName2, SLStringUtil::toLower(fileName1.c_str()));
}

}
