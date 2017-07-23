#ifndef __eMesh_h__
#define __eMesh_h__

#include "IMesh.h"
#include "IAsset.h"

class eMesh : public IMesh
{
public:
    /// Indicates if this submesh shares vertex data with other meshes or whether it has it's own vertices.
    bool useSharedVertices;

    /// The render operation type used to render this submesh
    RenderOperation::OperationType operationType;

    /** Dedicated vertex data (only valid if useSharedVertices = false).
        @remarks
            This data is completely owned by this submesh.
        @par
            The use of shared or non-shared buffers is determined when
            model data is converted to the OGRE .mesh format.
    */
    VertexData *vertexData;

    /// Face index data
    IndexData *indexData;
public:
    eMesh();
    ~eMesh();
	// provide data query interface for client.
	void getRenderOperation(RenderOperation& op);
};

class eMeshMap : public IAsset
{
public:
	String mName;
	HashMap<String, eMesh*> mMeshMap;
public:
	void addMesh(String name, eMesh* mesh);
};
#endif
