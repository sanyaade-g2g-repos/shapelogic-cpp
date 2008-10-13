/*
 * GILOperation.cpp
 *
 * Should contain GIL based image processing algorithms.
 *
 *  Created on: Oct 10, 2008
 *      Author: Sami Badawi
 */

#include "GILOperation.h"
#include <FL/Fl_JPEG_Image.H>
#include <iostream>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>


GILOperation::GILOperation() {
}

GILOperation::~GILOperation() {
}

using namespace boost::gil;
using namespace std;

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

template <typename SrcView, typename DstView>
void x_luminosity_gradient(const SrcView& src, const DstView& dst) {
    typedef pixel<typename channel_type<SrcView>::type, gray_layout_t> gray_pixel_t;
    x_gradient_generic(color_converted_view<gray_pixel_t>(src), dst);
}


rgb8_view_t GILOperation::make_rgb8_view_t(Fl_Image * input) {
	rgb8_view_t view = interleaved_view(input->w(),input->h(),(rgb8_view_t::value_type *)(*input->data()),input->w()*3);
	return view;
}

int getFirstByteInImage(rgb8_view_t & view) {
	rgb8_pixel_t* data = view.row_begin(0);
	int number = data[0][0];
	return number;
}

void printFirst(rgb8_view_t & view) {
	cerr << " first byte " << getFirstByteInImage(view) << endl;
}

void GILOperation::fltkGradient(Fl_Image * input, Fl_Image * output) {
	cerr << "Starting x_gradient\n";
	rgb8_view_t inputView = make_rgb8_view_t(input);
	rgb8_view_t outputView = make_rgb8_view_t(output);
	cerr << "Input ";
	printFirst(inputView);
	x_gradient(inputView, outputView);
//	x_gradient8rgb(make_rgb8_view_t(input),make_rgb8_view_t(output));
	cerr << "Output ";
	printFirst(outputView);
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
