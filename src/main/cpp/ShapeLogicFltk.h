/*
 * shapelogic-cpp.cxx
 *
 *  Created on: Sep 17, 2008
 *      Author: Sami Badawi
 */

// generated by Fast Light User Interface Designer (fluid) version 1.0107

#ifndef ShapeLogicFltk_h
#define ShapeLogicFltk_h
#include <FL/Fl.H>
#include <string>
#include "ImageController.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Scroll.H>
#include "ImageBox.h"

class ShapeLogicFltk {
public:
  ShapeLogicFltk();
  Fl_Double_Window *_window;
  static Fl_Menu_Item menu_[];
private:
  void cb_Open_i(Fl_Menu_*, void*);
  static void cb_Open(Fl_Menu_*, void*);
  void cb_Save_i(Fl_Menu_*, void*);
  static void cb_Save(Fl_Menu_*, void*);
  void cb_Save1_i(Fl_Menu_*, void*);
  static void cb_Save1(Fl_Menu_*, void*);
  void cb_Quit_i(Fl_Menu_*, void*);
  static void cb_Quit(Fl_Menu_*, void*);
  void cb_Undo_i(Fl_Menu_*, void*);
  static void cb_Undo(Fl_Menu_*, void*);
  void cb_Clear_i(Fl_Menu_*, void*);
  static void cb_Clear(Fl_Menu_*, void*);
  void cb_Fill_i(Fl_Menu_*, void*);
  static void cb_Fill(Fl_Menu_*, void*);
  void cb_Invert_i(Fl_Menu_*, void*);
  static void cb_Invert(Fl_Menu_*, void*);
  void cb_Gray8_i(Fl_Menu_*, void*);
  static void cb_Gray8(Fl_Menu_*, void*);
  void cb_RGB8_i(Fl_Menu_*, void*);
  static void cb_RGB8(Fl_Menu_*, void*);
  void cb_Threshold_i(Fl_Menu_*, void*);
  static void cb_Threshold(Fl_Menu_*, void*);
  void cb_Foreground_i(Fl_Menu_*, void*);
  static void cb_Foreground(Fl_Menu_*, void*);
  void cb_Background_i(Fl_Menu_*, void*);
  static void cb_Background(Fl_Menu_*, void*);
  void cb_Swap_RB_i(Fl_Menu_*, void*);
  static void cb_Swap_RB(Fl_Menu_*, void*);
  void cb_Flip_Horizontally_i(Fl_Menu_*, void*);
  static void cb_Flip_Horizontally(Fl_Menu_*, void*);
  void cb_Flip_Vertically_i(Fl_Menu_*, void*);
  static void cb_Flip_Vertically(Fl_Menu_*, void*);
  void cb_None_i(Fl_Menu_*, void*);
  static void cb_None(Fl_Menu_*, void*);
  void cb_Pen_i(Fl_Menu_*, void*);
  static void cb_Pen(Fl_Menu_*, void*);
  void cb_Point_info_i(Fl_Menu_*, void*);
  static void cb_Point_info(Fl_Menu_*, void*);
  void cb_Sample_color_i(Fl_Menu_*, void*);
  static void cb_Sample_color(Fl_Menu_*, void*);
  void cb_Dilate_i(Fl_Menu_*, void*);
  static void cb_Dilate(Fl_Menu_*, void*);
  void cb_Erode_i(Fl_Menu_*, void*);
  static void cb_Erode(Fl_Menu_*, void*);
  void cb_Smooth_i(Fl_Menu_*, void*);
  static void cb_Smooth(Fl_Menu_*, void*);
  void cb_Signed_Gradient_i(Fl_Menu_*, void*);
  static void cb_Signed_Gradient(Fl_Menu_*, void*);
  void cb_Sobel_X_i(Fl_Menu_*, void*);
  static void cb_Sobel_X(Fl_Menu_*, void*);
  void cb_Sobel_Y_i(Fl_Menu_*, void*);
  static void cb_Sobel_Y(Fl_Menu_*, void*);
  void cb_Sobel_XY_i(Fl_Menu_*, void*);
  static void cb_Sobel_XY(Fl_Menu_*, void*);
  void cb_Canny_Edge_i(Fl_Menu_*, void*);
  static void cb_Canny_Edge(Fl_Menu_*, void*);
  void cb_About_i(Fl_Menu_*, void*);
  static void cb_About(Fl_Menu_*, void*);
public:
  Fl_Scroll *_imageScroll;
  ImageBox *_imageBox;
  void imageSetup(const char* command, const char* arg);
  void updateLabel();
  ImageController * getImageController();
};
int main_proxy(int argc, char **argv);
#endif
