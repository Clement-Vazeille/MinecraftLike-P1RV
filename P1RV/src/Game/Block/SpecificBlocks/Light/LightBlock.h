#pragma once
#include "../../Block.h"
class LightBlock :
    public Block
{
protected:
    glm::vec3 color;
public:
    LightBlock(int i, int j, int k);

    bool isLight(void) const override;
    const glm::vec3 getColor(void) const;

};

