#pragma once


#include <TINS2025/GameProgressAndStateInfo.hpp>
#include <ostream>


namespace TINS2025
{
   bool operator==(const GameProgressAndStateInfo& object, const GameProgressAndStateInfo& other_object);
   bool operator!=(const GameProgressAndStateInfo& object, const GameProgressAndStateInfo& other_object);
   void PrintTo(const GameProgressAndStateInfo& object, ::std::ostream* os);
}


