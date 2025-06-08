#pragma once


#include <AllegroFlare/Model3D.hpp>
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
         FLAG_INACTIVE = 0x0001,
         FLAG_HIDDEN = 0x0002,
         FLAG_COLLIDES_WITH_PLAYER = 0x0004,
         FLAG_COLLIDES_WITH_TILEMAP = 0x0008,
      };
      enum Type
      {
         ENTITY_TYPE_UNDEF = 0,
         ENTITY_TYPE_PLAYER,
         ENTITY_TYPE_FRIEND_1,
         ENTITY_TYPE_FRIEND_2,
         ENTITY_TYPE_FRIEND_3,
         ENTITY_TYPE_APPLE,
         ENTITY_TYPE_CARROT,
         ENTITY_TYPE_RED_CARROT,
      };
      enum AnimationMode
      {
         ANIMATION_MODE_UNDEF = 0,
         ANIMATION_MODE_STANDING,
         ANIMATION_MODE_WALKING_WOBBLY,
         ANIMATION_MODE_JUMPING_IN_EXCITEMENT,
      };
   private:

   protected:


   public:
      ALLEGRO_BITMAP* sprite;
      AllegroFlare::Model3D* model;
      uint32_t type;
      uint32_t animation_mode;
      AllegroFlare::Physics::AABB2D aabb2d;
      uint32_t flags;
      Entity();
      ~Entity();

      void draw();
   };
}



