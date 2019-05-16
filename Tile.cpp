
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
  colour = colour;
  shape = shape;
}

Colour Tile::getColour()
{
  return this->colour;
}

Shape Tile::getShape()
{
  return this->shape;
}

std::string Tile::printTile()
{
  // double f = shape;
  std::string create = this->colour + std::to_string(this->shape);


  
  return create;
}
