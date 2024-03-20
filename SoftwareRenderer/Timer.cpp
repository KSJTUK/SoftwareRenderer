#include "pch.h"
#include "Timer.h"

Timer::Timer() {
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_performanceFrequencyPerSec));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_lastPerformanceCounter));
	m_timeScale = 1.0 / static_cast<double>(m_performanceFrequencyPerSec);

	m_basePerformanceCounter = m_lastPerformanceCounter;
}

Timer::~Timer() { }

ULONG Timer::GetFrameRate(std::wstring& wstr) {
	wstr = _T("FPS: ") + std::to_wstring(m_currentFrameRate);

	return m_currentFrameRate;
}

float Timer::GetTimeElapsed() {
	return m_timeElapsed;
}

float Timer::GetTotalTime() {
	if (m_stopped) 
		return(static_cast<float>(((m_stopPerformanceCounter - m_pausePerformanceCounter) - m_basePerformanceCounter) * m_timeScale));

	return(static_cast<float>(((m_currentPerformanceCounter - m_pausePerformanceCounter) - m_basePerformanceCounter) * m_timeScale));
}

void Timer::Tick(float lockFPS) {
	if (m_stopped) {
		m_timeElapsed = 0.0f;
		return;
	}
	float timeElapsed;

	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_currentPerformanceCounter));
	timeElapsed = static_cast<float>((m_currentPerformanceCounter - m_lastPerformanceCounter) * m_timeScale);

	if (lockFPS > 0.0f) {
		while (timeElapsed < (1.0f / lockFPS)) {
			::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_currentPerformanceCounter));
			timeElapsed = static_cast<float>((m_currentPerformanceCounter - m_lastPerformanceCounter) * m_timeScale);
		}
	}

	m_lastPerformanceCounter = m_currentPerformanceCounter;

	if (fabsf(timeElapsed - m_timeElapsed) < 1.0f) {
		::memmove(&m_frameTime[1], m_frameTime.data(), (MAX_SAMPLE_COUNT - 1) * sizeof(float));
		m_frameTime[0] = timeElapsed;
		if (m_sampleCount < MAX_SAMPLE_COUNT) 
			++m_sampleCount;
	}

	++m_fps;
	m_fpsTimeElapsed += timeElapsed;
	if (m_fpsTimeElapsed > 1.0f) {
		m_currentFrameRate = m_fps;
		m_fps = 0;
		m_fpsTimeElapsed = 0.0f;
	}

	m_timeElapsed = 0.0f;
	for (decltype(m_sampleCount) i = 0; i < m_sampleCount; i++) 
		m_timeElapsed += m_frameTime[i];

	if (m_sampleCount > 0) 
		m_timeElapsed /= m_sampleCount;
}

void Timer::Reset() {
	INT64 performanceCounter{ };
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&performanceCounter));

	m_basePerformanceCounter = performanceCounter;
	m_lastPerformanceCounter = performanceCounter;
	m_stopPerformanceCounter = 0;
	m_stopped = false;
}

void Timer::Start() {
	INT64 performanceCounter;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&performanceCounter));
	if (m_stopped) {
		m_pausePerformanceCounter += (performanceCounter - m_stopPerformanceCounter);
		m_lastPerformanceCounter = performanceCounter;
		m_stopPerformanceCounter = 0;
		m_stopped = false;
	}
}

void Timer::Stop() {
	if (!m_stopped) {
		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_stopPerformanceCounter));
		m_stopped = true;
	}
}
