//
// Created by Vlad Boroday on 2024-12-31.
//

#ifndef UNTITLED4_SPATIAL_H
#define UNTITLED4_SPATIAL_H

#include "includes.h"
#include "raymath.h"

class Spatial
{
public:
	Matrix Translation;

	Vector3 Forward() const
	{
		Vector3 _;
		Quaternion rotation;
		Vector3 scale;
		MatrixDecompose(Translation, &_, &rotation, &scale);
		glm::quat glmRotation{ rotation.w, rotation.x, rotation.y, rotation.z };
		glm::mat3 directions = glm::mat3_cast(glmRotation);

		// Extract directions
		glm::vec3 forward = -directions[2]; // Negative Z-axis in local space

		// Apply scaling
		forward *= scale.z;

		// Normalize directions (optional, depending on your needs)
		forward = glm::normalize(forward);

		return { forward.x, forward.y, forward.z };
	}

	Vector3 Left() const
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		MatrixDecompose(Translation, &position, &rotation, &scale);
		glm::quat glmRotation{ rotation.x, rotation.y, rotation.z, rotation.w };
		glm::mat3 directions = glm::mat3_cast(glmRotation);

		// Extract directions
		glm::vec3 left = -directions[0]; // Negative X-axis in local space

		// Apply scaling
		left *= scale.x;

		// Normalize directions (optional, depending on your needs)
		left = glm::normalize(left);

		return { left.x, left.y, left.z };
	}

	Vector3 Up() const
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		MatrixDecompose(Translation, &position, &rotation, &scale);
		glm::quat glmRotation{ rotation.x, rotation.y, rotation.z, rotation.w };
		glm::mat3 directions = glm::mat3_cast(glmRotation);

		// Extract directions
		glm::vec3 up = directions[1]; // Positive Y-axis in local space

		// Apply scaling
		up *= scale.y;

		// Normalize directions (optional, depending on your needs)
		up = glm::normalize(up);

		return { up.x, up.y, up.z };
	}

	Vector3 Position() const
	{
		Vector3 position;
		Quaternion _;
		Vector3 __;
		MatrixDecompose(Translation, &position, &_, &__);

		return position;
	}

	Quaternion Rotation() const
	{
		Vector3 _;
		Quaternion quat;
		Vector3 __;
		MatrixDecompose(Translation, &_, &quat, &__);

		return quat;
	}

	Vector3 RotationAngles() const
	{
		Vector3 _;
		Quaternion quat;
		Vector3 __;
		MatrixDecompose(Translation, &_, &quat, &__);

		return QuaternionToEuler(quat);
	}
};


#endif //UNTITLED4_SPATIAL_H
