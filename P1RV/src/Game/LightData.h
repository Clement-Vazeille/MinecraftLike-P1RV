#pragma once
#include <unordered_map>
#include "Maths/Vector2I.h"
#include "Maths/Vector3I.h"
#include <glm/glm.hpp>
struct LightData
{
	Vector2I chunkPosition;
	Vector3I sourcePosition; //coordonnées dans le repère du chunk
	glm::vec3 lightColor;
};