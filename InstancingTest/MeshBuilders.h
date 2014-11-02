#pragma once

#include <DirectXMath.h>
#include <cstdint>
#include <cmath>
#include <vector>

struct Vertex
{
	DirectX::XMFLOAT3 m_Position;
	DirectX::XMFLOAT3 m_Normal;
};

void AppendCylinder(
	float radius,
	float height,
	std::uint32_t nStacks,
	std::uint32_t nSlices,
	std::vector<Vertex>& vertices,
	std::vector<std::uint32_t>& indices)
{
	typedef std::uint32_t index_type;
	vertices.reserve(vertices.size() + nSlices * (nStacks + 1 + 2));
	index_type startIndex = vertices.size();

	// ====================================================
	// side vertices
	// ====================================================
	for (index_type iStack = 0; iStack <= nStacks; iStack++)
	{
		const float y = height * iStack / nStacks - height * 0.5f;
		for (index_type iSlice = 0; iSlice < nSlices; iSlice++)
		{
			const float angle = DirectX::XM_2PI * iSlice / nSlices;
			const float nx = cosf(angle);
			const float nz = sinf(angle);
			const float x = radius * nx;
			const float z = radius * nz;

			vertices.push_back({ { x, y, z }, { nx, 0.0f, nz } });
		}
	}

	// ====================================================
	// top vertices
	// ====================================================
	index_type topFaceStartIndex = vertices.size();
	const float y_top = height * 0.5f;
	vertices.push_back({ { radius, y_top, 0.0f }, { 0.0f, 1.0f, 0.0f } });
	for (index_type iSlice = 1; iSlice <= (nSlices - 1) / 2; iSlice++)
	{
		const float angle = DirectX::XM_2PI * iSlice / nSlices;
		const float nx = cosf(angle);
		const float nz = sinf(angle);
		const float x = radius * nx;
		const float z = radius * nz;

		vertices.push_back({ { x, y_top, -z }, { 0.0f, 1.0f, 0.0f } });
		vertices.push_back({ { x, y_top, z }, { 0.0f, 1.0f, 0.0f } });
	}
	if (nSlices % 2 == 0)
	{
		vertices.push_back({ { -radius, y_top, 0.0f }, { 0.0f, 1.0f, 0.0f } });
	}

	// ====================================================
	// bottom vertices
	// ====================================================
	index_type bottomFaceStartIndex = vertices.size();
	const float y_bottom = -height * 0.5f;
	vertices.push_back({ { radius, y_bottom, 0.0f }, { 0.0f, -1.0f, 0.0f } });
	for (index_type iSlice = 1; iSlice <= (nSlices - 1) / 2; iSlice++)
	{
		const float angle = DirectX::XM_2PI * iSlice / nSlices;
		const float nx = cosf(angle);
		const float nz = sinf(angle);
		const float x = radius * nx;
		const float z = radius * nz;

		vertices.push_back({ { x, y_bottom, z }, { 0.0f, -1.0f, 0.0f } });
		vertices.push_back({ { x, y_bottom, -z }, { 0.0f, -1.0f, 0.0f } });
	}
	if (nSlices % 2 == 0)
	{
		vertices.push_back({ { -radius, y_bottom, 0.0f }, { 0.0f, -1.0f, 0.0f } });
	}

	// ====================================================
	// side indices
	// ====================================================
	if (nStacks > nSlices)
	{
		for (index_type iSlice = 0; iSlice < nSlices; iSlice++)
		{
			for (index_type iStack = 0; iStack <= nStacks; iStack++)
			{
				indices.push_back(startIndex + iStack * nSlices + (iSlice + 1) % nSlices);
				indices.push_back(startIndex + iStack * nSlices + iSlice);
			}
			// terminate strip
			indices.push_back(0xffffffff);
		}
	}
	else
	{
		for (index_type iStack = 0; iStack < nStacks; iStack++)
		{
			for (index_type iSlice = 0; iSlice < nSlices + 1; iSlice++)
			{
				indices.push_back(startIndex + iStack * nSlices + iSlice % nSlices);
				indices.push_back(startIndex + (iStack + 1) * nSlices + iSlice % nSlices);
			}
			// terminate strip
			indices.push_back(0xffffffff);
		}
	}

	// ====================================================
	// top indices
	// ====================================================
	for (index_type iSlice = 0; iSlice < nSlices; iSlice++)
	{
		indices.push_back(topFaceStartIndex + iSlice);
	}

	// terminate strip
	indices.push_back(0xffffffff);

	// ====================================================
	// bottom indices
	// ====================================================
	for (index_type iSlice = 0; iSlice < nSlices; iSlice++)
	{
		indices.push_back(bottomFaceStartIndex + iSlice);
	}

	// terminate strip
	indices.push_back(0xffffffff);
}
