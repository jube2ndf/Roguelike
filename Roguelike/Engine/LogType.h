#pragma once
#include "EngineAPI.h"

namespace GameEngine {
	enum class ENGINE_API LogType
	{
		INFO = 0,

		WARNING,
		ERROR,
		FATAL,
	};
}