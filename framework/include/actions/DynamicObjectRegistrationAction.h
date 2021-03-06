/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef DYNAMICOBJECTREGISTRATIONACTION_H
#define DYNAMICOBJECTREGISTRATIONACTION_H

#include "Action.h"

class DynamicObjectRegistrationAction;

template<>
InputParameters validParams<DynamicObjectRegistrationAction>();

class DynamicObjectRegistrationAction : public Action
{
public:
  DynamicObjectRegistrationAction(InputParameters parameters);

  virtual void act() override;
};

#endif /* DYNAMICOBJECTREGISTRATIONACTION_H */
