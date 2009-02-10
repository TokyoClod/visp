/****************************************************************************
 *
 * $Id: vpFeaturePoint.h,v 1.11 2008-09-26 15:21:02 fspindle Exp $
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
 * 2D point visual feature.
 *
 * Authors:
 * Eric Marchand
 *
 *****************************************************************************/


#ifndef vpFeaturePoint_H
#define vpFeaturePoint_H

/*!
  \file vpFeaturePoint.h
  \brief Class that defines 2D point visual feature
*/

#include <visp/vpConfig.h>
#include <visp/vpMatrix.h>
#include <visp/vpBasicFeature.h>
#include <visp/vpPoint.h>

#include <visp/vpHomogeneousMatrix.h>
#include <visp/vpRGBa.h>


/*!
  \class vpFeaturePoint
  \ingroup VsFeature2

  \brief Class that defines 2D image point visual feature with
  cartesian coordinates \f$(x,y)\f$.
*/
class VISP_EXPORT vpFeaturePoint : public vpBasicFeature
{
private:
  //! FeaturePoint depth (required to compute the interaction matrix)
  //! default Z = 1m
  double Z ;

public:
  //! basic construction
  void init() ;
  //! basic constructor
  vpFeaturePoint() ;
  //! destructor
  virtual ~vpFeaturePoint() { ; }


  /*
    section Set coordinates
  */

  void buildFrom(const double x, const double y, const double Z) ;

  //! set the point x-coordinates
  void set_x(const double x) ;
  //! set the point y-coordinates
  void set_y(const double y) ;
  //! set the point depth (camera frame)
  void set_Z(const double Z) ;
  //! set the point xy and Z-coordinates
  void set_xyZ(const double x, const double y, const double Z) ;

  //! get the point x-coordinates
  double get_x()  const ;
  //! get the point y-coordinates
  double get_y()   const ;
  //! get the point depth (camera frame)
  double get_Z() const  ;


  /*
    vpBasicFeature method instantiation
  */

  // feature selection
  inline static int selectX()  { return FEATURE_LINE[0] ; }
  inline static int selectY()  { return FEATURE_LINE[1] ; }
  //! compute the interaction matrix from a subset a the possible features
  vpMatrix  interaction(const int select = FEATURE_ALL) const;
  //! compute the error between two visual features from a subset
  //! a the possible features
  vpColVector error(const vpBasicFeature &s_star,
		    const int select = FEATURE_ALL)  ;
  //! print the name of the feature
  void print(const int select = FEATURE_ALL ) const ;

  //! feature duplication
  vpFeaturePoint *duplicate() const ;


  void display(const vpCameraParameters &cam,
	       vpImage<unsigned char> &I,
	       vpColor::vpColorType color=vpColor::green) const ;
  void display(const vpCameraParameters &cam,
               vpImage<vpRGBa> &I,
               vpColor::vpColorType color=vpColor::green) const ;


  /*!
    @name Deprecated functions
  */
  typedef enum
    {
      X,   // x coordinates
      Y    // y coordinates
    } vpFeaturePointType;
  //! Compute the error between a visual features and zero
  vpColVector error(const int select = FEATURE_ALL)  ;

} ;



#endif

/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */
