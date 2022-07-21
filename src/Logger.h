#ifndef FLOODENGINE_LOGGER_H
#define FLOODENGINE_LOGGER_H

#include <stdexcept>
#include <stdlib.h>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32



#include "Utils.h"

namespace engine {

	void logErrorAndCrash(const std::string& message);
	void logError(const std::string& message);
	void logInfo(const std::string& message);
	void logWarning(const std::string& message);

}

#endif // FLOODENGINE_LOGGER_H