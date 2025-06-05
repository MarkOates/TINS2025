

#include <TINS2025/Gameplay/Level.hpp>




namespace TINS2025
{
namespace Gameplay
{


Level::Level()
   : AllegroFlare::Levels::Base(TINS2025::Gameplay::Level::TYPE)
   , title("[unset-title]")
{
}


Level::~Level()
{
}


void Level::set_title(std::string title)
{
   this->title = title;
}


std::string Level::get_title() const
{
   return title;
}




} // namespace Gameplay
} // namespace TINS2025


