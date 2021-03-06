/*
 * Medical Image Registration ToolKit (MIRTK)
 *
 * Copyright 2013-2015 Imperial College London
 * Copyright 2013-2015 Andreas Schuh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MIRTK_IntensityCrossCorrelation_H
#define MIRTK_IntensityCrossCorrelation_H

#include <mirtkImageSimilarity.h>


namespace mirtk {


/**
 * Cross correlation image similarity measure
 */
class IntensityCrossCorrelation : public ImageSimilarity
{
  mirtkEnergyTermMacro(IntensityCrossCorrelation, EM_CC);

  // ---------------------------------------------------------------------------
  // Construction/Destruction
public:

  /// Constructor
  IntensityCrossCorrelation(const char * = "");

  /// Copy constructor
  IntensityCrossCorrelation(const IntensityCrossCorrelation &);

  /// Assignment operator
  IntensityCrossCorrelation &operator =(const IntensityCrossCorrelation &);

  /// Destructor
  ~IntensityCrossCorrelation();

  // ---------------------------------------------------------------------------
  // Evaluation
protected:

  /// Evaluate similarity of images
  virtual double Evaluate();

  /// Evaluate non-parametric similarity gradient w.r.t the given image
  virtual bool NonParametricGradient(const RegisteredImage *, GradientImageType *);

};


} // namespace mirtk

#endif // MIRTK_IntensityCrossCorrelation_H
