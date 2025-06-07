#pragma once


#include <AllegroFlare/AssetStudio/Database.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/CollisionObservers/Simple.hpp>
#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <DialControl/ViewMotionStudio.hpp>
#include <TINS2025/Entity.hpp>
#include <TINS2025/Gameplay/Level.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace TINS2025
{
   namespace Gameplay
   {
      class Screen : public AllegroFlare::Screens::Gameplay
      {
      public:
         static constexpr char* DEFAULT_DATA_FOLDER_PATH = (char*)"[unset-data_folder_path]";
         static constexpr char* TYPE = (char*)"TINS2025/Gameplay/Screen";

      private:
         enum InputMode : uint32_t
         {
            INPUT_MODE_NONE = 0,
            INPUT_MODE_PLAYING,
            INPUT_MODE_EDITING,
         };
         std::string data_folder_path;
         AllegroFlare::AssetStudio::Database* asset_studio_database;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::ModelBin* model_bin;
         AllegroFlare::DialogSystem::DialogSystem* dialog_system;
         DialControl::ViewMotionStudio view_motion_studio;
         bool hide_view_motion_studio_hud;
         std::string current_level_identifier;
         TINS2025::Gameplay::Level* current_level;
         AllegroFlare::CollisionObservers::Simple collision_observer;
         AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
         AllegroFlare::Placement3D environment_overlay_placement;
         std::vector<TINS2025::Entity> entities;
         AllegroFlare::Model3D* environment_model;
         TINS2025::Entity* player_entity;
         int input_mode;
         bool initialized;

      protected:


      public:
         Screen();
         virtual ~Screen();

         void set_data_folder_path(std::string data_folder_path);
         void set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_model_bin(AllegroFlare::ModelBin* model_bin);
         void set_dialog_system(AllegroFlare::DialogSystem::DialogSystem* dialog_system);
         std::string get_data_folder_path() const;
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::DialogSystem::DialogSystem* get_dialog_system() const;
         bool get_initialized() const;
         AllegroFlare::AssetStudio::Database* &get_asset_studio_database_ref();
         void initialize();
         virtual void gameplay_suspend_func() override;
         virtual void gameplay_resume_func() override;
         void load_up_world();
         virtual bool load_level_by_identifier(std::string level_identifier="[unset-level_identifier]") override;
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         void render();
         virtual void game_event_func(AllegroFlare::GameEvent* game_event=nullptr) override;
         void refresh_environment_and_world(bool set_player_position=false);
         virtual void display_switch_in_func() override;
         virtual void primary_update_func(double time_now=0.0f, double delta_time=1.0f) override;
         virtual void primary_render_func() override;
         virtual void key_down_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
         ALLEGRO_FONT* obtain_font();
         void DEVELOPMENT__render_tile_map();
         static AllegroFlare::DialogTree::NodeBank build_dialog_node_bank();
      };
   }
}



