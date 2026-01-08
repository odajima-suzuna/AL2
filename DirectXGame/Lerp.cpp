#include "Lerp.h"

KamataEngine::Vector3 Lerp(KamataEngine::Vector3& translation, KamataEngine::Vector3& targetTranslation, float interpolationRate) {
	KamataEngine::Vector3 result;

	result.x = (1.0f - interpolationRate) * translation.x + interpolationRate * targetTranslation.x;
	result.y = (1.0f - interpolationRate) * translation.y + interpolationRate * targetTranslation.y;
	result.z = (1.0f - interpolationRate) * translation.z + interpolationRate * targetTranslation.z;

	return result;
}