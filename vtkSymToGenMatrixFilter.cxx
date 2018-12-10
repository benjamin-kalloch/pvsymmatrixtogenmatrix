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

#include "vtkSymToGenMatrixFilter.h"

#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkCellArray.h"
#include "vtkAppendPolyData.h"
#include "vtkMath.h"
#include "vtkDoubleArray.h"
#include "vtkIdTypeArray.h"

#include "vtkCompositeDataIterator.h"
#include "vtkSelectEnclosedPoints.h"
#include "vtkSmartPointer.h"


vtkStandardNewMacro(vtkSymToGenMatrixFilter);

vtkSymToGenMatrixFilter::vtkSymToGenMatrixFilter()
{
    this->SetNumberOfInputPorts(1);

    // by default, process active point tensors
    this->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS,
                               vtkDataSetAttributes::TENSORS);
}

vtkSymToGenMatrixFilter::~vtkSymToGenMatrixFilter()
{
}

int vtkSymToGenMatrixFilter::FillInputPortInformation
(
  int               port,
  vtkInformation*   info
)
{
    info->Remove( vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE() );
    info->Set( vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkDataSet" );

    return 1;
}


int vtkSymToGenMatrixFilter::RequestData
(
  vtkInformation        *vtkNotUsed(request),
  vtkInformationVector  **inputVector,
  vtkInformationVector  *outputVector
  )
{
    // get the info objects
    vtkInformation *inInfoP0 = inputVector[0]->GetInformationObject(0);
    vtkInformation *outInfo  = outputVector->GetInformationObject(0);

    // get the input and output
    vtkDataSet *tensors = vtkDataSet::SafeDownCast( inInfoP0->Get( vtkDataObject::DATA_OBJECT() ) );
    vtkDataSet *output  = vtkDataSet::SafeDownCast( outInfo->Get( vtkDataObject::DATA_OBJECT() ) );

    vtkPointData *tensorsPD = tensors->GetPointData();;
    vtkPointData *outputPD  = output->GetPointData();

    if ( !tensorsPD )
    {
        vtkErrorMacro(<<"No input tensor-data!");
        return 0;
    }

    // First, copy the input to the output as a starting point
    output->CopyStructure( tensors );
    //~ output->CopyAttributes( tensors );

    // proceed only, if both mask and tensor-field have data-points (attributes)
    if( tensorsPD->GetNumberOfArrays() > 0)
    {
        // retrieve the data-points
        vtkDataArray *tensorData  = tensorsPD->GetArray(0);
        vtkDataArray *outputData  = vtkDataArray::CreateDataArray(VTK_DOUBLE);

        vtkIdType numOfTuples  = tensorsPD->GetNumberOfTuples();
        int componentsPerValue = tensorsPD->GetNumberOfComponents();
        outputData->SetNumberOfComponents( 9 );         // from doc: "Make sure that this is set before allocation. "
        outputData->SetNumberOfTuples( numOfTuples );   // allocation
        outputData->SetName( "Gen-Matrices" );

        double symTensor[6];
        for( vtkIdType t = 0; t < numOfTuples; t++)
        {
            tensorData->GetTuple( t, symTensor );

            // used to work like this before (probably FSL ordering)
/*
            double genTensor[9] = {
                    symTensor[0], symTensor[1], symTensor[2],
                    symTensor[1], symTensor[3], symTensor[4],
                    symTensor[2], symTensor[4], symTensor[5]
                };
*/
            // now with MRTrix derived tensors:
            double genTensor[9] = {
                    symTensor[0], symTensor[3], symTensor[5],
                    symTensor[3], symTensor[1], symTensor[4],
                    symTensor[5], symTensor[4], symTensor[2]
                };
            outputData->SetTuple( t, genTensor );
        }
        outputPD->AddArray( outputData );
    }
    else
    {
        vtkErrorMacro(<<"The input fields does not conatin any data!");
    }

  return 1;
}

void vtkSymToGenMatrixFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
