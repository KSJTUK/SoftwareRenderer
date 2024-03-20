#pragma once

class GameFramework {
public:
	GameFramework();
	~GameFramework();

public:
	void OnCreate(HINSTANCE hInst, HWND hWnd);
	void OnDesroy();

	void BuildObjects();

	void ProcessInput();
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void CreateFrameBuffers();
	void ClearFrameBuffer(DWORD dwColor);
	void PresentFrameBuffer();

	void FrameAdvance();

private:
	HINSTANCE	m_hInstance{ nullptr };
	HWND		m_hWnd{ nullptr };
	RECT		m_rcClient{ };

	HDC			m_hDCPrimary{ nullptr };
	HDC			m_hDCFrameBuffer{ nullptr };
	HBITMAP		m_hBmpFrameBuffer{ nullptr };

	std::unique_ptr<class Timer> m_timer{ };
	std::unique_ptr<class TestSimpleRectMesh> m_renderingTestMesh{ };
	std::unique_ptr<class Camera> m_mainCamera{ };
};