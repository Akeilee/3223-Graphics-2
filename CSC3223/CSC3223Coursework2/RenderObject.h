//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#pragma once
#include "../../Common/Matrix4.h"
#include "../../Common/TextureBase.h"
#include "../../Common/ShaderBase.h"

#include <vector>
namespace NCL {
	using namespace NCL::Rendering;
	class MeshGeometry;
	namespace CSC3223 {
		using namespace Maths;

		class RenderObject
		{
		public:
			RenderObject(MeshGeometry* mesh, Matrix4 m = Matrix4());
			~RenderObject();

			MeshGeometry* GetMesh() const {
				return mesh;
			}

			void  SetTransform(Matrix4 mat) {
				transform = mat;
			}

			Matrix4 GetTransform() const {
				return transform;
			}

			void SetBaseTexture(TextureBase* t) {
				texture = t;
			}

			TextureBase* GetBaseTexture() const {
				return texture;
			}


			void SetShader(ShaderBase* s) {
				shader = s;
			}

			ShaderBase* GetShader() const {
				return shader;
			}

			//tut 10
			void SetSecondTexture(TextureBase* t) {
				secondTexture = t;
			}

			TextureBase* GetSecondTexture() const {
				return secondTexture;
			}

			//tut 14
			void UpdateSceneHierarchy();

			Matrix4 GetLocalTransform() const {
				return localMatrix;
			}

			void SetLocalTransform(const Matrix4& m) {
				localMatrix = m;
			}

			void AddChild(RenderObject* o) {
				o->parentObject = this;
				childObjects.push_back(o);
			}

			std::vector<RenderObject*> GetChildNodes() const {
				return childObjects;
			}


		protected:
			MeshGeometry* mesh;
			TextureBase* texture;
			ShaderBase* shader;
			Matrix4			transform;

			//tut 10
			TextureBase* secondTexture;

			//tut 14
			Matrix4 localMatrix;
			RenderObject* parentObject;
			std::vector<RenderObject*> childObjects;


		};
	}
}

