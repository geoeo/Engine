#include "BoxIndicesGeometry.h"

BoxIndicesGeometry::BoxIndicesGeometry(){

	for (int i = 0; i < nVertices; i++){
		indices.push_back(i);
	}
	
}