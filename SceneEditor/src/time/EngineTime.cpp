#include "time/EngineTime.h"

double EngineTime::getDeltaTime()
{
	return this->m_deltaTime;
}

void EngineTime::logFrameStart()
{
	this->m_start = std::chrono::system_clock::now();
}

void EngineTime::logFrameEnd()
{
	this->m_end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = this->m_end - this->m_start;
	this->m_deltaTime = elapsed_seconds.count();
}
