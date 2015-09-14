/****************************************************************************
 *
 * $Id: vpDisplay.cpp,v 1.28 2008-02-01 15:11:39 fspindle Exp $
 *
 * Copyright (C) 1998-2006 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit.
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE included in the packaging of this file.
 *
 * Licensees holding valid ViSP Professional Edition licenses may
 * use this file in accordance with the ViSP Commercial License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact visp@irisa.fr if any conditions of this licensing are
 * not clear to you.
 *
 * Description:
 * Image display.
 *
 * Authors:
 * Eric Marchand
 *
 *****************************************************************************/

#include <visp/vpDisplay.h>
#include <visp/vpDisplayException.h>

#include <visp/vpPoint.h>
#include <visp/vpMeterPixelConversion.h>
#include <visp/vpMath.h>


/*!
  \file vpDisplay.cpp
  \brief  generic class for image display

  Sample code :
  \code

    #include <visp/vpDebug.h>
    #include <visp/vpConfig.h>

    #include <visp/vpImage.h>
    #include <visp/vpImageIo.h>
    #include <visp/vpDisplayX.h>
    #include <visp/vpDisplayGTK.h>
    #include <visp/vpDisplayGDI.h>
    #include <visp/vpDisplayD3D.h>

    vpImage<vpRGBa> Ic; // A color image

    //Read an image on a disk
    vpImageIo::readPPM(Ic, "image.ppm");


    #if defined VISP_HAVE_GTK
      vpDisplayGTK display;
    #elif defined VISP_HAVE_X11
      vpDisplayX display;
    #elif defined VISP_HAVE_GDI
      vpDisplayGDI display;
    #elif defined VISP_HAVE_D3D
      vpDisplayD3D display;
    #endif

    // We open a window using either X11 or GTK or GDI.
    // Its size is automatically defined by the image (I) size
    display.init(I, 100, 100,"Display...") ;

    // Display the image
    // The image class has a member that specify a pointer toward
    // the display that has been initialized in the display declaration
    // therefore is is no longuer necessary to make a reference to the
    // display variable.
    vpDisplay::display(I) ;

    // Display in overlay a red cross at position 10,10 in the
    // image. The lines are 10 pixels long
    vpDisplay::displayCross(I, 100,10, 20, vpColor::red) ;
    // ...

    // The display is flushed; without this line, nothing will appear in
    // the display.
    vpDisplay::flush(I) ;

  \endcode

*/

vpDisplay::vpDisplay()
{
  title = NULL ;
  displayHasBeenInitialized = false ;
}

/*!
  Display the windows title.
*/
void
vpDisplay::displayTitle ( const vpImage<unsigned char> &I,
                          const char *windowtitle )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->flushTitle ( windowtitle ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  Display a 8bits image in the display window
*/
void
vpDisplay::display ( const vpImage<unsigned char> &I )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayImage ( I ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  \brief get the window pixmap and put it in vpRGBa image
*/
void
vpDisplay::getImage ( const vpImage<unsigned  char> &Isrc,
                      vpImage<vpRGBa> &Idest )
{

  try
  {
    if ( Isrc.display != NULL )
    {
      ( Isrc.display )->getImage ( Idest ) ;
    }
    else
    {
      vpERROR_TRACE ( "Display not initialized" ) ;
      throw ( vpDisplayException ( vpDisplayException::notInitializedError,
                                   "Display not initialized" ) ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  Display a point at coordinates (i,j) in the display window
*/
void vpDisplay::displayPoint ( const vpImage<unsigned char> &I,
                               int i, int j,
                               vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayPoint ( i,j,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }

}
/*!
  Display a cross at coordinates (i,j) in the display window
*/
void vpDisplay::displayCross ( const vpImage<unsigned char> &I,
                               int i, int j,
                               unsigned int size,vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCross ( i,j,size,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*!
  Display a large cross at coordinates (i,j) in the display window
*/
void
vpDisplay::displayCrossLarge ( const vpImage<unsigned char> &I,
                               int i, int j,
                               unsigned int size,vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCrossLarge ( i,j,size,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  Display a circle at coordinates (i,j) in the display window.
  circle radius is given in pixel by paramter r
*/
void
vpDisplay::displayCircle ( const vpImage<unsigned char> &I,
                           int i, int j, unsigned int r,
                           vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCircle ( i,j,r,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*!
  Display a line from coordinates (i1,j1) to (i2,j2) in the display window.
*/
void vpDisplay::displayLine ( const vpImage<unsigned char> &I,
                              int i1, int j1, int i2, int j2,
                              vpColor::vpColorType col, unsigned int e )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayLine ( i1,j1,i2,j2,col,e ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}


/*!  Display a dotted line from coordinates (i1,j1) to (i2,j2) in the display
  window.  circle radius is given in pixel by paramter r
*/
void vpDisplay::displayDotLine ( const vpImage<unsigned char> &I,
                                 int i1, int j1, int i2, int j2,
                                 vpColor::vpColorType col, unsigned int e2 )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayDotLine ( i1,j1,i2,j2,col,e2 ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

void
vpDisplay::displayFrame ( const vpImage<unsigned char> &I,
                          const vpHomogeneousMatrix &cMo,
                          const vpCameraParameters &cam,
                          double size, vpColor::vpColorType col)
{
  // used by display
  vpPoint o; o.setWorldCoordinates ( 0.0,0.0,0.0 ) ;
  vpPoint x; x.setWorldCoordinates ( size,0.0,0.0 ) ;
  vpPoint y; y.setWorldCoordinates ( 0.0,size,0.0 ) ;
  vpPoint z; z.setWorldCoordinates ( 0.0,0.0,size ) ;

  o.track ( cMo ) ;
  x.track ( cMo ) ;
  y.track ( cMo ) ;
  z.track ( cMo ) ;

  double ox=0, oy=0, x1=0, y1=0 ;

  if ( col == vpColor::none )
  {
    vpMeterPixelConversion::convertPoint ( cam,o.p[0],o.p[1],ox,oy) ;

    vpMeterPixelConversion::convertPoint ( cam,x.p[0],x.p[1],x1,y1) ;
    vpDisplay::displayArrow ( I,
                              vpMath::round ( oy ), vpMath::round ( ox ),
                              vpMath::round ( y1 ), vpMath::round ( x1 ),
                              vpColor::green ) ;

    vpMeterPixelConversion::convertPoint ( cam,y.p[0],y.p[1],x1,y1) ;
    vpDisplay::displayArrow ( I,
                              vpMath::round ( oy ), vpMath::round ( ox ),
                              vpMath::round ( y1 ), vpMath::round ( x1 ),
                              vpColor::blue ) ;

    vpMeterPixelConversion::convertPoint ( cam,z.p[0],z.p[1],x1,y1) ;
    vpDisplay::displayArrow ( I,
                              vpMath::round ( oy ), vpMath::round ( ox ),
                              vpMath::round ( y1 ), vpMath::round ( x1 ),
                              vpColor::red ) ;
  }
  else
  {
    vpMeterPixelConversion::convertPoint ( cam,o.p[0],o.p[1],ox,oy) ;

    vpMeterPixelConversion::convertPoint ( cam,x.p[0],x.p[1],x1,y1) ;
    vpDisplay::displayArrow ( I,
                              vpMath::round ( oy ), vpMath::round ( ox ),
                              vpMath::round ( y1 ), vpMath::round ( x1 ),
                              col ) ;

    vpMeterPixelConversion::convertPoint ( cam,y.p[0],y.p[1],x1,y1) ;
    vpDisplay::displayArrow ( I,
                              vpMath::round ( oy ), vpMath::round ( ox ),
                              vpMath::round ( y1 ), vpMath::round ( x1 ),
                              col ) ;

    vpMeterPixelConversion::convertPoint ( cam,z.p[0],z.p[1],x1,y1) ;
    vpDisplay::displayArrow ( I,
                              vpMath::round ( oy ), vpMath::round ( ox ),
                              vpMath::round ( y1 ), vpMath::round ( x1 ),
                              col ) ;
  }
}


/*! Display an arrow from coordinates (i1,j1) to (i2,j2) in the display
  window
*/
void
vpDisplay::displayArrow ( const vpImage<unsigned char> &I,
                          int i1, int j1, int i2, int j2,
                          vpColor::vpColorType col,
                          unsigned int L,unsigned int l )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayArrow ( i1,j1,i2,j2,col,L,l ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!

Display a rectangle in the display window.  The rectangle upper left corner
has coordinates (i,j). The size of the rectangle is fixed by \e width and \e
height.

\param I : Image associated to the display.
\param i : Row number of the rectangle upper corner
\param j : Column number of the rectangle upper corner
\param width : Width of the rectangle.
\param height : Height of the rectangle.
\param col : Color of the rectangle.
\param fill : set as true to fill the rectangle.
\param e : Line thickness

*/
void
vpDisplay::displayRectangle ( const vpImage<unsigned char> &I,
                              int i, int j,
			      unsigned int width, unsigned int height,
                              vpColor::vpColorType col, bool fill,
			                        unsigned int e)
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayRectangle ( i,j,width,height,col, fill, e ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*!

Display a rectangle in the display window.

\param I : Image associated to the display.
\param rect : The rectangle characteristics
\param col  : Color of the rectangle.
\param fill : set as true to fill the rectangle.
\param e : Line thickness
*/
void
vpDisplay::displayRectangle ( const vpImage<unsigned char> &I,
                              const vpRect &rect,
                              vpColor::vpColorType col, bool fill,
			                        unsigned int e )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayRectangle ( rect, col , fill, e ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*! display a string at coordinates (i,j) to (i2,j2) in the display
  window
*/
void
vpDisplay::displayCharString ( const vpImage<unsigned char> &I,
                               int i, int j,char *s,
                               vpColor::vpColorType c )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCharString ( i,j,s,c ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}


/*!
  flushes the output buffer and then waits until all
  requests have been received and processed by the server.

  \warning In vpDisplayX class this function is particular and must be called
  to show the overlay. Because it's time spending, use it parcimoniously.
*/
void vpDisplay::flush ( const vpImage<unsigned char> &I )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->flushDisplay() ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  Close the display attached to I.
*/
void vpDisplay::close ( const vpImage<unsigned char> &I )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->closeDisplay() ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}


/*!
  return true way a button is pressed
*/
bool  vpDisplay::getClick ( const vpImage<unsigned char> &I,
                            unsigned int& i, unsigned int& j, bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick ( i, j, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}

/*!
  return true way button is pressed
*/
bool  vpDisplay::getClick ( const vpImage<unsigned char> &I,
                            unsigned int& i, unsigned int& j,
                            vpMouseButton::vpMouseButtonType& button,
			                      bool blocking)
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick ( i, j, button, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}

/*!
  wait for a click
*/
bool  vpDisplay::getClick ( const vpImage<unsigned char> &I, bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick(blocking) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}


/*!
  return true way  button is released
*/
bool
vpDisplay::getClickUp ( const vpImage<unsigned char> &I,
                        unsigned int& i, unsigned int& j,
                        vpMouseButton::vpMouseButtonType& button,
			                  bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClickUp ( i, j, button, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}


/*!
  Display the windows title.
*/
void
vpDisplay::displayTitle ( const vpImage<vpRGBa> &I, const char *windowtitle )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->flushTitle ( windowtitle ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}


/*!
  Display a 32bits image in the display window
*/
void
vpDisplay::display ( const vpImage<vpRGBa> &I )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayImage ( I ) ;
    }
    else
    {
      vpERROR_TRACE ( "Display not initialized" ) ;
      throw ( vpDisplayException ( vpDisplayException::notInitializedError,
                                   "Display not initialized" ) ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}


/*!
  \brief get the window pixmap and put it in vpRGBa image
*/
void
vpDisplay::getImage ( const vpImage<vpRGBa> &Isrc, vpImage<vpRGBa> &Idest )
{

  try
  {
    if ( Isrc.display != NULL )
    {
      ( Isrc.display )->getImage ( Idest ) ;
    }
    else
    {
      vpERROR_TRACE ( "Display not initialized" ) ;
      throw ( vpDisplayException ( vpDisplayException::notInitializedError,
                                   "Display not initialized" ) ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  Display a point at coordinates (i,j) in the display window
*/


void vpDisplay::displayPoint ( const vpImage<vpRGBa> &I,
                               int i, int j,
                               vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayPoint ( i,j,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }

}
/*!
  Display a cross at coordinates (i,j) in the display window
*/
void vpDisplay::displayCross ( const vpImage<vpRGBa> &I,
                               int i, int j,
                               unsigned int size,vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCross ( i,j,size,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*!
  Display a large cross at coordinates (i,j) in the display window
*/
void
vpDisplay::displayCrossLarge ( const vpImage<vpRGBa> &I,
                               int i, int j,
                               unsigned int size,vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCrossLarge ( i,j,size,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  Display a circle at coordinates (i,j) in the display window.
  circle radius is given in pixel by paramter r
*/
void
vpDisplay::displayCircle ( const vpImage<vpRGBa> &I,
                           int i, int j, unsigned int r,
                           vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCircle ( i,j,r,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*!
  Display a line from coordinates (i1,j1) to (i2,j2) in the display window.
*/
void vpDisplay::displayLine ( const vpImage<vpRGBa> &I,
                              int i1, int j1,
                              int i2, int j2,
                              vpColor::vpColorType col, unsigned int e )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayLine ( i1,j1,i2,j2,col,e ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!  Display a dotted line from coordinates (i1,j1) to (i2,j2) in the display
  window.  circle radius is given in pixel by paramter r
*/
void vpDisplay::displayDotLine ( const vpImage<vpRGBa> &I,
                                 int i1, int j1,
                                 int i2, int j2,
                                 vpColor::vpColorType col, unsigned int e2 )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayDotLine ( i1,j1,i2,j2,col,e2 ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*! Display an arrow from coordinates (i1,j1) to (i2,j2) in the display
  window
*/
void
vpDisplay::displayArrow ( const vpImage<vpRGBa> &I,
                          int i1, int j1, int i2, int j2,
                          vpColor::vpColorType col,
                          unsigned int L,unsigned int l )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayArrow ( i1,j1,i2,j2,col,L,l ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*! display a string at coordinates (i,j) to (i2,j2) in the display
  window
*/
void
vpDisplay::displayCharString ( const vpImage<vpRGBa> &I,
                               int i, int j, char *s,
                               vpColor::vpColorType c )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCharString ( i,j,s,c ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}


/*!
  flushes the output buffer and then waits until all
  requests have been received and processed by the server
*/
void vpDisplay::flush ( const vpImage<vpRGBa> &I )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->flushDisplay() ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  Close the display attached to I.
*/
void vpDisplay::close ( const vpImage<vpRGBa> &I )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->closeDisplay() ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  return true way a button is pressed
*/
bool  vpDisplay::getClick ( const vpImage<vpRGBa> &I,
                            unsigned int& i, unsigned int& j, bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick ( i, j, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}

/*!
  return true way button is pressed
*/
bool  vpDisplay::getClick ( const vpImage<vpRGBa> &I,
                            unsigned int& i, unsigned int& j,
                            vpMouseButton::vpMouseButtonType& button,
			                      bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick ( i, j, button, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}

/*!
  wait for a click
*/
bool  vpDisplay::getClick ( const vpImage<vpRGBa> &I, bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick(blocking) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false;
}



/*!
  return true way  button is released
*/
bool
vpDisplay::getClickUp ( const vpImage<vpRGBa> &I,
                        unsigned int& i, unsigned int& j,
                        vpMouseButton::vpMouseButtonType& button,
			                  bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClickUp ( i, j, button, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}


//--------------
// uv

/*!
  Display a point at coordinates (u,v) in the display window
*/
void vpDisplay::displayPoint_uv ( const vpImage<unsigned char> &I,
                                  int u, int v,
                                  vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayPoint ( v,u,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }

}
/*!
  Display a cross at coordinates (u,v) in the display window
*/
void vpDisplay::displayCross_uv ( const vpImage<unsigned char> &I,
                                  int u, int v,
                                  unsigned int size,vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCross ( v,u,size,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*!
  Display a large cross at coordinates (u,v) in the display window
*/
void
vpDisplay::displayCrossLarge_uv ( const vpImage<unsigned char> &I,
                                  int u, int v,
                                  unsigned int size,vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCrossLarge ( v,u,size,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  Display a circle at coordinates (u,v) in the display window.
  circle radius is given in pixel by paramter r
*/
void
vpDisplay::displayCircle_uv ( const vpImage<unsigned char> &I,
                              int u, int v, unsigned int r,
                              vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCircle ( v,u,r,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*!
  Display a line from coordinates (u1,v1) to (u2,v2) in the display window.
*/
void vpDisplay::displayLine_uv ( const vpImage<unsigned char> &I,
                                 int u1, int v1,
                                 int u2, int v2,
                                 vpColor::vpColorType col, unsigned int e )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayLine ( v1,u1,v2,u2,col,e ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}


/*!  Display a dotted line from coordinates (u1,v1) to (u2,v2) in the display
  window.  circle radius is given in pixel by paramter r
*/
void vpDisplay::displayDotLine_uv ( const vpImage<unsigned char> &I,
                                    int u1, int v1, int u2, int v2,
                                    vpColor::vpColorType col, unsigned int e2 )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayDotLine ( v1,u1,v2,u2,col,e2 ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}


/*! Display an arrow from coordinates (u1,v1) to (u2,v2) in the display
  window
*/
void
vpDisplay::displayArrow_uv ( const vpImage<unsigned char> &I,
                             int u1, int v1, int u2, int v2,
                             vpColor::vpColorType col,
                             unsigned int L,unsigned int l )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayArrow ( v1,u1,v2,u2,col,L,l ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!

Display a rectangle in the display window.  The rectangle upper left corner
has coordinates (u,v). The size of the rectangle is fixed by \e width and \e
height.

\param v Row number of the rectangle upper corner
\param u Column number of the rectangle upper corner
\param width Width of the rectangle.
\param height Height of the rectangle.
\param col Color of the rectangle.
\param fill : set as true to fill the rectangle.
\param e : Line thickness

*/
void
vpDisplay::displayRectangle_uv ( const vpImage<unsigned char> &I,
                                 int u, int v,
                                 unsigned int width, unsigned int height,
                                 vpColor::vpColorType col, bool fill,
				 unsigned int e )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayRectangle ( v,u,width,height,col,fill, e ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*! display a string at coordinates (u,v) in the display
  window
*/
void
vpDisplay::displayCharString_uv ( const vpImage<unsigned char> &I,
                                  int u, int v, char *s,
                                  vpColor::vpColorType c )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCharString ( v,u,s,c ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}


/*!
  return true way a button is pressed
*/
bool  vpDisplay::getClick_uv ( const vpImage<unsigned char> &I,
                               unsigned int& u, unsigned int& v,
			                         bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick ( v, u, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}

/*!
  return true way button is pressed
*/
bool  vpDisplay::getClick_uv ( const vpImage<unsigned char> &I,
                               unsigned int& u, unsigned int& v,
                               vpMouseButton::vpMouseButtonType& button,
			                         bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick ( v, u, button, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}


/*!
  return true way  button is released
*/
bool
vpDisplay::getClickUp_uv ( const vpImage<unsigned char> &I,
                           unsigned int& u, unsigned int& v,
                           vpMouseButton::vpMouseButtonType& button,
			                     bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClickUp ( v, u, button, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}


/*!
  Display a point at coordinates (u,v) in the display window
*/


void vpDisplay::displayPoint_uv ( const vpImage<vpRGBa> &I,
                                  int u, int v,
                                  vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayPoint ( v,u,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }

}
/*!
  Display a cross at coordinates (u,v) in the display window
*/
void vpDisplay::displayCross_uv ( const vpImage<vpRGBa> &I,
                                  int u, int v,
                                  unsigned int size,vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCross ( v,u,size,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*!
  Display a large cross at coordinates (u,v) in the display window
*/
void
vpDisplay::displayCrossLarge_uv ( const vpImage<vpRGBa> &I,
                                  int u, int v,
                                  unsigned int size,vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCrossLarge ( v,u,size,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!
  Display a circle at coordinates (u,v) in the display window.
  circle radius is given in pixel by paramter r
*/
void
vpDisplay::displayCircle_uv ( const vpImage<vpRGBa> &I,
                              int u, int v, unsigned int r,
                              vpColor::vpColorType col )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCircle ( v,u,r,col ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}
/*!
  Display a line from coordinates (u1,v1) to (u2,v2) in the display window.
*/
void vpDisplay::displayLine_uv ( const vpImage<vpRGBa> &I,
                                 int u1, int v1, int u2, int v2,
                                 vpColor::vpColorType col, unsigned int e )
{

  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayLine ( v1,u1,v2,u2,col,e ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*!  Display a dotted line from coordinates  (u1,v1) to (u2,v2) in the display
  window.  circle radius is given in pixel by paramter r
*/
void vpDisplay::displayDotLine_uv ( const vpImage<vpRGBa> &I,
                                    int u1, int v1, int u2, int v2,
                                    vpColor::vpColorType col, unsigned int e2 )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayDotLine ( v1,u1,v2,u2,col,e2 ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*! Display an arrow from coordinates  (u1,v1) to (u2,v2) in the display
  window
*/
void
vpDisplay::displayArrow_uv ( const vpImage<vpRGBa> &I,
                             int u1, int v1, int u2, int v2,
                             vpColor::vpColorType col,
                             unsigned int L,unsigned int l )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayArrow ( v1,u1,v2,u2,col,L,l ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}

/*! display a string at coordinates (u,v) to (i2,j2) in the display
  window
*/
void
vpDisplay::displayCharString_uv ( const vpImage<vpRGBa> &I,
                                  int u, int v, char *s,
                                  vpColor::vpColorType c )
{
  try
  {
    if ( I.display != NULL )
    {
      ( I.display )->displayCharString ( v,u,s,c ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
}



/*!
  return true way a button is pressed
*/
bool  vpDisplay::getClick_uv ( const vpImage<vpRGBa> &I,
                               unsigned int& u, unsigned int& v,
			                         bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick ( v, u, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}

/*!
  return true way button is pressed
*/
bool  vpDisplay::getClick_uv ( const vpImage<vpRGBa> &I,
                               unsigned int& u, unsigned int& v,
                               vpMouseButton::vpMouseButtonType& button,
			                         bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClick ( v, u, button, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}


/*!
  return true way  button is released
*/
bool
vpDisplay::getClickUp_uv ( const vpImage<vpRGBa> &I,
                           unsigned int& u, unsigned int& v,
                           vpMouseButton::vpMouseButtonType& button,
			                     bool blocking )
{
  try
  {
    if ( I.display != NULL )
    {
      return ( I.display )->getClickUp ( v, u, button, blocking ) ;
    }
  }
  catch ( ... )
  {
    vpERROR_TRACE ( "Error caught" ) ;
    throw ;
  }
  return false ;
}