#pragma once

const ULONG MAX_SAMPLE_COUNT = 50; // Maximum frame time sample count

class Timer {
public:
	Timer();
	~Timer();

public:
	unsigned long GetFrameRate(std::wstring& wstr);
	float GetTimeElapsed();
	float GetTotalTime();

public:
	void Tick(float lockFPS = 0.0f);
	void Start();
	void Stop();
	void Reset();

private:
	double								m_timeScale{ };
	float								m_timeElapsed{ };

	INT64								m_basePerformanceCounter{ };
	INT64								m_pausePerformanceCounter{ };
	INT64								m_stopPerformanceCounter{ };
	INT64								m_currentPerformanceCounter{ };
	INT64								m_lastPerformanceCounter{ };

	INT64								m_performanceFrequencyPerSec{ };

	std::array<float, MAX_SAMPLE_COUNT>	m_frameTime{ };
	ULONG								m_sampleCount{ };

	ULONG						m_currentFrameRate{ };
	ULONG						m_fps{ };
	float								m_fpsTimeElapsed{ };

	bool								m_stopped{ };
};
