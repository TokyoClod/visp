/****************************************************************************
 *
 * $Id: vpIcCompGrabber.cpp,v 1.11 2007-12-19 08:25:25 fspindle Exp $
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
 * This file is part of the ViSP toolkit
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
 * IcComp (Imaging Technology) framegrabber.
 *
 * Authors:
 * Fabien Spindler
 *
 *****************************************************************************/


/*!
  \file vpIcCompGrabber.cpp

  \brief Member functions for the IcComp (Imaging Technology) video device
  class (suitable for new Linux Kernel > 2.4).

  \ingroup libdevice
*/
#include <visp/vpConfig.h>


#ifdef VISP_HAVE_ICCOMP


#include <visp/vpIcCompGrabber.h>
#include <visp/vpFrameGrabberException.h>
#include <visp/vpImageIo.h>

const int vpIcCompGrabber::DEFAULT_INPUT = 2;
const int vpIcCompGrabber::DEFAULT_SCALE = 2;

/*!
  Constructor.

  Uses the default input and scale.
  By default the framerate is set to 25 fps.

  \sa setFramerate()
*/
vpIcCompGrabber::vpIcCompGrabber()
{
  init = false ;

  framegrabber = new ICcomp2x ;

  setInput     (vpIcCompGrabber::DEFAULT_INPUT);
  setScale     (vpIcCompGrabber::DEFAULT_SCALE) ;
  setFramerate (vpIcCompGrabber::framerate_25fps);
}

/*!
  Constructor.

  \param _input : video port
  \param _scale : decimation factor

  By default the framerate is set to 25 fps.

  \sa setFramerate()
*/
vpIcCompGrabber::vpIcCompGrabber( unsigned int _input, unsigned int _scale)
{
  init = false ;

  framegrabber = new ICcomp2x ;

  setInput     (_input);
  setScale     (_scale) ;
  setFramerate (vpIcCompGrabber::framerate_25fps);
}

/*!
  Constructor.

  \param I : Image data structure (8 bits image)
  \param _input : video port
  \param _scale : decimation factor

  By default the framerate is set to 25 fps.

  \sa setFramerate()
*/
vpIcCompGrabber::vpIcCompGrabber(vpImage<unsigned char> &I,
				 unsigned int _input, unsigned int _scale )
{
  framegrabber = new ICcomp2x ;

  setInput(_input);
  setScale(_scale) ;
  setFramerate (vpIcCompGrabber::framerate_25fps);

  init = false ;

  open(I) ;
}

/*!
  Constructor.

  \param I : Image data structure (32 bits image)
  \param _input : video port
  \param _scale : decimation factor

  By default the framerate is set to 25 fps.

  \sa setFramerate()
*/
vpIcCompGrabber::vpIcCompGrabber(vpImage<vpRGBa> &I,
				 unsigned int _input, unsigned int _scale )
{
  framegrabber = new ICcomp2x ;

  setInput(_input);
  setScale(_scale) ;
  setFramerate (vpIcCompGrabber::framerate_25fps);

  open(I) ;

}

/*!
  Set the video port.
  \exception settingError : Wrong input (shoud be between 0 and 3).
*/
void
vpIcCompGrabber::setInput(unsigned int _input)
{
  if (_input >3)
  {
    vpERROR_TRACE("Wrong input %d, IC-Comp Frame grabber has only 4 input channels",_input) ;

    throw (vpFrameGrabberException(vpFrameGrabberException::settingError,
				   "Wrong input channel") );
  }

  this->input = _input ;

  framegrabber->SetCamera(_input);
}

/*!
  Set the scale

  \param scale : Decimation factor.

  \exception settingError : Wrong scale (shoud be between 1 and 16).
*/
void
vpIcCompGrabber::setScale(unsigned int scale)
{
  if ((scale <1) || (scale >16))
  {
    vpERROR_TRACE("Wrong scale %d, scale shoud be between 1 and 16",scale) ;
    throw (vpFrameGrabberException(vpFrameGrabberException::settingError,
				   "Wrong scale") );
  }

  this->scale = scale ;

  framegrabber->SetDecimation(scale);
}

/*!
  Initialize the device for grey level image acquisition.

  \param I : Image data structure (8 bits image)

  \sa setScale(), setInput(), setFramerate(), acquire(vpImage<unsigned char>)
*/
void
vpIcCompGrabber::open(vpImage<unsigned char> &I)
{
  if (framegrabber->GetDecimation() ==1)
    framegrabber->SetNBufs(1);
  else
    framegrabber->SetNBufs(2);

  framegrabber->SetDepth(8);

  framegrabber->SetCbCrOrder(ICCOMP_NORMAL_ORDER);

  framegrabber->Init() ;

  ncols = framegrabber->GetWidth() ;
  nrows = framegrabber->GetHeight() ;

  I.resize(nrows,ncols) ;

  init = true ;
}

/*!
  Initialize the device for color image acquisition.

  \param I : Image data structure (32 bits image)

  \sa setScale(), setInput(), setFramerate(), acquire(vpImage<vpRGBa>)
*/
void
vpIcCompGrabber::open(vpImage<vpRGBa> &I)
{
  if (framegrabber != NULL)
    framegrabber = new ICcomp2x ;

  framegrabber->SetDecimation(1) ;

  framegrabber->SetNBufs(1);
  framegrabber->SetDepth(16);

  framegrabber->SetCbCrOrder(ICCOMP_NORMAL_ORDER);

  framegrabber->Init() ;

  ncols = framegrabber->GetWidth()/scale ;
  nrows = framegrabber->GetHeight()/scale ;

  I.resize(nrows,ncols) ;

  init = true ;
}

/*!
  Acquire a color image

  \param I : Image data structure (32 bits image)

  \exception initializationError : The device is not initialized.

  \sa open(vpImage<vpRGBa> &), getField()
*/
void
vpIcCompGrabber::acquire(vpImage<vpRGBa> &I)
{

  if (framegrabber==NULL)
  {
    vpERROR_TRACE("ICcomp not initialized ") ;

    throw (vpFrameGrabberException(vpFrameGrabberException::initializationError,
				   "ICcomp not initialized ") );
  }

  int framebuffer = 0 ;

  unsigned  char *bitmap ;
  bitmap = framegrabber->Acquire(field, framebuffer) ;

  if ((I.getWidth() != ncols)||(I.getHeight() != nrows))
    I.resize(nrows,ncols) ;


  if (scale==1)
    framegrabber->ConvertYCbCrToRGBA(bitmap, (unsigned char *)I.bitmap, nrows, ncols) ;
  else
  {
    unsigned char *bitmaprgba ;
    bitmaprgba = new unsigned char[framegrabber->GetWidth()*framegrabber->GetHeight()*4*sizeof(unsigned char)] ;
    framegrabber->ConvertYCbCrToRGBA(bitmap, bitmaprgba,
				     framegrabber->GetHeight(),
				     framegrabber->GetWidth()) ;

    unsigned char *ptr = bitmaprgba ;
    for (int i=0 ; i < I.getHeight() ; i++)
    {
      for (int j=0 ; j < I.getWidth() ; j++)
      {
	I[i][j].B = *(ptr ) ;
	I[i][j].G = *(ptr +1 ) ;
	I[i][j].R = *(ptr +2) ;

	ptr += 4*scale ;
      }
      ptr += framegrabber->GetWidth()*4*sizeof(unsigned char)*(scale-1) ;
    }

    delete [] bitmaprgba ;

  }
}


/*!
  Acquire a grey level image.

  \param I : Image data structure (8 bits image)

  \exception initializationError : The device is not initialized.

  \sa open(vpImage<unsigned char> &), getField()
*/
void
vpIcCompGrabber::acquire(vpImage<unsigned char> &I)
{

  if (framegrabber==NULL)
  {
    vpERROR_TRACE("ICcomp not initialized ") ;

    throw (vpFrameGrabberException(vpFrameGrabberException::initializationError,
				   "ICcomp not initialized ") );
  }

  int framebuffer = 0 ;

  unsigned  char *bitmap = NULL ;

  switch (framerate) {
  case framerate_25fps:
    bitmap = framegrabber->Acquire(field, framebuffer) ;

    if (framegrabber->GetDecimation()!=1) {
      // If subsampling, we get only the even frame
      while (field == 0)
	bitmap = framegrabber->Acquire(field,framebuffer) ;
    }
    break;

  case framerate_50fps:
    bitmap = framegrabber->Acquire(field, framebuffer) ;

    break;
  }

  if ((I.getWidth() != ncols)||(I.getHeight() != nrows))
    I.resize(nrows,ncols) ;

  memcpy(I.bitmap,bitmap,nrows*ncols)  ;
}

/*!

  Return the field (odd or even) corresponding to the last acquired
  frame.

  This method is to call after acquire() and has only a mean if the acquisition
  framerate is set to 50 fps.

  \return Field of the acquired frame (0 if odd field, 1 if even field).

  \sa acquire(), setFramerate()

*/
bool
vpIcCompGrabber::getField()
{
  return field;
}
/*!

  Set the framerate of the acquisition.

  \param framerate The framerate for the acquisition.

  \sa getFramerate()

*/
void
vpIcCompGrabber::setFramerate(vpIcCompGrabber::vpIcCompFramerateType framerate)
{
   this->framerate = framerate;
}
/*!

  Return the framerate of the acquisition.

  \return The actual framerate of the framegrabber.

  \sa setFramerate()
*/


vpIcCompGrabber::vpIcCompFramerateType
vpIcCompGrabber::getFramerate()
{
  return framerate;
}


/*!
  Close the video port.
*/
void
vpIcCompGrabber::close()
{

  if (framegrabber!=NULL)
  {
    delete framegrabber;
    framegrabber = NULL ;
  }
}


/*!
  Destructor.
  \sa close()
*/
vpIcCompGrabber::~vpIcCompGrabber()
{
  close() ;
}


#endif