/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile$

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkSymToGenMatrixFilter - mask a tensor field according to a scalar field

// .SECTION Description
// A Class to convert 6-element tensors to 9-element tensors.
// NIfTI-Style: sym-Matrix -> gen-Matrix

// .SECTION Thanks
// noone

#ifndef vtkSymToGenMatrixFilter_h
#define vtkSymToGenMatrixFilter_h

#include "vtkDataSetAlgorithm.h"

class vtkSymToGenMatrixFilter : public vtkDataSetAlgorithm
{
public:
  vtkGetMacro(iso, double);
  vtkSetMacro(iso, double);

  vtkTypeMacro(vtkSymToGenMatrixFilter, vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
  static vtkSymToGenMatrixFilter *New();

protected:
  vtkSymToGenMatrixFilter();
  ~vtkSymToGenMatrixFilter();

  /* implementation of algorithm */
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  virtual int FillInputPortInformation(int port, vtkInformation* info);
  void SetActiveTensors(int, int, int, int, const char *);

protected:
  double iso;

private:
  vtkSymToGenMatrixFilter(const vtkSymToGenMatrixFilter&);  // Not implemented.
  void operator=(const vtkSymToGenMatrixFilter&);  // Not implemented.
};

#endif
