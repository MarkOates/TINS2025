#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <DialControl/CameraInfo.hpp>
#include <allegro5/allegro.h>
#include <lib/nlohmann/json.hpp>
#include <string>
#include <vector>


namespace DialControl
{
   class CameraStudio
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::vector<AllegroFlare::Camera3D> cameras;
      std::vector<DialControl::CameraInfo> cameras_;
      int current_camera_idx;
      AllegroFlare::Camera3D* current_camera;
      AllegroFlare::Camera3D live_camera;
      AllegroFlare::Camera2D hud_camera;
      bool camera_info_overlay_visible;
      float live_camera_blend_factor;
      float clip_plane_near_min;
      float clip_plane_near_max;
      float clip_plane_far_min;
      float clip_plane_far_max;
      float clip_plane_increment;
      bool initialized;
      void handle_key_down(ALLEGRO_EVENT* event=nullptr);

   protected:


   public:
      CameraStudio();
      ~CameraStudio();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_cameras(std::vector<AllegroFlare::Camera3D> cameras);
      void set_cameras_(std::vector<DialControl::CameraInfo> cameras_);
      void set_current_camera(AllegroFlare::Camera3D* current_camera);
      void set_live_camera_blend_factor(float live_camera_blend_factor);
      void set_clip_plane_near_min(float clip_plane_near_min);
      void set_clip_plane_near_max(float clip_plane_near_max);
      void set_clip_plane_far_min(float clip_plane_far_min);
      void set_clip_plane_far_max(float clip_plane_far_max);
      void set_clip_plane_increment(float clip_plane_increment);
      std::vector<AllegroFlare::Camera3D> get_cameras() const;
      std::vector<DialControl::CameraInfo> get_cameras_() const;
      AllegroFlare::Camera3D* get_current_camera() const;
      float get_live_camera_blend_factor() const;
      float get_clip_plane_near_min() const;
      float get_clip_plane_near_max() const;
      float get_clip_plane_far_min() const;
      float get_clip_plane_far_max() const;
      float get_clip_plane_increment() const;
      bool get_initialized() const;
      AllegroFlare::Camera3D &get_live_camera_ref();
      void initialize();
      void update();
      void setup_projection_on_live_camera();
      void setup_projection_on_hud_camera();
      void toggle_camera_info_overlay_visibility();
      void show_camera_info_overlay();
      void hide_camera_info_overlay();
      void draw_camera_info_overlay();
      void set_current_camera_to_next_camera();
      void set_current_camera_to_previous_camera();
      void on_key_char(ALLEGRO_EVENT* event=nullptr);
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
      std::string build_json_dump();
      nlohmann::json build_json();
      void load_json(std::string json_string="[unset-json_string]");
      void move_far_plane_further();
      void move_far_plane_nearer();
      void move_near_plane_further();
      void move_near_plane_nearer();
   };
}



