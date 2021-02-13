#include "ModelUtility.h"
#ifdef _DEBUG
#pragma comment(lib, "Assimp/Debug/x64/assimp-vc141-mtd.lib")
#else
#pragma comment(lib, "Assimp/Release/x64/assimp-vc141-mt.lib")
#endif

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ModelImporter
{
	bool ModelUtility::LoadModel(const char* filePath)
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(
			filePath,	
			aiProcess_CalcTangentSpace	| 
			aiProcess_Triangulate		|
			aiProcess_JoinIdenticalVertices	|
			aiProcess_SortByPType
			);

		if (!pScene)
			return false;

		return true;
	}
}