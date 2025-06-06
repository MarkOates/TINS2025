#pragma once


#include <AllegroFlare/Physics/AABB2D.hpp>
#include <allegro5/allegro.h>
#include <cstdint>


namespace TINS2025
{
   class Entity
   {
   public:

      enum Flags
      {
         FLAG_NONE = 0x0000,
         FLAG_HIDDEN = 0x0001,
         FLAG_COLLIDES_WITH_PLAYER = 0x0002,
         FLAG_COLLIDES_WITH_TILEMAP = 0x0004,
      };
      enum Type
      {
         ENTITY_TYPE_UNDEF = 0,
         ENTITY_TYPE_PLAYER,
         ENTITY_TYPE_APPLE,
      };
   private:

   protected:


   public:
      ALLEGRO_BITMAP* sprite;
      uint32_t type;
      AllegroFlare::Physics::AABB2D aabb2d;
      uint32_t flags;
      Entity();
      ~Entity();

      void draw();
   };
}



