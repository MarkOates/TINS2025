
#include <gtest/gtest.h>

#include <TINS2025/GameProgressAndStateInfo.hpp>


TEST(TINS2025_GameProgressAndStateInfoTest, can_be_created_without_blowing_up)
{
   TINS2025::GameProgressAndStateInfo game_progress_and_state_info;
}


TEST(TINS2025_GameProgressAndStateInfoTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "TINS2025/GameProgressAndStateInfo",
     TINS2025::GameProgressAndStateInfo::TYPE
   );
}


TEST(TINS2025_GameProgressAndStateInfoTest, type__has_the_expected_value_matching_TYPE)
{
   TINS2025::GameProgressAndStateInfo game_progress_and_state_info;
   EXPECT_EQ(TINS2025::GameProgressAndStateInfo::TYPE, game_progress_and_state_info.get_type());
}


