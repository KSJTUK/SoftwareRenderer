#pragma once

class Mesh {
public:
	Mesh(size_t nPolygons);
	virtual ~Mesh();

private:
	static void Draw2DLine(HDC hDCFrameBuffer, DirectX::XMFLOAT3& prevProject, DirectX::XMFLOAT3& curProject);

public:
	void SetPolygon(size_t index, class Poly* polygon);

	virtual void Render(HDC hDCFrameBuffer);

private:
	size_t m_nPolygons{ };
	class Poly** m_polygons{ };
};

// --------------------------------------------------------------------------------------
class TestSimpleRectMesh : public Mesh {
public:
	TestSimpleRectMesh(float width=4.0f, float height=4.0f);
	~TestSimpleRectMesh();
};