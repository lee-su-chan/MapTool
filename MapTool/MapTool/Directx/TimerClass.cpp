#include "TimerClass.h"

TimerClass::TimerClass()
{
}

TimerClass::TimerClass(const TimerClass &other)
{
}

TimerClass::~TimerClass()
{
}

bool TimerClass::Initialize()
{
	INT64 frequency;

	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	
	if (frequency == 0)
		return false;

	m_frequency = (float)frequency;

	QueryPerformanceCounter((LARGE_INTEGER *)&m_startTime);

	return true;
}

void TimerClass::Frame()
{
	INT64 currentTime;
	INT64 elapsedTicks;

	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);

	elapsedTicks = currentTime - m_startTime;
	m_frameTime = (float)elapsedTicks / m_frequency;
	m_startTime = currentTime;

	return;
}

float TimerClass::GetTime()
{
	return m_frameTime;
}

void TimerClass::StartTimer()
{
	QueryPerformanceCounter((LARGE_INTEGER *)&m_beginTime);

	return;
}

void TimerClass::StopTimer()
{
	QueryPerformanceCounter((LARGE_INTEGER *)&m_endTime);

	return;
}

int TimerClass::GetTiming()
{
	float elapsedTicks;
	INT64 frequency;
	float milliseconds;

	elapsedTicks = (float)(m_endTime - m_beginTime);

	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	milliseconds = (elapsedTicks / (float)frequency) * 1000.0f;

	return (int)milliseconds;
}