//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef AUXKERNEL_H
#define AUXKERNEL_H

#include "AuxKernelTempl.h"

class AuxKernel;

template <>
InputParameters validParams<AuxKernel>();

class AuxKernel : public AuxKernelTempl<Real>
{
public:
  AuxKernel(const InputParameters & parameters);
};

#endif
