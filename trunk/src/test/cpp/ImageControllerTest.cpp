/*
 * FltkImage.cpp
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#include <ImageController.h>
#include <FL/Fl_Image.H>
#include <gtest/gtest.h>


// Tests factorial of negative numbers.
TEST(ImageControllerTest, Dummy) {
    ImageController imageController;
    const char * filename = "/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/spot1Clean.jpg";
    imageController.open(filename);
    Fl_Image * image = imageController.getCurrentImage();
    EXPECT_NE((void *)NULL, image );
    EXPECT_EQ(30, image->w());
}
