#include "pch.h"
#include "Mesh.h"
#include "GraphicsPipeline.h"
#include "Utils.h"

Mesh::Mesh(size_t nPolygons) : m_nPolygons{ nPolygons } {
	m_polygons = new Poly*[m_nPolygons]{ };
}

Mesh::~Mesh() {
	if (!m_polygons) {
		return;
	}

	for (decltype(m_nPolygons) i = 0; i < m_nPolygons; ++i) {
		if (m_polygons[i]) {
			delete m_polygons[i];
		}
	}
	delete[] m_polygons;
	m_polygons = nullptr;
}

void Mesh::Draw2DLine(HDC hDCFrameBuffer, DirectX::XMFLOAT3& prevProject, DirectX::XMFLOAT3& curProject) {
		DirectX::XMFLOAT3 prev = GraphicsPipeline::ScreenTransform(prevProject);
		DirectX::XMFLOAT3 cur = GraphicsPipeline::ScreenTransform(curProject);
		::MoveToEx(hDCFrameBuffer, static_cast<int>(prev.x), static_cast<int>(prev.y), NULL);
		::LineTo(hDCFrameBuffer, static_cast<int>(cur.x), static_cast<int>(cur.y));
}

void Mesh::SetPolygon(size_t index, Poly* polygon) {
	if (0 > index or index >= m_nPolygons) exit(EXIT_FAILURE);
	if (!m_nPolygons) exit(EXIT_FAILURE);
	if (!polygon) return;

	m_polygons[index] = polygon;
}

void Mesh::Render(const HDC hDCFrameBuffer) {
	DirectX::XMFLOAT3 initProject{ }, prevProject{ };
	bool prevInside = false, initInside = false, curInside = false, intersectInside = false;

	for (decltype(m_nPolygons) j = 0; j < m_nPolygons; j++) {
		auto nVertices = m_polygons[j]->m_nVertices;
		Vertex* vertices = m_polygons[j]->m_vertices;

		prevProject = initProject = GraphicsPipeline::Project(vertices[0].position);
		prevInside = initInside = (-1.0f <= initProject.x) and (initProject.x <= 1.0f) and (-1.0f <= initProject.y) and (initProject.y <= 1.0f);
		for (decltype(nVertices) i = 1; i < nVertices; ++i) {
			DirectX::XMFLOAT3 curProject{ GraphicsPipeline::Project(vertices[i].position) };
			curInside = (-1.0f <= curProject.x) and (curProject.x <= 1.0f) and (-1.0f <= curProject.y) and (curProject.y <= 1.0f);

			if (((0.0f <= curProject.z) and (curProject.z <= 1.0f)) and ((curInside or prevInside))) 
				Mesh::Draw2DLine(hDCFrameBuffer, prevProject, curProject);

			prevProject = curProject;
			prevInside = curInside;
		}

		if (((0.0f <= initProject.z) and (initProject.z <= 1.0f)) and ((initInside or prevInside))) 
			Mesh::Draw2DLine(hDCFrameBuffer, prevProject, initProject);
	}
}

// ----------------------------------------------------------------------------------------------
CubeMesh::CubeMesh(float fWidth, float fHeight, float fDepth) : Mesh(6) {
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;
	float fHalfDepth = fDepth * 0.5f;

	Poly* pFrontFace = new Poly(4);
	pFrontFace->SetVertex(0, Vertex(-fHalfWidth, +fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(1, Vertex(+fHalfWidth, +fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(2, Vertex(+fHalfWidth, -fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(3, Vertex(-fHalfWidth, -fHalfHeight, -fHalfDepth));
	SetPolygon(0, pFrontFace);

	Poly* pTopFace = new Poly(4);
	pTopFace->SetVertex(0, Vertex(-fHalfWidth, +fHalfHeight, +fHalfDepth));
	pTopFace->SetVertex(1, Vertex(+fHalfWidth, +fHalfHeight, +fHalfDepth));
	pTopFace->SetVertex(2, Vertex(+fHalfWidth, +fHalfHeight, -fHalfDepth));
	pTopFace->SetVertex(3, Vertex(-fHalfWidth, +fHalfHeight, -fHalfDepth));
	SetPolygon(1, pTopFace);

	Poly* pBackFace = new Poly(4);
	pBackFace->SetVertex(0, Vertex(-fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(1, Vertex(+fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(2, Vertex(+fHalfWidth, +fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(3, Vertex(-fHalfWidth, +fHalfHeight, +fHalfDepth));
	SetPolygon(2, pBackFace);

	Poly* pBottomFace = new Poly(4);
	pBottomFace->SetVertex(0, Vertex(-fHalfWidth, -fHalfHeight, -fHalfDepth));
	pBottomFace->SetVertex(1, Vertex(+fHalfWidth, -fHalfHeight, -fHalfDepth));
	pBottomFace->SetVertex(2, Vertex(+fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBottomFace->SetVertex(3, Vertex(-fHalfWidth, -fHalfHeight, +fHalfDepth));
	SetPolygon(3, pBottomFace);

	Poly* pLeftFace = new Poly(4);
	pLeftFace->SetVertex(0, Vertex(-fHalfWidth, +fHalfHeight, +fHalfDepth));
	pLeftFace->SetVertex(1, Vertex(-fHalfWidth, +fHalfHeight, -fHalfDepth));
	pLeftFace->SetVertex(2, Vertex(-fHalfWidth, -fHalfHeight, -fHalfDepth));
	pLeftFace->SetVertex(3, Vertex(-fHalfWidth, -fHalfHeight, +fHalfDepth));
	SetPolygon(4, pLeftFace);

	Poly* pRightFace = new Poly(4);
	pRightFace->SetVertex(0, Vertex(+fHalfWidth, +fHalfHeight, -fHalfDepth));
	pRightFace->SetVertex(1, Vertex(+fHalfWidth, +fHalfHeight, +fHalfDepth));
	pRightFace->SetVertex(2, Vertex(+fHalfWidth, -fHalfHeight, +fHalfDepth));
	pRightFace->SetVertex(3, Vertex(+fHalfWidth, -fHalfHeight, -fHalfDepth));
	SetPolygon(5, pRightFace);
}