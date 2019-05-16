
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
  this->colour = colour;
  this->shape = shape;
}

Colour Tile::getColour()
{
  return this->colour;
}

Shape Tile::getShape()
{
  return this->shape;
}

void Tile::printTile()
{
  // double f = shape;
 std::cout << colour << shape;
 
}
