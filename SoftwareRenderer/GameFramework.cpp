#include "pch.h"
#include "GameFramework.h"
#include "Timer.h"
#include "Mesh.h"
#include "Camera.h"
#include "GraphicsPipeline.h"

GameFramework::GameFramework() { }

GameFramework::~GameFramework() { }

void GameFramework::OnCreate(HINSTANCE hInst, HWND hWnd) {
	m_hInstance = hInst;
	m_hWnd = hWnd;

	CreateFrameBuffers();
	BuildObjects();
}

void GameFramework::OnDesroy() {
	// Release Objects
	if (m_hBmpFrameBuffer) ::DeleteObject(m_hBmpFrameBuffer);
	if (m_hDCFrameBuffer) ::DeleteDC(m_hDCFrameBuffer);
	::ReleaseDC(m_hWnd, m_hDCPrimary);
}

void GameFramework::BuildObjects() {
	m_timer = std::make_unique<Timer>();
	m_renderingTestMesh = std::make_unique<TestSimpleRectMesh>();
	m_mainCamera = std::make_unique<Camera>();
	m_mainCamera->SetViewport(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	m_mainCamera->GeneratePerspectiveProjectionMatrix(1.0f, 500.f, 60.0f);
	m_mainCamera->SetFOVAngle(60.0f);
}

void GameFramework::ProcessInput() {

}

void GameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	switch (nMessageID) {
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		break;

	default:
		break;
	}
}

void GameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	switch (nMessageID) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			::PostQuitMessage(0);
			break;

		case VK_RETURN:
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

LRESULT CALLBACK GameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	switch (nMessageID) {
	case WM_SIZE:
		break;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}

	return(0);
}

void GameFramework::CreateFrameBuffers() {
	::GetClientRect(m_hWnd, &m_rcClient);

	//HDC hDC{ ::GetDC(m_hWnd) };
	m_hDCPrimary = ::GetDC(m_hWnd);
	m_hDCFrameBuffer = ::CreateCompatibleDC(m_hDCPrimary);
	m_hBmpFrameBuffer = ::CreateCompatibleBitmap(m_hDCPrimary, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top);
	::SelectObject(m_hDCFrameBuffer, m_hBmpFrameBuffer);

	//::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void GameFramework::ClearFrameBuffer(DWORD dwColor) {
	HPEN hPen = ::CreatePen(PS_SOLID, 0, dwColor);
	HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);

	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);

	::Rectangle(m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);

	::SelectObject(m_hDCFrameBuffer, hOldBrush);
	::SelectObject(m_hDCFrameBuffer, hOldPen);

	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}

void GameFramework::PresentFrameBuffer() {
	HDC hDC = ::GetDC(m_hWnd);
	::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);
}

void GameFramework::FrameAdvance() {
	m_timer->Tick(0.0f); // 0.0f is no limits

	ProcessInput();

	ClearFrameBuffer(RGB(90, 103, 224));

	// Rendering Code
	// Mesh Rendering Test

	m_mainCamera->Move(DirectX::XMFLOAT3{ 0.f, 0.f, 0.001f });
	m_mainCamera->Rotate(0.f, 0.f, 0.02f);
	m_mainCamera->GenerateViewMatrix();

	DirectX::XMFLOAT4X4 w{ Matrix4x4::Identity() };
	GraphicsPipeline::SetWorldTransform(&w);
	GraphicsPipeline::SetViewport(&m_mainCamera->m_viewport);
	GraphicsPipeline::SetViewPerspectiveProjectTransform(&m_mainCamera->m_viewPerspectiveProject);

	HPEN hPen = ::CreatePen(PS_SOLID, 0, RGB(0xff, 0xff, 0x00));
	HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);

	m_renderingTestMesh->Render(m_hDCFrameBuffer);

	::SelectObject(m_hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);

	PresentFrameBuffer();

	std::wstring testWindowText{ };
	m_timer->GetFrameRate(testWindowText);
	::SetWindowText(m_hWnd, testWindowText.c_str());
}
