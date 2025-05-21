#include "fireballSpell.h"
#include "player.hpp"
#include "projectile.hpp"
#include "gameWorld.hpp"

FireballSpell::FireballSpell()
    : DamageSpell("Fireball", 5, 10, 20) {}

void FireballSpell::cast(Player& caster, GameWorld& world) const {
    Position start = caster.getPosition();
    Position dir = caster.getFacingDirection(); // debe existir
    Position velocity = dir;

    //auto* projectile = new Projectile(start + dir, velocity, damage, range, caster.getTeam());
    auto* projectile = new Projectile(start + dir, velocity, getDamage(), getRange());
    world.addEntity(projectile);
}
