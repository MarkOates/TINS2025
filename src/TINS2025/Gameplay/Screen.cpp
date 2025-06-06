

#include <TINS2025/Gameplay/Screen.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <TINS2025/Gameplay/Level.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace TINS2025
{
namespace Gameplay
{


Screen::Screen()
   : AllegroFlare::Screens::Gameplay()
   , data_folder_path(DEFAULT_DATA_FOLDER_PATH)
   , asset_studio_database(nullptr)
   , event_emitter(nullptr)
   , bitmap_bin(nullptr)
   , font_bin(nullptr)
   , model_bin(nullptr)
   , dialog_system(nullptr)
   , view_motion_studio({})
   , current_level_identifier("[unset-current_level]")
   , current_level(nullptr)
   , collision_observer({})
   , collision_tile_map({})
   , entities({})
   , player_entity(nullptr)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_data_folder_path(std::string data_folder_path)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_data_folder_path]: error: guard \"get_initialized()\" not met.");
   this->data_folder_path = data_folder_path;
}


void Screen::set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_asset_studio_database]: error: guard \"get_initialized()\" not met.");
   this->asset_studio_database = asset_studio_database;
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_event_emitter]: error: guard \"get_initialized()\" not met.");
   this->event_emitter = event_emitter;
}


void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void Screen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_model_bin]: error: guard \"get_initialized()\" not met.");
   this->model_bin = model_bin;
}


void Screen::set_dialog_system(AllegroFlare::DialogSystem::DialogSystem* dialog_system)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_dialog_system]: error: guard \"get_initialized()\" not met.");
   this->dialog_system = dialog_system;
}


std::string Screen::get_data_folder_path() const
{
   return data_folder_path;
}


AllegroFlare::EventEmitter* Screen::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::DialogSystem::DialogSystem* Screen::get_dialog_system() const
{
   return dialog_system;
}


bool Screen::get_initialized() const
{
   return initialized;
}


AllegroFlare::AssetStudio::Database* &Screen::get_asset_studio_database_ref()
{
   return asset_studio_database;
}


void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"model_bin\" not met");
   }
   if (!(dialog_system))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"dialog_system\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"dialog_system\" not met");
   }
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   load_up_world();
   initialized = true;
   return;
}

void Screen::gameplay_suspend_func()
{
   // Function that is called immediately after the gameplay is suspended.
   //AllegroFlare::Logger::warn_from_once(
      //"AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      //"Not implemented in the base class. This method should be implemented in the derived class. Take into account "
         //"the AllegroFlare/Screens/Gameplay class has a suspend_gameplay func"
   //);
   return;
}

void Screen::gameplay_resume_func()
{
   // Function that is called immediately after the gameplay is resumed.
   //AllegroFlare::Logger::warn_from_once(
      //"AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      //"Not implemented in the base class. This method should be implemented in the derived class. Take into account "
         //"the AllegroFlare/Screens/Gameplay class has a resume_gameplay func"
   //);
   return;
}

void Screen::load_up_world()
{
   collision_observer.clear();

   // Setup the tile map
   collision_tile_map.resize(100, 100);
   collision_tile_map.initialize();
   //collision_tile_map.set_tile(69, 34, 1);


   // Setup the entities
   entities.reserve(256);

   Entity e;
   e.aabb2d.set_x(1920/2);
   e.aabb2d.set_y(1080/2);
   e.aabb2d.set_w(40);
   e.aabb2d.set_h(20);
   e.sprite = bitmap_bin->auto_get("character-012.png");
   e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_TILEMAP;
   entities.push_back(e);

   player_entity = &entities.back();

   {
      Entity e;
      e.aabb2d.set_x(1920/2 + 200);
      e.aabb2d.set_y(1080/2);
      e.aabb2d.set_w(20);
      e.aabb2d.set_h(10);
      e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_PLAYER;
      entities.push_back(e);
   }


   // Setup the dialog
   dialog_system->set_dialog_node_bank(build_dialog_node_bank());
   //dialog_system->set_standard_dialog_box_font_name("MavenPro-Medium.ttf");
   //dialog_system->set_standard_dialog_box_font_size(-52);
   //dialog_system->set_standard_dialog_box_font_line_height(-52); // TODO: Add this feature
   //dialog_system->set_standard_dialog_box_width(1920 * 0.6);
   //dialog_system->set_standard_dialog_box_height(248);
   dialog_system->set_standard_dialog_box_y(1080/5*4+60);


   // Setup view_motion_studio
   view_motion_studio.set_font_bin(font_bin);
   view_motion_studio.initialize();
   //view_motion_studio.load_json(cameras_json_string); // Load some test data
   // TODO: Fix these paths
   std::string filename_load = "tests/fixtures/animations/camera_move_1-0n.txt";
   //std::string filename_save = "tests/fixtures/animations/camera_move_1-0n_output.txt";
   //std::cout << "loading json" << std::endl;
   std::string file_content = AllegroFlare::php::file_get_contents(filename_load);
   view_motion_studio.load_json(file_content);


   return;
}

bool Screen::load_level_by_identifier(std::string level_identifier)
{
   return false;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::on_activate]: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::on_deactivate]: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::update()
{
   if (!get_gameplay_suspended())
   {
      // Observe aabb2d <-> tile steps
      AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(
         &collision_tile_map,
         nullptr,
         16.0f,
         16.0f
      );
      for (auto &entity : entities)
      {
         if ((entity.flags & TINS2025::Entity::FLAG_COLLIDES_WITH_TILEMAP) == 0) continue;
         tile_map_collision_stepper.set_aabb2d(&entity.aabb2d);
         tile_map_collision_stepper.step();
      }

      // Observe changes in bounding box collisions
      collision_observer.set_subject(player_entity);
      std::set<void*> collidables;
      for (auto &entity : entities)
      {
         if (entity.flags & TINS2025::Entity::FLAG_COLLIDES_WITH_PLAYER) collidables.insert((void*)&entity);
      }
      collision_observer.set_collidables(collidables);
      collision_observer.set_on_test_collide([](void* subject_v, void* collidable_v) -> bool {
         TINS2025::Entity &subject = *static_cast<TINS2025::Entity*>(subject_v);
         TINS2025::Entity &collidable = *static_cast<TINS2025::Entity*>(collidable_v);

         return (subject.aabb2d.collides(&collidable.aabb2d));
      });

      collision_observer.process();

      for (auto &entered : collision_observer.get_entered())
      {
         TINS2025::Entity &collidable = *static_cast<TINS2025::Entity*>(entered);
         collidable.flags |= TINS2025::Entity::FLAG_HIDDEN;
         event_emitter->emit_activate_dialog_node_by_name_event("pickup_apple");
         //event_emitter->emit_activate_dialog_node_by_name_event("alfred_questioning");
      }
   }

   // Update the view motion
   view_motion_studio.update();

   // TODO
   //view_motion_studio.setup_camera_projection_on_live_camera();

   // Render the view motion hud
   view_motion_studio.render_hud();

   return;
}

void Screen::render()
{
   DEVELOPMENT__render_tile_map();

   for (auto &entity : entities)
   {
      if ((entity.flags & TINS2025::Entity::FLAG_HIDDEN) == 0) entity.draw();
   }

   //DEVELOPMENT__render_tile_map();

   //ALLEGRO_FONT *font = obtain_font();
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 1080/2 - 30, ALLEGRO_ALIGN_CENTER, "Hello");
   return;
}

void Screen::game_event_func(AllegroFlare::GameEvent* game_event)
{
   if (!(game_event))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::game_event_func]: error: guard \"game_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::game_event_func]: error: guard \"game_event\" not met");
   }
   return;
}

void Screen::primary_update_func(double time_now, double delta_time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::primary_update_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::primary_update_func]: error: guard \"initialized\" not met");
   }
   // Update stuff here (take into account delta_time)
   //player_entity->aabb2d.set_velocity_x(player_entity->aabb2d.get_x() + 1.0);
   player_entity->aabb2d.set_velocity_x(2.0);

   update();
   return;
}

void Screen::primary_render_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::primary_render_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::primary_render_func]: error: guard \"initialized\" not met");
   }
   // Render stuff here
   render();
   return;
}

void Screen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   using namespace AllegroFlare;
   //if (!is_processing_user_input()) return;

   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_RIGHT)
   {
      //player_velocity.x = 1;
      //chapter_select_element.rotate_carousel_right();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_LEFT)
   {
      //player_velocity.x = -1;
      //chapter_select_element.rotate_carousel_left();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_A
      || virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_MENU
      )
   {
      //select_menu_option();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_X)
   {
      //exit_screen();
   }
   //call_on_finished_callback_func(); // Consider technique to exit
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

ALLEGRO_FONT* Screen::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -32");
}

void Screen::DEVELOPMENT__render_tile_map()
{
   AllegroFlare::TileMaps::TileMap<int> &tile_map = collision_tile_map;
   float tile_width=16.0f;
   float tile_height=16.0f;

   for (int y=0; y<tile_map.get_num_rows(); y++)
   {
      for (int x=0; x<tile_map.get_num_columns(); x++)
      {
         int tile_type = tile_map.get_tile(x, y);
         switch(tile_type)
         {
            case 0:
              //al_draw_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 //ALLEGRO_COLOR{0.2, 0.2, 0.21, 0.21}, 1.0);
            break;

            case 1:
              al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 ALLEGRO_COLOR{0.65, 0.62, 0.6, 1.0});
            break;

            default:
              //al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 //ALLEGRO_COLOR{0.8, 0.32, 0.4, 1.0});
            break;
         }
      }
   }
   return;
}

AllegroFlare::DialogTree::NodeBank Screen::build_dialog_node_bank()
{
   AllegroFlare::DialogTree::NodeBank result;

   std::string LOLLIE = "Lollie";

   result.set_nodes({
      { "pickup_apple", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
            LOLLIE,
            {
               "This is perfect! I just found an essential ingredient for our party!"
            },
            {
               { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            }
         )
      },
   });

   return result;
}


} // namespace Gameplay
} // namespace TINS2025


