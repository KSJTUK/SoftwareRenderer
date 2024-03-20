#pragma once

class Mesh {
public:
	Mesh(size_t nPolygons);
	virtual ~Mesh();

private:
	static void Draw2DLine(HDC hDCFrameBuffer, DirectX::XMFLOAT3& prevProject, DirectX::XMFLOAT3& curProject);

public:
	void SetPolygon(size_t index, class Poly* polygon);

	virtual void Render(const HDC hDCFrameBuffer);

private:
	size_t m_nPolygons{ };
	class Poly** m_polygons{ };
};

// --------------------------------------------------------------------------------------
class CubeMesh : public Mesh {
public:
	CubeMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f);
	virtual ~CubeMesh() { }
};