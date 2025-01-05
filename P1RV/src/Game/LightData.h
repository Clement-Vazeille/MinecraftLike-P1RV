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

	/*bool operator== (const LightData& param) const {
		return (chunkPosition == param.chunkPosition) && (sourcePosition == param.sourcePosition) && (lightColor == param.lightColor);
	}

	struct HashFunction
	{
		size_t operator()(const LightData& lightData) const
		{
			return std::hash<int>()(lightData.sourcePosition.getX());
		}
	};*/
};