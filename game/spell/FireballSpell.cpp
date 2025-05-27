#include "FireballSpell.hpp"
#include "entity/Player.hpp"
#include "world/GameWorld.hpp"
#include "world/Position.hpp"
#include "entity/Projectile.hpp"
#include "engine/Renderer.hpp"

using namespace game::spell;

void FireballSpell::cast(const Player& caster, GameWorld& world, engine::Renderer& renderer) const {
    Position start = caster.getPosition();
    Position dir = caster.getFacingDirection(); // debe existir
	Position projectile_position = start + dir;
    Position velocity = dir;
	char render_char = '*';

    //auto* projectile = new Projectile(start + dir, velocity, damage, range, caster.getTeam());
    auto* projectile = new game::entity::Projectile("Fireball", render_char, projectile_position, velocity, getDamage(), getRange(), renderer, world);
    world.addEntity(projectile);
}
