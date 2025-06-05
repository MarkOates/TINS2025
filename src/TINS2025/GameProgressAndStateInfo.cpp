

#include <TINS2025/GameProgressAndStateInfo.hpp>

#include <TINS2025/JSONLoaders/TINS2025/GameProgressAndStateInfo.hpp>


namespace TINS2025
{


GameProgressAndStateInfo::GameProgressAndStateInfo()
   : AllegroFlare::GameProgressAndStateInfos::Base(TINS2025::GameProgressAndStateInfo::TYPE)
   , player_num_lives(0)
   , player_inventory_items({})
{
}


GameProgressAndStateInfo::~GameProgressAndStateInfo()
{
}


void GameProgressAndStateInfo::set_player_num_lives(int player_num_lives)
{
   this->player_num_lives = player_num_lives;
}


void GameProgressAndStateInfo::set_player_inventory_items(std::vector<std::string> player_inventory_items)
{
   this->player_inventory_items = player_inventory_items;
}


int GameProgressAndStateInfo::get_player_num_lives() const
{
   return player_num_lives;
}


std::vector<std::string> GameProgressAndStateInfo::get_player_inventory_items() const
{
   return player_inventory_items;
}


int &GameProgressAndStateInfo::get_player_num_lives_ref()
{
   return player_num_lives;
}


std::vector<std::string> &GameProgressAndStateInfo::get_player_inventory_items_ref()
{
   return player_inventory_items;
}


void GameProgressAndStateInfo::add_player_inventory_item(std::string item_identifier)
{
   player_inventory_items.push_back(item_identifier);
}

std::string GameProgressAndStateInfo::export_to_string()
{
   nlohmann::json j = *this;
   std::string string_dump = j.dump(2);
   return string_dump;
}

void GameProgressAndStateInfo::import_from_string(std::string data_string)
{
   nlohmann::json parsed_json = nlohmann::json::parse(data_string);
   parsed_json.get_to(*this);
}


} // namespace TINS2025


