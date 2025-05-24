#include "fireballSpell.hpp"
#include "player.hpp"
#include "gameWorld.hpp"
#include "position.hpp"
#include "projectile.hpp"

FireballSpell::FireballSpell()
    : DamageSpell("Fireball", 5, 10, 20) {}

void FireballSpell::cast(Player& caster, GameWorld& world) const {
    Position start = caster.getPosition();
    Position dir = caster.getFacingDirection(); // debe existir
	Position projectile_position = start + dir;
    Position velocity = dir;
	char render_char = '*';

    //auto* projectile = new Projectile(start + dir, velocity, damage, range, caster.getTeam());
    auto* projectile = new Projectile("Fireball", render_char, projectile_position, velocity, getDamage(), getRange());
    world.addEntity(projectile);
}
