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

#include "TriangleEdgeSubModel.hh"
#include "Region.hh"
#include "Edge.hh"
#include "Vector.hh"
#include "Device.hh"
#include "dsAssert.hh"
#include "GeometryStream.hh"
#include "ModelErrors.hh"


#include <sstream>


TriangleEdgeSubModel::TriangleEdgeSubModel(const std::string &nm, RegionPtr rp, TriangleEdgeModel::DisplayType dt)
    :
        TriangleEdgeModel(nm, rp, dt),
        parentModel()
{
}

TriangleEdgeSubModel::TriangleEdgeSubModel(const std::string &nm, RegionPtr rp, ConstTriangleEdgeModelPtr nmp, TriangleEdgeModel::DisplayType dt)
    :
        TriangleEdgeModel(nm, rp, dt),
        parentModel(nmp)
{
    parentModelName = parentModel.lock()->GetName();

    //// TODO: consider making it so that we have different kinds of callbacks
    RegisterCallback(parentModelName);
#if 0
    os << "creating TriangleEdgeSubModel " << nm << " with parent " << parentModel->GetName() << "\n";
#endif
}

TriangleEdgeModelPtr TriangleEdgeSubModel::CreateTriangleEdgeSubModel(const std::string &nm, RegionPtr rp, TriangleEdgeModel::DisplayType dt)
{
  TriangleEdgeModel *p = new TriangleEdgeSubModel(nm, rp, dt);
  return p->GetSelfPtr();
}

TriangleEdgeModelPtr TriangleEdgeSubModel::CreateTriangleEdgeSubModel(const std::string &nm, RegionPtr rp, TriangleEdgeModel::DisplayType dt, ConstTriangleEdgeModelPtr nmp)
{
  TriangleEdgeModel *p = new TriangleEdgeSubModel(nm, rp, nmp, dt);
  return p->GetSelfPtr();
}

void TriangleEdgeSubModel::calcTriangleEdgeScalarValues() const
{
    if (!parentModelName.empty())
    {
#if 0
      os << "updating TriangleEdgeSubModel " << GetName() << " from parent " << parentModel->GetName() << "\n";
#endif
      ConstTriangleEdgeModelPtr emp = GetRegion().GetTriangleEdgeModel(parentModelName);
      if (!parentModel.expired())
      {
        parentModel.lock()->GetScalarValues();
      }
      else if (emp != parentModel.lock())
      {
        parentModel.reset();
        dsErrors::ChangedModelModelDependency(GetRegion(), parentModelName, dsErrors::ModelInfo::ELEMENTEDGE, GetName(), dsErrors::ModelInfo::ELEMENTEDGE, OutputStream::INFO);
        parentModelName.clear();
      }
      else
      {
        dsAssert(0, "UNEXPECTED");
      }
    }
}

void TriangleEdgeSubModel::Serialize(std::ostream &of) const
{
  if (!parentModelName.empty())
  {
    of << "DATAPARENT \"" << parentModelName << "\"";
  }
  else if (this->IsUniform())
  {
    of << "UNIFORM " << GetUniformValue();
  }
  else
  {
    of << "DATA\n";
    const TriangleEdgeScalarList &vals = this->GetScalarValues();
    for (size_t i = 0; i < vals.size(); ++i)
    {
      of << vals[i] << "\n";
    }
  }
}

