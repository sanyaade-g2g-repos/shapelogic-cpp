/*
 * FltkImage.cpp
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#include <ImageController.h>
#include <FL/Fl_Image.H>
#include <gtest/gtest.h>


// Tests Open SLImage
TEST(ImageControllerTest, OpenSLImage) {
    ImageController imageController;
    const char * filename = "/home/sbadawi/shapelogic-cpp/src/test/resources/images/particles/spot1Clean.jpg";
    imageController.open(filename);
    Fl_Image * image = imageController.getCurrentImage();
    ASSERT_NE((void *)NULL, image ) << "File did not open " << filename;
    EXPECT_EQ(30, image->w());
    EXPECT_EQ(30, image->h());
    EXPECT_EQ(3, image->d());
    EXPECT_EQ(90, image->ld());
}
