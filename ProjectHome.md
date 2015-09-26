# ![http://shapelogic.googlecode.com/svn/wiki/shapelogicsmalltransparent.png](http://shapelogic.googlecode.com/svn/wiki/shapelogicsmalltransparent.png) ShapeLogic C++ #

ShapeLogic C++ is an open source toolkit for declarative programming, image processing and computer vision. Optimized for simplicity of programming. Started September 2008.

The first real application for ShapeLogic Java is a [particle analyzer](http://www.shapelogic.org/particle.html). It will find and categorize particles on a relatively uniform background then make a report of geometric properties for each of the particles. The main application is for recognizing cells in medical image processing.

Join the ShapeLogic [mailing list](http://groups.google.com/group/shapelogic) for announcements, questions, bug reports, suggestions and feature requests.

## Main ideas and motivation for ShapeLogic ##
ShapeLogic is a library for
  * [Declarative programming](http://www.shapelogic.org/general-declarative.html) and lazy computations in C++
  * Image processing and computer vision
  * [Particle analyzer](http://www.shapelogic.org/particle.html) for medical image processing
While ShapeLogic's declarative programming system was initially developed
for image processing and computer vision, it is widely applicable.
It is currently difficult to combine declarative programming and image processing.
ShapeLogic is intended as basic plumbing software that turns a logic engine
into a simple plugin component to ease entry into vision and image
analysis. ShapeLogic also fills gaps missing from current Java image
processing libraries, and uses a commercially friendly license.

ShapeLogic has an automatic color [particle counter and analyzer](http://www.shapelogic.org/particle.html) and a [letter matching example](http://www.shapelogic.org/letter-match.html).

## Features ##
  * It is free (as in free speech and free beer)
  * Commercially friendly MIT open source license
  * Programmed in C++

![http://shapelogic-cpp.googlecode.com/svn/images/shapelogic-cpp-windows.jpg](http://shapelogic-cpp.googlecode.com/svn/images/shapelogic-cpp-windows.jpg)

ShapeLogic C++ under Windows

![http://shapelogic-cpp.googlecode.com/svn/images/shapelogic-cpp-linux.jpg](http://shapelogic-cpp.googlecode.com/svn/images/shapelogic-cpp-linux.jpg)

ShapeLogic C++ under Linux

## Getting Started links ##

[ShapeLogic project home page](http://www.shapelogic.org) is the main source of information.

A Getting Started page for ShapeLogic C++ will be put up when there are working code.

## Requirements ##
For running as a library for functional and declarative programming there are no requirements.

For running as a ImageJ plugin ShapeLogic uses the following libraries:
  * [Boost](http://www.boost.org) the C++ library
  * [OpenCV](http://opencvlibrary.sourceforge.net) for computer vision algorithms
  * [Generic Image Library](http://opensource.adobe.com/wiki/display/gil/Generic+Image+Library) which is part of Boost as of v 1.35
  * [FLTK, Fast Light Toolkit](http://www.fltk.org/) lightweight cross platform GUI
  * [Google Testing Framework](http://code.google.com/p/googletest/)
  * [Boost.build v2](http://www.boost.org/doc/tools/build/index.html) for command line based build system
  * [Eclipse CDT](http://www.eclipse.org/cdt/) for IDE based build system

## Development Status: Alpha ##
  * ShapeLogic is in Alpha, as of version 0.4
  * Same code runs under both Windows and Linux
  * Contains some image processing algorithms
  * Unit test are setup
  * Builds can be done both with Bjam and Eclipse

## News ##

### 2009/03/22 ShapeLogic C++ 0.5 released ###
  * Added binary thresholds operations
    * Threshold with fixed limit of 127
    * Adaptive threshold with a small block size of 3
  * Added morphological operations
    * Dilate
    * Erode

### 2008/11/14 ShapeLogic C++ 0.4 released ###
  * Images are now internally stored in OpenCV's IplImage format
  * More image formats: BMP, DIB, JPEG, JPG, JPE, PNG, PBM, PGM, PPM, SR, RAS, TIFF, TIF
  * Made a few OpenCV image processing algorithm available:
    * Canny edge detector
    * Flip RB color
    * Flip horizontally
    * Flip vertically
  * Made Boost Build Jamfiles that works both on Windows and other operating systems
  * First release with development status Alpha

### 2008/10/31 ShapeLogic C++ 0.3 released ###

  * Added 3 first brushes: Pen, Sample color, Point info
  * Fixed bugs causing ShapeLogic to crash

### 2008/10/22 ShapeLogic C++ 0.2 released ###

  * Save images using GIL
  * Scroll big images
  * Display file name in window frame

### 2008/10/16 ShapeLogic C++ 0.1 released ###

  * Integrate FLTK, Boost, GIL, Google C++ Testing Frameworks, Boost Build
  * Minimalist GUI to load images and run image processing operations
  * Image processing code written in GIL
  * Tested on Windows and Linux

### 2008/09/03 Start of experimental port from Java to C++ ###

An [experimental port of ShapeLogic to C++](http://www.shapelogic.org/cpp.html) has begun.
The algorithms in ShapeLogic are not using anything too languages specific so they should be portable to similar languages say C++ and C#. The idea with ShapeLogic is that it should be a declarative framework for vision and you should be able to get work done by making rules instead of regular procedural or object oriented programming. For example should be able to make a list of rules for categorizing the shape of a particle in a particle analyzer. You put them in a database or a flat file and the same rules should work for C++ and Java version of ShapeLogic.

## Future plans for ShapeLogic ##

For more up to date information on ongoing development work look at these
  * Blog [Declarative Computer Vision](http://samibadawi.blogspot.com)
  * [Roadmap](http://www.shapelogic.org/roadmap.html)

### ShapeLogic C++ v 0.6 soon to be released ###
  * Make OpenCV more image processing algorithm available in menus
  * Make generic dialog to get parameters for algorithms
  * Improve threshold to have a user input for limit

## Examples applications for ShapeLogic Java ##
  * Automatic color and gray scale [particle counter and analyzer](http://www.shapelogic.org/particle.html), first medical image processing example
  * [Letter matching example](http://www.shapelogic.org/letter-match.html). Very rudimentary OCR.
  * [Mathematical problems](http://www.shapelogic.org/project-euler.html) from [Project Euler](http://projecteuler.net). This is a list of 192 mathematical problems that can be solved by computers. They vary in complexity from simple to hard. The goal is to test ShapeLogic's new declarative and functional constructs on real problems and make sure they are terse and intuitive.

Site last modified 2009-05-14