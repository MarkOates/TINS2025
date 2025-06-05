#pragma once


#include <lib/nlohmann/json.hpp>
#include <TINS2025/GameProgressAndStateInfo.hpp>


namespace TINS2025
{
  void to_json(nlohmann::json& j, const GameProgressAndStateInfo& object);
  void from_json(const nlohmann::json& j, GameProgressAndStateInfo& object);
}


