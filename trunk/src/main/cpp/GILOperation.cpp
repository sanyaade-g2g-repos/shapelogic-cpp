/*
 * GILOperation.cpp
 *
 * Should contain GIL based image processing algorithms.
 *
 *  Created on: Oct 10, 2008
 *      Author: Sami Badawi
 */

#include "GILOperation.h"
#include "SLStringUtil.h"
#include <FL/Fl_JPEG_Image.H>
#include <iostream>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
//#include <boost/gil/extension/io/tiff_dynamic_io.hpp>
//#include <boost/gil/extension/io/tiff_io.hpp>

using namespace boost::gil;
using namespace std;

//-----------------------Helper functions-----------------------------

rgb8_view_t GILOperation::make_rgb8_view_t(Fl_Image * input) {
	rgb8_view_t view = interleaved_view(input->w(), input->h(),
			(rgb8_view_t::value_type *)(*input->data()),input->w()*input->d());
	return view;
}

gray8_view_t make_gray8_view_t(Fl_Image * input) {
	gray8_view_t view = interleaved_view(input->w(), input->h(),
			(gray8_view_t::value_type *)(*input->data()),input->w()*input->d());
	return view;
}

bool isGray8(Fl_Image * input) {
	return input->d() == 1;
}

int getFirstByteInImage(rgb8_view_t & view) {
	rgb8_pixel_t* data = view.row_begin(0);
	int number = data[0][0];
	return number;
}

void printFirst(rgb8_view_t & view) {
	cerr << " first byte " << getFirstByteInImage(view) << endl;
}


//-----------------------x_gradient functions-----------------------------
//x_gradient returns a signed output, that will not be represented right in a normal jpeg image
//TODO example code should be removed

template <typename Out>
struct halfdiff_cast_channels {
    template <typename T> Out operator()(const T& in1, const T& in2) const {
        return Out((in2-in1)/2);
    }
};

template <typename SrcView, typename DstView>
void x_gradient(const SrcView& src, const DstView& dst) {

    int max_x = src.width()-1;
    for (int y=0; y<src.height(); ++y) {
        typename SrcView::x_iterator src_it = src.row_begin(y);
        typename DstView::x_iterator dst_it = dst.row_begin(y);

        for (int x=1; x < max_x; ++x) {
            for (int c=0; c< num_channels<rgb8_view_t>::value; ++c) {
            	dst_it[x][c] = (src_it[x+1][c] - src_it[x-1][c])/2;
            }
        }
    }
}

template <typename SrcView, typename DstView>
void x_gradient_generic(const SrcView& src, const DstView& dst) {
    typedef typename channel_type<DstView>::type dst_channel_t;

    for (int y=0; y<src.height(); ++y) {
        typename SrcView::x_iterator src_it = src.row_begin(y);
        typename DstView::x_iterator dst_it = dst.row_begin(y);

        for (int x=1; x<src.width()-1; ++x) {
            static_transform(src_it[x-1], src_it[x+1], dst_it[x],
                             halfdiff_cast_channels<dst_channel_t>());
        }
    }
}

void GILOperation::fltkGradient(Fl_Image * input, Fl_Image * output) {
	x_gradient(make_rgb8_view_t(input),make_rgb8_view_t(output));
}

//-----------------------x_luminosity_gradient functions-----------------------------
//TODO example code should be removed

template <typename SrcView, typename DstView>
void x_luminosity_gradient(const SrcView& src, const DstView& dst) {
    typedef pixel<typename channel_type<SrcView>::type, gray_layout_t> gray_pixel_t;
    x_gradient_generic(color_converted_view<gray_pixel_t>(src), dst);
}

void GILOperation::xLuminosityGradient(const char * inputFile, const char * outputFile) {
    rgb8_image_t img;
    jpeg_read_image(inputFile,img);

    gray8s_image_t img_out(img.dimensions());
    fill_pixels(view(img_out),bits8s(0));

    x_luminosity_gradient(const_view(img), view(img_out));
    if (outputFile != NULL)
    	jpeg_write_view(outputFile,color_converted_view<gray8_pixel_t>(const_view(img_out)));
}

//-----------------------sobel_x functions-----------------------------

template <typename SrcView, typename DstView>
void sobel_x(const SrcView& src, const DstView& dst) {
    typedef typename channel_type<DstView>::type dst_channel_t;

    int max_x = src.width()-1;
    for (int y=0; y<src.height(); ++y) {
        typename SrcView::x_iterator src_it = src.row_begin(y);
        typename DstView::x_iterator dst_it = dst.row_begin(y);

        for (int x=1; x < max_x; ++x) {
            for (int c=0; c< num_channels<rgb8_view_t>::value; ++c) {
            	dst_channel_t srcPlus1 = src_it[x+1][c];
            	dst_channel_t srcMinus1 = src_it[x-1][c];
            	dst_it[x][c] = (srcPlus1 > srcMinus1) ?
            			srcPlus1 - srcMinus1 :
						srcMinus1 - srcPlus1;
            }
        }
    }
}

void GILOperation::fltkSobelX(Fl_Image * input, Fl_Image * output) {
	if (isGray8(input))
		sobel_x(make_gray8_view_t(input),make_gray8_view_t(output));
	else
		sobel_x(make_rgb8_view_t(input),make_rgb8_view_t(output));
}

//-----------------------sobel_y functions-----------------------------

template <typename SrcView, typename DstView>
void sobel_y(const SrcView& src, const DstView& dst) {
    typedef typename channel_type<DstView>::type dst_channel_t;

    int max_x = src.width();
    int width = src.width();
    for (int y=1; y<src.height()-1; ++y) {
        typename SrcView::x_iterator src_it = src.row_begin(y);
        typename DstView::x_iterator dst_it = dst.row_begin(y);

        for (int x=0; x < max_x; ++x) {
            for (int c=0; c< num_channels<rgb8_view_t>::value; ++c) {
            	dst_channel_t srcPlus1 = src_it[x+width][c]; //TODO should be replaced by line length
            	dst_channel_t srcMinus1 = src_it[x-width][c];
            	dst_it[x][c] = (srcPlus1 > srcMinus1) ?
            			srcPlus1 - srcMinus1 :
						srcMinus1 - srcPlus1;
            }
        }
    }
}

void GILOperation::fltkSobelY(Fl_Image * input, Fl_Image * output) {
	sobel_y(make_rgb8_view_t(input),make_rgb8_view_t(output));
}

//-----------------------sobel_xy functions-----------------------------

template <typename SrcView, typename DstView>
void sobel_xy(const SrcView& src, const DstView& dst) {
    typedef typename channel_type<DstView>::type dst_channel_t;

    int max_x = src.width() - 1;
    int width = src.width();
    for (int y=1; y<src.height()-1; ++y) {
        typename SrcView::x_iterator src_it = src.row_begin(y);
        typename DstView::x_iterator dst_it = dst.row_begin(y);

        for (int x=1; x < max_x; ++x) {
            for (int c=0; c< num_channels<rgb8_view_t>::value; ++c) {
            	dst_channel_t srcPlus1 = src_it[x+width][c]; //TODO should be replaced by line length
            	dst_channel_t srcMinus1 = src_it[x-width][c];
            	dst_channel_t sobelY = (srcPlus1 > srcMinus1) ?
            			srcPlus1 - srcMinus1 :
						srcMinus1 - srcPlus1;
            	srcPlus1 = src_it[x+1][c];
            	srcMinus1 = src_it[x-1][c];
            	dst_channel_t sobelX = (srcPlus1 > srcMinus1) ?
            			srcPlus1 - srcMinus1 :
						srcMinus1 - srcPlus1;
            	dst_it[x][c] = max(sobelX, sobelY);
            }
        }
    }
}

void GILOperation::fltkSobelXY(Fl_Image * input, Fl_Image * output) {
	sobel_y(make_rgb8_view_t(input),make_rgb8_view_t(output));
}

//-----------------------blur functions-----------------------------

template <typename SrcView, typename DstView>
void blur(const SrcView& src, const DstView& dst) {
    typedef typename channel_type<DstView>::type dst_channel_t;

    int max_x = src.width() - 1;
    int width = src.width();
    for (int y=1; y<src.height()-1; ++y) {
        typename SrcView::x_iterator src_it = src.row_begin(y);
        typename DstView::x_iterator dst_it = dst.row_begin(y);

        for (int x=1; x < max_x; ++x) {
            for (int c=0; c< num_channels<rgb8_view_t>::value; ++c) {
            	dst_it[x][c] =
            		src_it[x-1-width][c] / 16 +
            		src_it[x-width][c] / 8 +
            		src_it[x-1-width][c] / 16 +

            		src_it[x-1][c] / 8 +
            		src_it[x][c] / 4 +
            		src_it[x-1][c] / 8 +

            		src_it[x-1+width][c] / 16 +
            		src_it[x+width][c] / 8 +
            		src_it[x-1+width][c] / 16;
            }
        }
    }
}

void GILOperation::fltkBlur(Fl_Image * input, Fl_Image * output) {
	blur(make_rgb8_view_t(input),make_rgb8_view_t(output));
}

//-----------------------save jpg-----------------------------

void GILOperation::saveJpg(const char * filename, Fl_Image * input) {
	jpeg_write_view(filename, make_rgb8_view_t(input));
}

void GILOperation::saveAnyImage(const char * filename, Fl_Image * input) {

	if (SLStringUtil::isJpeg(filename)) jpeg_write_view(filename, make_rgb8_view_t(input));
	else if (SLStringUtil::isPng(filename)) png_write_view(filename, make_rgb8_view_t(input));
//	else if (SLStringUtil::isTiff(filename)) tiff_write_view(filename, make_rgb8_view_t(input));
}
