#include "PhysicsSystem.h"
#include "AdvancePosition.h"
#include "AdvanceVelocity.h"
#include "LeapFrog6Solver.h"

namespace pba
{
   using std::string;
   using std::vector;

   PhysicsSystem::PhysicsSystem()
   {
   }

   PhysicsSystem::~PhysicsSystem() {}

   void PhysicsSystem::Init(SoftBodyState pq, std::shared_ptr<pba::Force> f, double _dt)
   {
      softbody = pq;
      dt = _dt;
      force_ptr = f;

      auto pos_part = std::make_shared<AdvancePosition>(softbody);
      auto vel_part = std::make_shared<AdvanceVelocity>(softbody, force_ptr);

      leap_frog_6 = std::make_shared<LeapFrog6Solver>(pos_part, vel_part);
      leap_frog_6->init();
   }

   void PhysicsSystem::Solve()
   {
      leap_frog_6->solve(dt);
   }
   void PhysicsSystem::Reset()
   {
      leap_frog_6->init();
   }

}