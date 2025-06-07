

#include <TINS2025/Gameplay/Screen.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/PlayerInputControllers/Generic.hpp>
#include <AllegroFlare/Tiled/TMJDataLoader.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <TINS2025/Gameplay/Level.hpp>
#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <cmath>
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
   , hide_view_motion_studio_hud(false)
   , current_level_identifier("[unset-current_level]")
   , current_level(nullptr)
   , collision_observer({})
   , collision_tile_map({})
   , environment_overlay_placement()
   , entities({})
   , environment_model(nullptr)
   , player_entity(nullptr)
   , input_mode(0)
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
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
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


   // Load up the world model
   collision_tile_map.initialize();

   //environment_model = model_bin->auto_get("simple_scene-03.obj");
   //environment_model->texture = bitmap_bin->auto_get("simple_scene-03.png");

   environment_overlay_placement.rotation.x = 0.25;
   environment_overlay_placement.position.y = 0.25;

   // Setup the tile map
   ////collision_tile_map.resize(1000, 1000);
   //collision_tile_map.initialize();
   //AllegroFlare::Tiled::TMJDataLoader tmj_data_loader;
   //tmj_data_loader.set_filename(data_folder_path + "maps/hello_friend-world_map-0n.tmj");
   //tmj_data_loader.load();

   ////get_tilelayers_tile_data
   //auto data = tmj_data_loader.get_tilelayer_data_by_name_as_2d_vector("collision");

   //collision_tile_map.resize(tmj_data_loader.get_num_columns(), tmj_data_loader.get_num_rows());
   //collision_tile_map.fill_with_data(data);

   //collision_tile_map.set_tile(69, 34, 1);


   // Setup the entities
   entities.reserve(256);

   Entity e;
   e.aabb2d.set_x(9.0);
   e.aabb2d.set_y(5.0);
   e.aabb2d.set_w(0.25);
   e.aabb2d.set_h(0.25);
   //e.sprite = bitmap_bin->auto_get("character_a-01.png");
   e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_TILEMAP;
   e.type = TINS2025::Entity::ENTITY_TYPE_PLAYER;
   e.model = model_bin->auto_get("character_model-01.obj");
   e.model->texture = bitmap_bin->auto_get("character_a-01.png");
   entities.push_back(e);

   player_entity = &entities.back();


   refresh_environment_and_world();


   // Setup the dialog
   dialog_system->set_dialog_node_bank(build_dialog_node_bank());
   dialog_system->set_standard_dialog_box_font_name("Quicksand-SemiBold.ttf");
   dialog_system->set_standard_dialog_box_font_size(-52);
   //dialog_system->set_standard_dialog_box_font_line_height(-52); // TODO: Add this feature
   dialog_system->set_standard_dialog_box_width(1920 * 0.5);
   dialog_system->set_standard_dialog_box_height(248);
   dialog_system->set_standard_dialog_box_y(1080/5*4);

   dialog_system->set_standard_dialog_box_frame_color(al_color_html("c6987e"));
   dialog_system->set_standard_dialog_box_background_color(al_color_html("fdf5e6"));
   dialog_system->set_standard_dialog_box_text_color(al_color_html("9f6b32"));
   dialog_system->set_standard_dialog_box_label_color(al_color_html("fdf5e6"));

   //dialog_system->set_standard_dialog_box_frame_color(al_color_html("6dbacc"));
   //dialog_system->set_standard_dialog_box_background_color(al_color_html("6dbacc"));
   //dialog_system->set_standard_dialog_box_text_color(al_color_html("000000"));
   //dialog_system->set_standard_dialog_box_label_color(al_color_html("000000"));


   // Setup view_motion_studio
   view_motion_studio.set_font_bin(font_bin);
   view_motion_studio.set_data_folder_path(data_folder_path);
   view_motion_studio.initialize();
   //view_motion_studio.load_json(cameras_json_string); // Load some test data
   // TODO: Fix these paths
   std::string filename_load = data_folder_path + "animations/camera_move_1-0n.txt";
   //std::string filename_save = "tests/fixtures/animations/camera_move_1-0n_output.txt";
   //std::cout << "loading json" << std::endl;
   std::string file_content = AllegroFlare::php::file_get_contents(filename_load);
   view_motion_studio.load_json(file_content);


   input_mode = INPUT_MODE_PLAYING;


   // Hide the view motion studio
   hide_view_motion_studio_hud = true;



   // Setup the player_input_controller
   auto generic_player_input_controller = new AllegroFlare::PlayerInputControllers::Generic();
   generic_player_input_controller->set_on_time_step_update(
      [this](AllegroFlare::Vec2D value, double time_now, double time_step) {
         //throw std::runtime_error("asdfasf");

         //player_entity->
         //auto player_box = frustum_viewer.find_first_box("player_box");
         //AllegroFlare::Camera3D &camera = frustum_viewer.get_camera_ref();

         // Simple:
         //player_box->position.x += value.x * 0.02;
         //player_box->position.z += value.y * 0.02;
         //player_entity->aabb2d.set_velocity_x(value.x * 0.02);
         //player_entity->aabb2d.set_velocity_y(value.y * 0.02);
         player_entity->aabb2d.set_velocity_x(value.x * 0.01625 * 2);
         player_entity->aabb2d.set_velocity_y(value.y * 0.01625 * 2);
         //player_entity->position.z += value.y * 0.02;

         // Relative to camera:
         //float angle = camera.spin;
         //float x_prime = value.x * std::cos(angle) - value.y * std::sin(angle);
         //float y_prime = value.x * std::sin(angle) + value.y * std::cos(angle);

         //player_entity->velocity.x = x_prime * 0.05;
         //player_box->velocity.z = y_prime * 0.05;
      }
   );
   set_player_input_controller(generic_player_input_controller);


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
         1.0f,
         1.0f
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
         TINS2025::Entity &entity = *static_cast<TINS2025::Entity*>(entered);
         if (entity.flags & TINS2025::Entity::FLAG_INACTIVE) continue;

         switch (entity.type)
         {
            case TINS2025::Entity::ENTITY_TYPE_APPLE:
               entity.flags |= TINS2025::Entity::FLAG_HIDDEN;
               entity.flags |= TINS2025::Entity::FLAG_INACTIVE;
               event_emitter->emit_activate_dialog_node_by_name_event("pickup_apple");
            break;

            case TINS2025::Entity::ENTITY_TYPE_FRIEND:
               event_emitter->emit_activate_dialog_node_by_name_event("enter_home");
            break;
         }
      }
   }

   // Update the view motion
   view_motion_studio.update();

   // Update the current camera to track the current player position
   view_motion_studio.get_camera_studio_ref().get_live_camera_ref().position.x = player_entity->aabb2d.get_x();
   view_motion_studio.get_camera_studio_ref().get_live_camera_ref().position.z = player_entity->aabb2d.get_y();

   return;
}

void Screen::render()
{
   view_motion_studio.setup_camera_projection_on_live_camera();

   AllegroFlare::Placement3D environment_model_displacement;
   environment_model_displacement.position.x = 0.5;
   environment_model_displacement.position.z = 0.5;
   environment_model_displacement.start_transform();
   environment_model->draw();
   environment_model_displacement.restore_transform();

   if (!hide_view_motion_studio_hud) DEVELOPMENT__render_tile_map();

   AllegroFlare::Placement3D placement;
   for (auto &entity : entities)
   {
      if (entity.flags & TINS2025::Entity::FLAG_INACTIVE) continue;
      if (entity.flags & TINS2025::Entity::FLAG_HIDDEN) continue;

      //entity.draw();
      placement.position.x = entity.aabb2d.get_x(); // + entity.aabb2d.get_w() * 0.5f;
      placement.position.z = entity.aabb2d.get_y(); // + entity.aabb2d.get_h() * 0.5;
      placement.position.y = 0;
      placement.scale.x = 1.0; // + entity.aabb2d.get_w() * 0.5f;
      placement.scale.y = 1.25; // + entity.aabb2d.get_w() * 0.5f;
      //placement.size.x = entity.aabb2d.get_w(); // + entity.aabb2d.get_w() * 0.5f;
      //placement.size.z = entity.aabb2d.get_h(); // + entity.aabb2d.get_h() * 0.5;
      /*
      //placement.size.x = entity.aabb2d.get_w(); // + entity.aabb2d.get_w() * 0.5f;
      //placement.size.z = entity.aabb2d.get_h(); // + entity.aabb2d.get_h() * 0.5;
      placement.size.y = 0;
      placement.align.x = 0.5;
      placement.align.z = 0.5;
      placement.align.y = 0;
      */

      placement.start_transform();
      entity.model->set_texture(entity.model->texture);
      entity.model->draw();
      if (!hide_view_motion_studio_hud)
      {
         al_draw_rectangle(0, 0, entity.aabb2d.get_w(), entity.aabb2d.get_h(), ALLEGRO_COLOR{1, 1, 1, 1}, 0.01);
      }
      placement.restore_transform();
   }

   //view_motion_studio.setup_camera_projection_on_live_camera();

   // Render the view motion hud
   if (!hide_view_motion_studio_hud) view_motion_studio.render_hud();
   //DEVELOPMENT__render_tile_map();
   //for (auto &entity : entities)
   //{
      //if ((entity.flags & TINS2025::Entity::FLAG_HIDDEN) == 0) entity.draw_bbox();
   //}
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
   //if (scripting) scripting->game_event_func(game_event);

   //if (game_event->is_type("trigger_central_core_cinematic"))
   //{
      //start_cinematic_camera("central_core_cinematic");
   //}
   if (game_event->is_type("win_game"))
   {
      call_on_finished_callback_func(); // Consider technique to exit
      // HERE
      
      //game_is_won();
      //toggle_player_input_controller_between_robot_and_player_if_available();
   }

   // game_configuration->handle_game_event(game_event);
   return;
   return;
}

void Screen::refresh_environment_and_world()
{
   // Clear out all the entities (non-character)
   entities.erase(
      std::remove_if(entities.begin(), entities.end(),
         [](const TINS2025::Entity &entity)
         {
            return entity.type != TINS2025::Entity::ENTITY_TYPE_PLAYER;
         }),
      entities.end()
   );


   // Clear the bitmap bin
   bitmap_bin->clear();


   // Relad the TMJ and refill the tile layer data
   AllegroFlare::Tiled::TMJDataLoader tmj_data_loader;
   tmj_data_loader.set_filename(data_folder_path + "maps/hello_friend-world_map-0n.tmj");
   tmj_data_loader.load();

   auto data = tmj_data_loader.get_tilelayer_data_by_name_as_2d_vector("collision");

   collision_tile_map.resize(tmj_data_loader.get_num_columns(), tmj_data_loader.get_num_rows());
   collision_tile_map.fill_with_data(data);


   tmj_data_loader.for_each_object([this](AllegroFlare::Tiled::TMJObject* object, void* user_data) {
      int tile_width = 16;
      int tile_height = 16;
      Entity e;
      e.aabb2d.set_x(object->x / (float)tile_width);
      e.aabb2d.set_y(object->y / (float)tile_height);
      e.aabb2d.set_w(1.0);
      e.aabb2d.set_h(1.0);
      e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_PLAYER;
      e.type = TINS2025::Entity::ENTITY_TYPE_FRIEND;
      //e.model = model_bin->auto_get("centered_unit_cube-02.obj");
      //e.model->texture = bitmap_bin->auto_get("simple_scene-03.png");
      e.model = model_bin->auto_get("character_model-01.obj");
      e.model->texture = bitmap_bin->auto_get("character_a-01.png");
      entities.push_back(e);
      
      //std::function<void(AllegroFlare::Tiled::TMJObject*, void*)> function={}, void* user_data=nullptr)
   });



   { // Add an "apple"
      Entity e;
      e.aabb2d.set_x(0 + 2);
      e.aabb2d.set_y(3.0);
      e.aabb2d.set_w(1.0);
      e.aabb2d.set_h(1.0);
      e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_PLAYER;
      e.type = TINS2025::Entity::ENTITY_TYPE_APPLE;
      e.model = model_bin->auto_get("centered_unit_cube-02.obj");
      e.model->texture = bitmap_bin->auto_get("simple_scene-03.png");
      entities.push_back(e);
   }

   { // Add a "building entry"
      Entity e;
      e.aabb2d.set_x(10.0);
      e.aabb2d.set_y(9.0);
      e.aabb2d.set_w(1.0);
      e.aabb2d.set_h(1.0);
      e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_PLAYER;
      e.type = TINS2025::Entity::ENTITY_TYPE_FRIEND;
      e.model = model_bin->auto_get("centered_unit_cube-02.obj");
      e.model->texture = bitmap_bin->auto_get("simple_scene-03.png");
      entities.push_back(e);
   }



   // Reload the environment model
   std::string model_filename = "hello_friend-environment-0n.obj";
   std::string image_filename = "hello_friend-environment-0n.png";

   model_bin->destroy(model_filename);
   bitmap_bin->destroy(image_filename);
   environment_model = model_bin->auto_get(model_filename);
   environment_model->texture = bitmap_bin->auto_get(image_filename);

   return;
}

void Screen::display_switch_in_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::display_switch_in_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::display_switch_in_func]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Screens::Gameplay::display_switch_in_func();

   refresh_environment_and_world();

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
   AllegroFlare::Screens::Gameplay::primary_update_func(time_now, delta_time);

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

void Screen::key_down_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::key_down_func]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::key_down_func]: error: guard \"ev\" not met");
   }
   // Process standard gameplay screen controls, which includes whatever active player_input_controller is
   // assigned to the Screens/Gameplay
   AllegroFlare::Screens::Gameplay::key_down_func(ev);

   bool shift = ev->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
   bool ctrl = ev->keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;

   if (ev->keyboard.keycode == ALLEGRO_KEY_BACKQUOTE)
   {
      // Toggle playmode
      if (input_mode == INPUT_MODE_PLAYING) input_mode = INPUT_MODE_EDITING;
      else if (input_mode == INPUT_MODE_EDITING) input_mode = INPUT_MODE_PLAYING;
   }
   else if (ev->keyboard.keycode == ALLEGRO_KEY_H)
   {
      hide_view_motion_studio_hud = !hide_view_motion_studio_hud;
   }
   else
   {
      switch (input_mode)
      {
         case INPUT_MODE_PLAYING:
         break;

         case INPUT_MODE_EDITING:
            view_motion_studio.on_key_down(ev);
         break;
      }
   }

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
   AllegroFlare::Placement3D tile_map_placement = environment_overlay_placement;
   float o = 0.25;
   tile_map_placement.rotation.x = 0.25;
   tile_map_placement.position.y = 0.25;

   AllegroFlare::TileMaps::TileMap<int> &tile_map = collision_tile_map;
   float tile_width=1.0f;
   float tile_height=1.0f;

   tile_map_placement.start_transform();
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
                 ALLEGRO_COLOR{0.94f*o, 0.42f*o, 0.8f*o, 1.0f*o});
            break;

            default:
              //al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 //ALLEGRO_COLOR{0.8, 0.32, 0.4, 1.0});
            break;
         }
      }
   }
   tile_map_placement.restore_transform();
   return;
}

AllegroFlare::DialogTree::NodeBank Screen::build_dialog_node_bank()
{
   AllegroFlare::DialogTree::NodeBank result;

   std::string LOTTIE = "Lottie";

   result.set_nodes({
      { "pickup_apple", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
            LOTTIE,
            {
               "This is perfect! I just found an essential ingredient for our party!"
            },
            {
               { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            }
         )
      },
      { "enter_home", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
            LOTTIE,
            {
               "I did it! What a party!"
            },
            {
               { "Win game", new AllegroFlare::DialogTree::NodeOptions::GoToNode("emit_win_game"), 0 },
            }
         )
      },
     //AllegroFlare::DialogTree::NodeOptions::GoToNode
      { "emit_win_game", new AllegroFlare::DialogTree::Nodes::EmitGameEvent("win_game", "exit_dialog") },
      { "exit_dialog", new AllegroFlare::DialogTree::Nodes::ExitDialog() },
            //LOTTIE,
            //{
               //"I did it! What a party!"
            //},
            //{
               //{ "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
               //{ "Win game", new AllegroFlare::DialogTree::Nodes::EmitGameEvent("win_game", "->mission_briefing") },
            //}
         //)
      //},
   });

   return result;
}


} // namespace Gameplay
} // namespace TINS2025


