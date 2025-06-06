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
      };
   private:

   protected:


   public:
      ALLEGRO_BITMAP* sprite;
      AllegroFlare::Physics::AABB2D aabb2d;
      uint32_t flags;
      Entity();
      ~Entity();

      void draw();
   };
}



