#pragma once


#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/GameConfigurations/Complete.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/Levels/Base.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <AllegroFlare/Runners/Complete.hpp>
#include <AllegroFlare/SavingAndLoading/SavingAndLoading.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/Screens/Subscreen/Screen.hpp>
#include <AllegroFlare/Screens/TitledMenuScreen.hpp>
#include <DialControl/Gameplay/Screen.hpp>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace DialControl
{
   namespace Game
   {
      namespace Configurations
      {
         class Main : public AllegroFlare::GameConfigurations::Complete
         {
         public:
            static constexpr char* TYPE = (char*)"DialControl/Game/Configurations/Main";

         private:
            DialControl::Gameplay::Screen* primary_gameplay_screen;
            AllegroFlare::Screens::Subscreen::Screen* primary_gameplay_subscreen;
            AllegroFlare::Screens::TitledMenuScreen* pause_screen;

         protected:


         public:
            Main();
            virtual ~Main();

            virtual std::string app_icon_1024_filename() override;
            virtual std::string app_title() override;
            virtual std::string title_screen_title() override;
            virtual std::string primary_display_icon_filename() override;
            virtual int get_num_save_profiles() override;
            virtual int get_num_manual_save_slots() override;
            virtual int get_num_autosave_save_slots() override;
            virtual int get_num_quicksave_save_slots() override;
            virtual AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle get_saving_and_loading_start_style() override;
            virtual AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle get_saving_and_loading_save_style() override;
            virtual AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle get_saving_and_loading_load_style() override;
            virtual std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> build_achievements() override;
            virtual AllegroFlare::Screens::Gameplay* create_primary_gameplay_screen(AllegroFlare::Runners::Complete* runner=nullptr) override;
            virtual void destroy_primary_gameplay_screen() override;
            virtual void load_save_file_content_into_gameplay(std::string save_file_content="[unset-save_file_content]") override;
            virtual std::string build_save_file_content_for_current_game() override;
            virtual void handle_save_file_loading_finished() override;
            virtual AllegroFlare::Screens::Subscreen::Screen* create_primary_gameplay_subscreen(AllegroFlare::Runners::Complete* runner=nullptr) override;
            virtual AllegroFlare::Screens::Base* create_pause_screen(AllegroFlare::Runners::Complete* runner=nullptr) override;
            virtual void destroy_pause_screen() override;
            virtual void handle_primary_gameplay_screen_paused() override;
            virtual void handle_primary_gameplay_screen_unpaused() override;
            virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_logos_storyboard_pages() override;
            virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_storyboard_pages() override;
            virtual void handle_arbitrary_storyboard_screen_finished() override;
            virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_arbitrary_storyboard_pages_by_identifier(std::string identifier="[unset-identifier]") override;
            virtual std::vector<std::pair<std::string, std::string>> build_title_screen_menu_options() override;
            virtual void load_audio_controller(AllegroFlare::AudioController* audio_controller=nullptr) override;
            virtual void load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session=nullptr) override;
            virtual AllegroFlare::GameProgressAndStateInfos::Base* create_game_progress_and_state_info_saver_loader() override;
            virtual void setup_new_game_progress_and_state_info_DEPRECATED(AllegroFlare::GameSession* game_session=nullptr) override;
            virtual std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> build_save_slots_for_load_a_saved_game_screen() override;
            virtual void handle_game_event(AllegroFlare::GameEvent* game_event=nullptr) override;
            void continue_from_last_save();
            virtual std::vector<std::pair<std::string, std::string>> build_level_list_for_level_select_screen_by_identifier(std::string identifier="[unset-identifier]") override;
            virtual AllegroFlare::DialogTree::NodeBank build_dialog_bank_by_identifier(std::string identifier="[identifier-discarded]") override;
            virtual AllegroFlare::Levels::Base* load_level_by_identifier(std::string identifier="[unset-identifier]") override;
         };
      }
   }
}



