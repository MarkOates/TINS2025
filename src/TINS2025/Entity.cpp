

#include <TINS2025/Entity.hpp>

#include <allegro5/allegro_primitives.h>


namespace TINS2025
{


Entity::Entity()
   : sprite(nullptr)
   , aabb2d({})
   , flags(0)
{
}


Entity::~Entity()
{
}


AllegroFlare::Physics::AABB2D &Entity::get_aabb2d_ref()
{
   return aabb2d;
}


void Entity::draw()
{
   al_draw_rectangle(
      aabb2d.get_x(),
      aabb2d.get_y(),
      aabb2d.get_x()+aabb2d.get_w(),
      aabb2d.get_y()+aabb2d.get_h(),
      ALLEGRO_COLOR{1, 1, 1, 1},
      1.0
   );
}


} // namespace TINS2025


