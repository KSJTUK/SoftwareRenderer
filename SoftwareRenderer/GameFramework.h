#pragma once

class GameFramework {
public:
	void OnCreate(HINSTANCE hInst, HWND hWnd);
	void OnDesroy();

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

	HDC			m_hDCFrameBuffer{ nullptr };
	HBITMAP		m_hBmpFrameBuffer{ nullptr };
	HBITMAP		m_hBmpSelect{ nullptr };
};