/***
DEVSIM
Copyright 2013 Devsim LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***/

#ifndef DS_EQUATION_ERRORS_HH
#define DS_EQUATION_ERRORS_HH
#include <string>
#include "GeneralErrors.hh"
#include "OutputStream.hh"
class Region;
class Contact;
class Equation;
class ContactEquation;
class InterfaceEquation;

namespace dsErrors {


  std::string MissingEquationModel(const Region &, const std::string &/*equation_name*/, const std::string &/*model_name*/, ModelInfo::ModelType /*model_type*/, OutputStream::OutputType /*error_level*/);

  std::string MissingEquationIndex(const Region &, const std::string &/*equation_name*/, const std::string &/*variable_name*/, OutputStream::OutputType /*error_level*/);

  std::string MissingContactEquationModel(const Region &, const ContactEquation &/*contact_equation*/, const std::string &/*model_name*/, ModelInfo::ModelType /*model_type*/, OutputStream::OutputType /*error_level*/);

  std::string MissingContactEquationIndex(const Region &, const Contact &, const std::string &/*equation_name*/, OutputStream::OutputType /*error_level*/);

  std::string SolutionVariableNonPositive(const Region &, const std::string &/*equation_name*/, const std::string &/*variable*/, double /*value*/, OutputStream::OutputType /*error_level*/);
  std::string MissingCircuitNodeOnContactEquation(const ContactEquation &/*contact_equation*/,  const std::string &/*circuit_node*/, OutputStream::OutputType /*error_level*/);

  std::string EquationMathErrorInfo(const Equation &/*equation*/, OutputStream::OutputType /*error_level*/);

  std::string CreateModelOnRegion(const Region &/*region*/, const std::string &/*model_name*/, OutputStream::OutputType /*error_level*/);

  std::string MissingInterfaceEquationModel(const Region &/*region*/, const InterfaceEquation &/*interface_equation*/, const std::string &/*model_name*/, OutputStream::OutputType /*error_level*/);
}
#endif
