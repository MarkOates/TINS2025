
#include <gtest/gtest.h>

#include <TINS2025/Game/Configurations/Main.hpp>


TEST(TINS2025_Game_Configurations_MainTest, can_be_created_without_blowing_up)
{
   TINS2025::Game::Configurations::Main main_configuration;
}


TEST(TINS2025_Game_Configurations_MainTest, load_level_by_identifier__will_not_blow_up)
{
   TINS2025::Game::Configurations::Main main_configuration;
   AllegroFlare::Levels::Base* level = main_configuration.load_level_by_identifier("forest_village_1");
   EXPECT_NE(nullptr, level);
}

/*
      result->set_on_paused_callback_func(
         [runner](AllegroFlare::Screens::Gameplay* screen, void* user_data){
            runner->get_event_emitter()->emit_router_event(
               AllegroFlare::Routers::Standard::EVENT_PAUSE_GAME,
               nullptr,
               al_get_time()
            );
         }
      );
      result->set_on_finished_callback_func(
         [runner](AllegroFlare::Screens::Gameplay* screen, void* user_data){
            runner->get_event_emitter()->emit_router_event(
               AllegroFlare::Routers::Standard::EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED,
               nullptr,
               al_get_time()
            );
         }
      );
*/

