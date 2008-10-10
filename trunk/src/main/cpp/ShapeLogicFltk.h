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
#include <FL/Fl_Group.H>

class ShapeLogicFltk {
public:
  ShapeLogicFltk();
  Fl_Double_Window *_window;
  static Fl_Menu_Item menu_[];
private:
  void cb_Open_i(Fl_Menu_*, void*);
  static void cb_Open(Fl_Menu_*, void*);
  void cb_Undo_i(Fl_Menu_*, void*);
  static void cb_Undo(Fl_Menu_*, void*);
  void cb_Clear_i(Fl_Menu_*, void*);
  static void cb_Clear(Fl_Menu_*, void*);
  void cb_Fill_i(Fl_Menu_*, void*);
  static void cb_Fill(Fl_Menu_*, void*);
  void cb_Invert_i(Fl_Menu_*, void*);
  static void cb_Invert(Fl_Menu_*, void*);
  void cb_Foreground_i(Fl_Menu_*, void*);
  static void cb_Foreground(Fl_Menu_*, void*);
  void cb_Background_i(Fl_Menu_*, void*);
  static void cb_Background(Fl_Menu_*, void*);
public:
  Fl_Group *_imageGroup;
private:
  ImageController _imageController;
public:
  void imageSetup(const char* command, const char* arg);
};
int main_proxy(int argc, char **argv);
#endif