
#include <gtest/gtest.h>

#include <TINS2025/Testing/Comparison/TINS2025/GameProgressAndStateInfo.hpp>


TEST(AllegroFlare_Testing_Comparison_TINS2025_GameProgressAndStateInfoTest,
   PrintTo__with_an_AllegroFlare_GameProgressAndStateInfo__will_output_as_expected)
{
   std::stringstream ss;
   TINS2025::GameProgressAndStateInfo object;
   object.set_player_inventory_items({ "fruit", "veggie", "fork" });
   object.set_player_num_lives(7);

   PrintTo(object, &ss);

   std::string expected_output =
      "GameProgressAndStateInfo(player_inventory_items: {\"fruit\", \"veggie\", \"fork\", }, "
        "player_num_lives: 7, )";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_TINS2025_GameProgressAndStateInfoTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   TINS2025::GameProgressAndStateInfo object;
   TINS2025::GameProgressAndStateInfo other_object;

   EXPECT_EQ(object, other_object);
}


