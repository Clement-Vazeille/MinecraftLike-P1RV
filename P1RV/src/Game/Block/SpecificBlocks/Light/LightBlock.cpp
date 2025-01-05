#include "LightBlock.h"

LightBlock::LightBlock(int i, int j, int k) : Block(i,j,k)
{
}

bool LightBlock::isLight(void) const
{
    return true;
}

const glm::vec3 LightBlock::getColor(void) const
{
    return color;
}
