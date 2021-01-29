#pragma once
#include <chrono>

class EngineTime
{
public:
	double getDeltaTime();
	void logFrameStart();
	void logFrameEnd();

private:
	std::chrono::system_clock::time_point m_start;
	std::chrono::system_clock::time_point m_end;
	double m_deltaTime = 0.0;
};
