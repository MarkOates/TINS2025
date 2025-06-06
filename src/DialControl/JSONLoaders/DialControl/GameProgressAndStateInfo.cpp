

#include <DialControl/JSONLoaders/DialControl/GameProgressAndStateInfo.hpp>

#include <AllegroFlare/Logger.hpp>


namespace DialControl
{


void to_json(nlohmann::json& j, const GameProgressAndStateInfo& v)
{
   j = nlohmann::json{
      { "player_inventory_items", v.get_player_inventory_items() },
      { "player_num_lives", v.get_player_num_lives() },
   };
}


void from_json(const nlohmann::json& j, GameProgressAndStateInfo& v)
{
   // player_inventory_items
   if (!j.contains("player_inventory_items"))
   {
      AllegroFlare::Logger::throw_error(
         "When loading JSON, expecting to find \"player_inventory_items\" but it does not exist."
      );
   }
   j.at("player_inventory_items").get_to(v.get_player_inventory_items_ref());

   // player_num_lives
   if (!j.contains("player_num_lives"))
   {
      AllegroFlare::Logger::throw_error(
         "When loading JSON, expecting to find \"player_num_lives\" but it does not exist."
      );
   }
   j.at("player_num_lives").get_to(v.get_player_num_lives_ref());
}


} // namespace DialControl


