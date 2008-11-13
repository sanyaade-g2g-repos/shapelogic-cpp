/*
 * ImageControllerTest.cpp
 *
 * Current version test opening images of different types from different classes.
 *
 *  Created on: Oct 2, 2008
 *      Author: Sami Badawi
 */

#include <FltkImage.h>
#include <ImageController.h>
#include <OpenCVImage.h>
#include <SLFactory.h>

#include <FL/Fl_Image.H>
#include <gtest/gtest.h>

//TODO have a way to find the top directory and give address relative to that
static const char * filename = "./src/test/resources/images/particles/spot1Clean.jpg";

// Tests Open SLImage
TEST(ImageControllerTest, loadSLImageWithImageController) {
    ImageController imageController;
    imageController.open(filename);
    Fl_Image * image = imageController.getCurrentImage();
    ASSERT_NE((void *)NULL, image ) << "File did not open " << filename;
    EXPECT_EQ(30, image->w());
    EXPECT_EQ(30, image->h());
    EXPECT_EQ(3, image->d());
    EXPECT_EQ(92, image->ld()); //4 byte aligned under OpenCV not under FLTK
}

// Tests Open SLImage. Disabled since PNG image in FLTK caused linker problems
//TEST(ImageControllerTest, loadSLImageWithSLFactory) {
//	SLFactory sLFactory;
//	sLFactory.setImageType("FLTK");
//	SLImage * slImage = sLFactory.makeSLImage(filename);
//    Fl_Image * image = slImage->getFlImage();
//    ASSERT_NE((void *)NULL, image ) << "File did not open " << filename;
//    EXPECT_EQ(30, image->w());
//    EXPECT_EQ(30, image->h());
//    EXPECT_EQ(3, image->d());
//    EXPECT_EQ(0, image->ld()); //4 byte aligned under OpenCV not under FLTK
//}

// Tests load OpenCVImage
TEST(ImageControllerTest, loadOpenCVImage) {
	OpenCVImage * openCVImage = OpenCVImage::NULL_OBJECT->load(filename);
    ASSERT_NE((void *)NULL, openCVImage ) << "File did not open " << filename;
    Fl_Image * image = openCVImage->getFlImage();
    ASSERT_NE((void *)NULL, image ) << "File did not open " << filename;
    EXPECT_EQ(30, image->w());
    EXPECT_EQ(30, image->h());
    EXPECT_EQ(3, image->d());
    EXPECT_EQ(92, image->ld()); //4 byte aligned under OpenCV not under FLTK
    EXPECT_EQ(8, openCVImage->getDepth());
    EXPECT_EQ(92, openCVImage->getWidthStep());
}

// Tests load FltkImage. Disabled since PNG image in FLTK caused linker problems
//TEST(ImageControllerTest, loadFltkImage) {
//	FltkImage * fltkImage = FltkImage::NULL_OBJECT->load(filename);
//    ASSERT_NE((void *)NULL, fltkImage ) << "File did not open " << filename;
//    Fl_Image * image = fltkImage->getFlImage();
//    ASSERT_NE((void *)NULL, image ) << "File did not open " << filename;
//    EXPECT_EQ(30, image->w());
//    EXPECT_EQ(30, image->h());
//    EXPECT_EQ(3, image->d());
//    EXPECT_EQ(0, image->ld()); //4 byte aligned under OpenCV not under FLTK
//    EXPECT_EQ(8, fltkImage->getDepth());
//    EXPECT_EQ(90, fltkImage->getWidthStep());
//}
