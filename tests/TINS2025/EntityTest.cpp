
#include <gtest/gtest.h>

#include <TINS2025/Entity.hpp>


TEST(TINS2025_EntityTest, can_be_created_without_blowing_up)
{
   TINS2025::Entity entity;
}


/*
  - name: handle_enter_player_box_box_collision
    private: true
    parameters:
      - name: player_box
        type: TileFPS::Box*
        default_argument: nullptr
      - name: box
        type: TileFPS::Box*
        default_argument: nullptr
    guards: [ player_box, box ]
    body: |
      //if (box->on_enters_collision_with_player) box->on_enters_collision_with_player();

      if (box->identifier == "sarge")
      {
         std::string dialog_identifier = (!questioned_everyone) ? "mission_briefing" : "mission_review_start";
         event_emitter->emit_activate_dialog_node_by_name_event(dialog_identifier);
      }
      else if (box->identifier == "alfred")
      {
         event_emitter->emit_activate_dialog_node_by_name_event("alfred_questioning");
      }
      else if (box->identifier == "green")
      {
         event_emitter->emit_activate_dialog_node_by_name_event("green_questioning");
      }
      else if (box->identifier == "emily")
      {
         event_emitter->emit_activate_dialog_node_by_name_event("emily_questioning");
      }
      return;
*/


