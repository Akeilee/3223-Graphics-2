//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "RenderObject.h"
#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3223 {

		class Renderer : public OGLRenderer
		{
		public:
			Renderer(Window& w);
			~Renderer();

			void AddRenderObject(RenderObject* ro) {
				renderObjects.emplace_back(ro);
			}

			void DeleteAllRenderObjects() {
				for (const RenderObject* object : renderObjects) {
					delete object;
				}
				renderObjects.clear();
			}

			void SetProjectionMatrix(const Matrix4& m) {
				projMatrix = m;
			}

			void SetViewMatrix(const Matrix4& m) {
				viewMatrix = m;
			}

			//tut 6
			void EnableDepthBuffer(bool state) {
				if (state) {
					glEnable(GL_DEPTH_TEST);
				}
				else {
					glDisable(GL_DEPTH_TEST);
				}
			}

			void WriteDepthBuffer(const string& filepath) const;

			//tut7
			void EnableBilinearFiltering(OGLTexture& t);
			void EnableMipMapFiltering(OGLTexture& t);
			void EnableTextureRepeating(OGLTexture& t, bool uRepeat, bool vRepeat);

			//tut8
			void EnableAlphaBlending(bool state) {
				if (state) {
					glEnable(GL_BLEND);
				}
				else {
					glDisable(GL_BLEND);
				}
			}

			void SetBlendToLinear();
			void SetBlendToAdditive();
			void SetBlendToInvert();

			//tut 13
			struct Light {
				Vector3 position;
				float radius;
				Vector3 colour;
			};
			void SetLightProperties(Vector3 pos, Vector3 colour, float radius);

			//tut 14
			void RenderScene(RenderObject* root);

		protected:

			void OnWindowResize(int w, int h)	override;

			void RenderFrame()	override;
			OGLShader* defaultShader;

			Matrix4		projMatrix;
			Matrix4		viewMatrix;

			vector<RenderObject*> renderObjects;

			//tut 9
			GameTimer frameTimer;

			//tut 13
			void ApplyLightToShader(const Light& l, const OGLShader* s);
			Light activeLight;

			//tut 14
			void RenderNode(RenderObject* node);

		};
	}
}

