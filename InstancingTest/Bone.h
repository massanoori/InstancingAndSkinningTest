#pragma once

#include <DirectXMath.h>
#include <vector>

struct Bone
{
	DirectX::XMFLOAT3 BaseTranslation;
	DirectX::XMFLOAT3 BaseRotation;
	DirectX::XMFLOAT3 BaseScaling;
	DirectX::XMMATRIX BasePoseInverse;
	DirectX::XMMATRIX RelativeTransform;
	DirectX::XMMATRIX Transform;
	Bone* pParent;
	std::vector<Bone*> pChildren;
};

void ComputeBasePoseInverse(Bone& root)
{
	auto invRotation =
		DirectX::XMMatrixRotationZ(-root.BaseRotation.z) *
		DirectX::XMMatrixRotationY(-root.BaseRotation.y) *
		DirectX::XMMatrixRotationX(-root.BaseRotation.x);
	auto invScaling = DirectX::XMMatrixScaling(
		1.0f / root.BaseScaling.x,
		1.0f / root.BaseScaling.y,
		1.0f / root.BaseScaling.z);
	auto invLocal = invRotation * invScaling;

	if (root.pParent == nullptr)
	{
		root.BasePoseInverse = invLocal;
	}
	else
	{
		auto invTranslation = DirectX::XMMatrixTranslation(
			-root.pParent->BaseTranslation.x,
			-root.pParent->BaseTranslation.y,
			-root.pParent->BaseTranslation.z);
		root.BasePoseInverse = root.pParent->BasePoseInverse * invTranslation * invLocal;
	}

	for (auto& pChild : root.pChildren)
	{
		ComputeBasePoseInverse(*pChild);
	}
}

void ComputeTransform(Bone& root)
{
	auto transfScaling = DirectX::XMMatrixScaling(
		root.BaseScaling.x,
		root.BaseScaling.y,
		root.BaseScaling.z);
	auto transfRotation =
		DirectX::XMMatrixRotationX(root.BaseRotation.x) *
		DirectX::XMMatrixRotationY(root.BaseRotation.y) *
		DirectX::XMMatrixRotationZ(root.BaseRotation.z);
	

	if (root.pParent == nullptr)
	{
		root.Transform =
			root.RelativeTransform *
			transfScaling * transfRotation;
	}
	else
	{
		auto transfTranslation = DirectX::XMMatrixTranslation(
			root.pParent->BaseTranslation.x,
			root.pParent->BaseTranslation.y,
			root.pParent->BaseTranslation.z);
		root.Transform =
			root.RelativeTransform *
			transfScaling * transfRotation * transfTranslation *
			root.pParent->Transform;
	}

	for (auto& pChild : root.pChildren)
	{
		ComputeTransform(*pChild);
	}

	root.Transform = root.BasePoseInverse * root.Transform;
}
