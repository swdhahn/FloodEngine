#include "Logger.h"

void engine::logErrorAndCrash(const std::string& message) {

#ifdef _WIN32
	/*int len;
	int slength = message.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, message.c_str(), slength, 0, 0);
	auto buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, message.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	LPCWSTR sw = r.c_str();*/
	MessageBox(NULL, message.c_str(), "Crash Error!", MB_OK);
#endif // _WIN32

    logError(message);

	std::exit(-1);
}

void engine::logError(const std::string& message) {
	std::cerr << "[" << getElapsedTime() <<"][Error]\t" << message << std::endl;
}

void engine::logInfo(const std::string& message) {
	std::cout << "[" << getElapsedTime() << "][Info]\t" << message << std::endl;
}

void engine::logWarning(const std::string& message) {
	std::cout << "[" << getElapsedTime() << "][Warn]\t" << message << std::endl;
}

