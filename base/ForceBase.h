#pragma once
#include <memory>
#include "SoftBodyStateData.h"

namespace pba
{
   class ForceBase
   {
   public:
      ForceBase() {};
      virtual void compute(SoftBodyState &p, const float dt) = 0;
      virtual ~ForceBase() {};
   };

   typedef std::shared_ptr<ForceBase> ForceBasePtr;

}