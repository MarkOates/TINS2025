

#include <TINS2025/Entity.hpp>

#include <allegro5/allegro_primitives.h>


namespace TINS2025
{


Entity::Entity()
   : sprite(nullptr)
   , model(nullptr)
   , type(TINS2025::Entity::ENTITY_TYPE_UNDEF)
   , aabb2d({})
   , flags(0)
{
}


Entity::~Entity()
{
}


void Entity::draw()
{
   // Draw the box
   al_draw_rectangle(
      aabb2d.get_x(),
      aabb2d.get_y(),
      aabb2d.get_x()+aabb2d.get_w(),
      aabb2d.get_y()+aabb2d.get_h(),
      ALLEGRO_COLOR{1, 1, 1, 1},
      1.0
   );

   // Draw the sprite (bottom centered)
   if (sprite)
   {
      ALLEGRO_BITMAP *bitmap = sprite;

      float center_x = aabb2d.get_x() + aabb2d.get_w() / 2.0f;
      float center_y = aabb2d.get_y() + aabb2d.get_h() / 2.0f;

      float bitmap_w = al_get_bitmap_width(bitmap);
      float bitmap_h = al_get_bitmap_height(bitmap);

      float draw_x = center_x - bitmap_w / 2.0f;
      float draw_y = center_y - bitmap_h;

      al_draw_bitmap(bitmap, draw_x, draw_y, 0);
   }
}


} // namespace TINS2025


