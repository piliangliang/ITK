
/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkSphereSpatialFunction.h
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
#ifndef __itkSphereSpatialFunction_h
#define __itkSphereSpatialFunction_h

#include "itkInteriorExteriorSpatialFunction.h"

namespace itk
{

/** \class SphereSpatialFunction
 * \brief Spatial function implementation of a sphere
 *
 * Implements a function that returns 0 for points inside or on the surface
 * of a sphere, 1 for points outside the sphere
 * 
 * \ingroup SpatialFunctions
 */
template <unsigned int VImageDimension=3,typename TInput=Point<double,3> >
class ITK_EXPORT SphereSpatialFunction : 
            public InteriorExteriorSpatialFunction<VImageDimension,TInput>
{
public:
  /** Standard class typedefs. */
  typedef SphereSpatialFunction<VImageDimension,TInput> Self;
  typedef InteriorExteriorSpatialFunction<VImageDimension,TInput> Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
    
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(SphereSpatialFunction,InteriorExteriorSpatialFunction);

  /** Input type for the function. */
  typedef typename Superclass::InputType InputType;

  /** Output type for the function. */
  typedef typename Superclass::OutputType OutputType;

  /** Evaluates the function at a given position */
  OutputType Evaluate(const InputType& position) const;

  /** Get and set the center of the sphere. */
  itkGetMacro( Center, InputType);
  itkSetMacro( Center, InputType);
  
  /** Get and set the radius of the sphere */
  itkGetMacro( Radius, double);
  itkSetMacro( Radius, double);
       
protected:
  SphereSpatialFunction();
  virtual ~SphereSpatialFunction();
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  SphereSpatialFunction(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** The center of the sphere (of the same type as Input). */
  InputType m_Center;

  /** The radius of the sphere. */
  double m_Radius;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkSphereSpatialFunction.txx"
#endif

#endif
