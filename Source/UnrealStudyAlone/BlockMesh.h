// Copyright Lee Chang Young 2019.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "BlockMesh.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDYALONE_API UBlockMesh : public UProceduralMeshComponent
{
	GENERATED_BODY()

public:
	UBlockMesh();

private:
	const TArray<FVector> Vertices =
	{
		//Top
		FVector(-0.5f, -0.5f,  0.5f),
		FVector( 0.5f, -0.5f,  0.5f),
		FVector(-0.5f,  0.5f,  0.5f),
		FVector( 0.5f,  0.5f,  0.5f),
		//Bottom
		FVector(-0.5f, -0.5f, -0.5f),
		FVector(-0.5f,  0.5f, -0.5f),
		FVector( 0.5f, -0.5f, -0.5f),
		FVector( 0.5f,  0.5f, -0.5f),
		//Front
		FVector(-0.5f, -0.5f, -0.5f),
		FVector( 0.5f, -0.5f, -0.5f),
		FVector(-0.5f, -0.5f,  0.5f),
		FVector( 0.5f, -0.5f,  0.5f),
		//Back
		FVector(-0.5f,  0.5f, -0.5f),
		FVector(-0.5f,  0.5f,  0.5f),
		FVector( 0.5f,  0.5f, -0.5f),
		FVector( 0.5f,  0.5f,  0.5f),
		//Left
		FVector(-0.5f, -0.5f, -0.5f),
		FVector(-0.5f,  0.5f, -0.5f),
		FVector(-0.5f, -0.5f,  0.5f),
		FVector(-0.5f,  0.5f,  0.5f),
		//Right
		FVector( 0.5f, -0.5f, -0.5f),
		FVector( 0.5f, -0.5f,  0.5f),
		FVector( 0.5f,  0.5f, -0.5f),
		FVector( 0.5f,  0.5f,  0.5f)
	};

	const TArray<int32> Triangles =
	{
		//Top
		0, 1, 2,
		3, 2, 1,
		//Bottom
		4, 5, 6,
		7, 6, 5,
		//Front
		8, 9, 10,
		11, 10, 9,
		//Back
		12, 13, 14,
		15, 14, 13,
		//Left
		16, 17, 18,
		19, 18, 17,
		//Right
		20, 21, 22,
		23, 22, 21,
	};

	const TArray<FVector2D> UV0 = 
	{
		FVector2D(0.f, 0.f),
		FVector2D(0.f, 1.f),
		FVector2D(1.f, 0.f),
		FVector2D(1.f, 1.f),

		FVector2D(0.f, 0.f),
		FVector2D(0.f, 1.f),
		FVector2D(1.f, 0.f),
		FVector2D(1.f, 1.f),

		FVector2D(0.f, 0.f),
		FVector2D(0.f, 1.f),
		FVector2D(1.f, 0.f),
		FVector2D(1.f, 1.f),

		FVector2D(0.f, 0.f),
		FVector2D(0.f, 1.f),
		FVector2D(1.f, 0.f),
		FVector2D(1.f, 1.f),

		FVector2D(0.f, 0.f),
		FVector2D(0.f, 1.f),
		FVector2D(1.f, 0.f),
		FVector2D(1.f, 1.f),

		FVector2D(0.f, 0.f),
		FVector2D(0.f, 1.f),
		FVector2D(1.f, 0.f),
		FVector2D(1.f, 1.f),
	};
};
