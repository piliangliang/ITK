/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkBloxBoundaryPointImage.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#ifndef __itkBloxBoundaryPointImage_h
#define __itkBloxBoundaryPointImage_h

#include "itkPoint.h"
#include "itkBloxBoundaryPointPixel.h"
#include "itkBloxImage.h"

namespace itk
{

/**
 * \class BloxBoundaryPointImage
 * \brief Templated n-dimensional image class used to store linked lists.
 * \ingroup ImageObjects
 *
 * */

template <class TSourceImage,
          class TImageTraits = DefaultImageTraits<BloxBoundaryPointPixel<TSourceImage::ImageDimension>,
          TSourceImage::ImageDimension> >
class ITK_EXPORT BloxBoundaryPointImage :
    public BloxImage<BloxBoundaryPointPixel<TSourceImage::ImageDimension>,
                     TSourceImage::ImageDimension, TImageTraits>
{
public:
  /** Standard class typedefs. */
  typedef BloxBoundaryPointImage  Self;
  typedef BloxImage<BloxBoundaryPointPixel<TSourceImage::ImageDimension>,
                    TSourceImage::ImageDimension, TImageTraits>  Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  
  /** Run-time type information (and related methods). */
  itkTypeMacro(BloxBoundaryPointImage, BloxImage);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Dimension of the image.  This enum is used by functions that are
   * templated over image type (as opposed to being templated over pixel
   * type and dimension) when they need compile time access to the dimension
   * of the image. */
  enum { NDimensions = TSourceImage::ImageDimension };

  /** Pixel typedef support. Used to declare pixel type in filters
   * or other operations. */
  typedef BloxBoundaryPointPixel<NDimensions> PixelType;

  /** Internal Pixel representation. Used to maintain a uniform API
   * with Image Adaptors and allow to keep a particular internal
   * representation of data while showing a different external 
   * representation. */
  typedef PixelType InternalPixelType;

  /**  Accessor type that convert data between internal and external
   *  representations. */
  typedef DefaultPixelAccessor< PixelType > AccessorType;

  /** The type of vector used to convert between physical and blox space */
  typedef Point<double, NDimensions> TPositionType;

  /** The ImageTraits for this image. */
  typedef TImageTraits ImageTraits;

  /** Convenient typedefs obtained from TImageTraits template parameter. */
  typedef typename ImageTraits::PixelContainer PixelContainer;
  typedef typename ImageTraits::SizeType SizeType;
  typedef typename ImageTraits::IndexType IndexType;
  typedef typename ImageTraits::OffsetType OffsetType;
  typedef typename ImageTraits::RegionType RegionType;
  
  /** A pointer to the pixel container. */
  typedef typename PixelContainer::Pointer PixelContainerPointer;

  /**
   * Methods for getting/setting the physical image that this Blox-derived
   * image stores information about.
   */
  void SetSourceImage(typename TSourceImage::Pointer pSource){m_SourceImage = pSource;};
  
  /** Update parameters of the source image (origin, spacing, etc.)
   * Call me before finding boundary points!! */
  void UpdateSourceParameters();

  /** Walk the source image, find boundary points, store them.  */
  void FindBoundaryPoints();

  /** Method to set the threshold for detecting boundary points */
  itkSetMacro(Threshold, double);

protected:
  BloxBoundaryPointImage();
  virtual ~BloxBoundaryPointImage();
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  BloxBoundaryPointImage(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** Pointer to the image that we store info. about */
  typename TSourceImage::Pointer m_SourceImage;

  /** The gradient-magnitude intensity threshold (minimum) for
   * considering a pixel to be a boundary location */
  double m_Threshold;

  /** The origin of the source image */
  const double* m_SourceOrigin;

  /** The spacing of the source image */
  const double* m_SourceSpacing;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkBloxBoundaryPointImage.txx"
#endif

#endif
