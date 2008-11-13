====================
ShapeLogic C++ v 0.4
====================

This is the first apha release. This is not an adequate description of how
to build ShapeLogic C++, but just a few pointers.
See project site for more information: http://www.shapelogic.org/cpp.html

ShapeLogic C++ v 0.4 only has a limited number of image processing algorithms 
and brushes. The main function is to show how the different components of 
ShapeLogic C++ work together. Drawing is slow, and only have a pen size of 1.

Main components:
* Boost the C++ library
* OpenCV for reading and writing and a long list of existing computer vision algorithms
* Generic Image Library for writing new image processing code
* FLTK, Fast Light Toolkit lightweight cross platform GUI
* Google Testing Framework
* Boost.build v2 for command line based build system

Make sure that they are available on your system.

Future plans:
* Wiring up a long list of existing computer vision algorithms in OpenCV
* Dialog box class for setting parameters
* Selection of ROI
* Macros
* Faster draw
* More pen sizes

-------------------------------------------------------------------------------
Build under UNIX, Linux, possibly OS X
-------------------------------------------------------------------------------

ShapeLogic C++ can be build from command line:

cd shapelogic-cpp
bjam

This will both build ShapeLogic and run the unit tests.

ShapeLogic C++ can be build from Eclipse CDE:
There is a project file coming with the project

For more information see http://www.shapelogic.org/cpp-setup-linux.html

-------------------------------------------------------------------------------
Build under Windows
-------------------------------------------------------------------------------

It has been built using MSVC Express.

Start by compiling FLTK. This worked with the MSVC version 2005 project file.

Rename the Jamfile.msvc and Jamroot.msvc to Jamfile and Jamroot.
 
Then from a command line run:

cd shapelogic-cpp
bjam

This will build ShapeLogic but will not run the unit tests.

For more information see http://www.shapelogic.org/cpp-setup-windows.html
