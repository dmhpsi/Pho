#include "stdafx.h"
#include "Model.h"

void Model::Init(Vertex* vetices, unsigned int* indices)
{
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*numVertices, vetices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*numIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

errno_t Model::LoadNFG(const char * nfg_file)
{
	FILE *modelFile;
	if (fopen_s(&modelFile, nfg_file, "r") != 0)
	{
		return 0;
	}

	fscanf_s(modelFile, "NrVertices: %d\n", &numVertices);

	Vertex *vetices = new Vertex[numVertices];
	int i, c;
	for (i = 0; i < numVertices; i++)
	{
		fscanf_s(modelFile, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
			&c,
			&vetices[i].pos.x, &vetices[i].pos.y, &vetices[i].pos.z,
			&vetices[i].normal.x, &vetices[i].normal.y, &vetices[i].normal.z,
			&vetices[i].binormal.x, &vetices[i].binormal.y, &vetices[i].binormal.z,
			&vetices[i].tangent.x, &vetices[i].tangent.y, &vetices[i].tangent.z,
			&vetices[i].uv.x, &vetices[i].uv.y
			);
		vetices[i].pos.w = 1.0;
	}

	
	fscanf_s(modelFile, "NrIndices: %d\n", &numIndices);

	unsigned int *indices = new unsigned int[numIndices];
	for (i = 0; i < numIndices / 3; i++)
	{
		fscanf_s(modelFile, "%d. %d, %d, %d\n",
			&c,
			&indices[i * 3],
			&indices[i * 3 + 1],
			&indices[i * 3 + 2]
			);
	}
	fclose(modelFile);

	Init(vetices, indices);
	
	delete[] vetices;
	delete[] indices;

	return 1;
}


Model::~Model()
{
}
