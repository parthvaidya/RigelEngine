/* Copyright (C) 2016, Nikolai Wuttke. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "base/warnings.hpp"
#include "engine/base_components.hpp"

RIGEL_DISABLE_WARNINGS
#include <entityx/entityx.h>
RIGEL_RESTORE_WARNINGS

namespace rigel {

struct IGameServiceProvider;
namespace engine { class CollisionChecker; }
namespace engine { class RandomNumberGenerator; }
namespace engine { namespace components { struct Sprite; }}
namespace game_logic { class EntityFactory; }

}


namespace rigel { namespace game_logic { namespace ai {

namespace components {

struct BlueGuard {
  static BlueGuard typingOnTerminal() {
    BlueGuard instance;
    instance.mTypingOnTerminal = true;
    return instance;
  }

  static BlueGuard patrolling(const engine::components::Orientation orientation) {
    BlueGuard instance;
    instance.mOrientation = orientation;
    return instance;
  }

  engine::components::Orientation mOrientation =
    engine::components::Orientation::Left;
  int mStanceChangeCountdown = 0;
  int mStepsWalked = 0;
  bool mTypingOnTerminal = false;
  bool mOneStepWalkedSinceTypingStop = true;
  bool mIsCrouched = false;
};

}

class BlueGuardSystem {
public:
  BlueGuardSystem(
    entityx::Entity player,
    engine::CollisionChecker* pCollisionChecker,
    EntityFactory* pEntityFactory,
    IGameServiceProvider* pServiceProvider,
    engine::RandomNumberGenerator* pRandomGenerator);

  void update(entityx::EntityManager& es);
  void onEntityHit(entityx::Entity entity);

private:
  void stopTyping(
    components::BlueGuard& state,
    engine::components::Sprite& sprite,
    engine::components::WorldPosition& position);

  void updateGuard(
    entityx::Entity guardEntity,
    components::BlueGuard& state,
    engine::components::Sprite& sprite,
    engine::components::WorldPosition& position);

private:
  entityx::Entity mPlayer;
  engine::CollisionChecker* mpCollisionChecker;
  EntityFactory* mpEntityFactory;
  IGameServiceProvider* mpServiceProvider;
  engine::RandomNumberGenerator* mpRandomGenerator;

  bool mIsOddFrame = false;
};

}}}
