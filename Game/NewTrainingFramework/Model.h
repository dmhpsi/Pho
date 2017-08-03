#pragma once 
#include "../Utilities/utilities.h"
#include "Vertex.h"

class Model
{
	void Init(Vertex* verticle, unsigned int* indices);
public:
	int ID;
	int numVertices, numIndices;
	GLuint vboId, iboId;
	errno_t LoadNFG(const char * nfg_file);
	~Model();
};