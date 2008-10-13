/*
 * shapelogic-cpp.cxx
 *
 *  Created on: Sep 17, 2008
 *      Author: Sami Badawi
 */

// generated by Fast Light User Interface Designer (fluid) version 1.0107

#include "ShapeLogicFltk.h"
#include <iostream>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_JPEG_Image.H>
#include "FltkUtil.h"
#include "shapelogic-cpp.h"
#include <FL/Fl_Color_Chooser.H>

void ShapeLogicFltk::cb_Open_i(Fl_Menu_*, void*) {
  const char * filename = FltkUtil::singleFileDialog();
imageSetup("Open", filename);
}
void ShapeLogicFltk::cb_Open(Fl_Menu_* o, void* v) {
  ((ShapeLogicFltk*)(o->parent()->user_data()))->cb_Open_i(o,v);
}

void ShapeLogicFltk::cb_Undo_i(Fl_Menu_*, void*) {
  imageSetup("Undo", NULL);
}
void ShapeLogicFltk::cb_Undo(Fl_Menu_* o, void* v) {
  ((ShapeLogicFltk*)(o->parent()->user_data()))->cb_Undo_i(o,v);
}

void ShapeLogicFltk::cb_Clear_i(Fl_Menu_*, void*) {
  imageSetup("Clear", NULL);
}
void ShapeLogicFltk::cb_Clear(Fl_Menu_* o, void* v) {
  ((ShapeLogicFltk*)(o->parent()->user_data()))->cb_Clear_i(o,v);
}

void ShapeLogicFltk::cb_Fill_i(Fl_Menu_*, void*) {
  imageSetup("Fill", NULL);
}
void ShapeLogicFltk::cb_Fill(Fl_Menu_* o, void* v) {
  ((ShapeLogicFltk*)(o->parent()->user_data()))->cb_Fill_i(o,v);
}

void ShapeLogicFltk::cb_Invert_i(Fl_Menu_*, void*) {
  imageSetup("Invert", NULL);
}
void ShapeLogicFltk::cb_Invert(Fl_Menu_* o, void* v) {
  ((ShapeLogicFltk*)(o->parent()->user_data()))->cb_Invert_i(o,v);
}

void ShapeLogicFltk::cb_Foreground_i(Fl_Menu_*, void*) {
  unsigned char * foreground = _imageController._foreground;
  fl_color_chooser("Chose foreground color", foreground[0], foreground[1], foreground[2]);
}
void ShapeLogicFltk::cb_Foreground(Fl_Menu_* o, void* v) {
  ((ShapeLogicFltk*)(o->parent()->user_data()))->cb_Foreground_i(o,v);
}

void ShapeLogicFltk::cb_Background_i(Fl_Menu_*, void*) {
  unsigned char * background = _imageController._background;
  fl_color_chooser("Chose foreground color", background[0], background[1], background[2]);
}
void ShapeLogicFltk::cb_Background(Fl_Menu_* o, void* v) {
  ((ShapeLogicFltk*)(o->parent()->user_data()))->cb_Background_i(o,v);
}

void ShapeLogicFltk::cb_Edge_i(Fl_Menu_*, void*) {
  imageSetup("Edge", NULL);
}
void ShapeLogicFltk::cb_Edge(Fl_Menu_* o, void* v) {
  ((ShapeLogicFltk*)(o->parent()->user_data()))->cb_Edge_i(o,v);
}

Fl_Menu_Item ShapeLogicFltk::menu_[] = {
 {"File", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Open...", 0x4006f,  (Fl_Callback*)ShapeLogicFltk::cb_Open, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Save", 0x40073,  0, 0, 128, FL_NORMAL_LABEL, 0, 14, 0},
 {"Quit", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Edit", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Undo", 0x4007a,  (Fl_Callback*)ShapeLogicFltk::cb_Undo, 0, 128, FL_NORMAL_LABEL, 0, 14, 0},
 {"Clear", 0,  (Fl_Callback*)ShapeLogicFltk::cb_Clear, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Fill", 0,  (Fl_Callback*)ShapeLogicFltk::cb_Fill, 0, 128, FL_NORMAL_LABEL, 0, 14, 0},
 {"Invert", 0x50069,  (Fl_Callback*)ShapeLogicFltk::cb_Invert, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Image", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Type", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"8-bit", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"16-bit", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"RGB Color", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Color", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Foreground", 0,  (Fl_Callback*)ShapeLogicFltk::cb_Foreground, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Background", 0,  (Fl_Callback*)ShapeLogicFltk::cb_Background, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0},
 {"Process", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Smooth", 0x50073,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Sharpen", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Edge", 0,  (Fl_Callback*)ShapeLogicFltk::cb_Edge, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Plugins", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"ShapeLogic", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"ShapeLogicOld", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0},
 {"Help", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"About ShapeLogic", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

ShapeLogicFltk::ShapeLogicFltk() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = _window = new Fl_Double_Window(730, 600, "ShapeLogic fltk v 0.1");
    w = o;
    o->user_data((void*)(this));
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 730, 20);
      o->menu(menu_);
    }
    { Fl_Group* o = _imageGroup = new Fl_Group(0, 20, 730, 580);
      _imageGroup->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
      o->end();
      Fl_Group::current()->resizable(o);
    }
    o->end();
  }
  w->show();
}

void ShapeLogicFltk::imageSetup(const char* command, const char* arg) {
  _imageController.run(command, arg);
  _imageController.getCurrentImage()->uncache();
  _imageGroup->image(_imageController.getCurrentImage());
  _window->redraw();
}

int main_proxy(int argc, char **argv) {
  ShapeLogicFltk shapeLogicFltk;
return Fl::run();
}
