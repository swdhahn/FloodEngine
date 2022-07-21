#include "Utils.h"

float engine::getElapsedTimeMillis() {
	return ((float)clock()) / CLOCKS_PER_SEC * 1000;
}

float engine::getElapsedTime() {
	return ((float)clock()) / CLOCKS_PER_SEC;
}
