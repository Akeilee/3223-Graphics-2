//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#include "RenderObject.h"
#include "../../Common/MeshGeometry.h"

using namespace NCL;
using namespace CSC3223;

RenderObject::RenderObject(MeshGeometry* inMesh, Matrix4 m)
{
	mesh = inMesh;
	transform = m;
	texture = nullptr;
	shader = nullptr;
	secondTexture = nullptr;

	//tut 14
	parentObject = nullptr;
}

RenderObject::~RenderObject()
{
}

//tut 14
void RenderObject::UpdateSceneHierarchy() {
	if (!parentObject) {
		transform = localMatrix;
	}
	else {
		transform = parentObject->transform * localMatrix;
	}
	for (auto& i : childObjects) {
		i->UpdateSceneHierarchy();
	}
}