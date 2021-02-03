//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"
using namespace std;

using namespace NCL;
using namespace CSC3223;

OGLShader* shaders[2];

RenderObject* Background(Renderer& renderer) { 
	OGLMesh* background = new OGLMesh();
	background->SetVertexPositions({ Vector3(0,0,-0.9), Vector3(800,0,-0.9), Vector3(0,600,-0.9),Vector3(800,600,-0.9) });
	background->SetVertexTextureCoords({ Vector2(0,0),Vector2(1,0),Vector2(0,-1),Vector2(1,-1) });
	background->SetVertexColours({ Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1) });
	background->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	background->UploadToGPU();

	Matrix4 translate = Matrix4::Translation(Vector3(-400, -330, -650));

	RenderObject* render = new RenderObject(background,translate);
	TextureBase* bkgrndTex = OGLTexture::RGBATextureFromFilename("cw2Back.png");
	render->SetBaseTexture(bkgrndTex);
	renderer.AddRenderObject(render);

	return render;
}

RenderObject* Coursework2(Renderer& renderer) {
	OGLMesh* m = new OGLMesh("Cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Triangles);

	m->UploadToGPU();

	RenderObject* object = new RenderObject(m);
	TextureBase* bkgrndTex = OGLTexture::RGBATextureFromFilename("doge.PNG");
	object->SetBaseTexture(bkgrndTex);
	renderer.AddRenderObject(object);
	renderer.SetLightProperties(Vector3(0, 10, 0), Vector3(1,1,1), 100);

	return object;
}

RenderObject* TessCube(Renderer& renderer) { //for tesellation only
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	OGLMesh* m = new OGLMesh("Cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Patches);

	m->UploadToGPU();

	RenderObject* object = new RenderObject(m);
	TextureBase* bkgrndTex = OGLTexture::RGBATextureFromFilename("doge.PNG");
	object->SetBaseTexture(bkgrndTex);
	//object->SetTransform(Matrix4::Translation(Vector3(0, 0, -10)));
	renderer.AddRenderObject(object);

	return object;
}


int main() {
	Window* w = Window::CreateGameWindow("CSC3223 Coursework 2!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);
	Vector3 viewPosition(0, 0, 0); //camera view

	RenderObject* back = Background(*renderer);
	RenderObject* cube = Coursework2(*renderer);
	RenderObject* cubeTess = TessCube(*renderer);
	
	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

	float rotation = 0.0f;

	OGLShader* original = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl");
	cube->SetShader(original);
	back->SetShader(original);
	
	cout << endl << " --- CONTROLS ---" << endl;
	cout << "R - Reset cube" << endl;
	cout << "S - Shrink cube" << endl;
	cout << "B - Blend clean texture into destroyed texture" << endl;
	cout << "F - Fade cube" << endl;
	cout << "G - Split cube up with Geometry shader" << endl;
	cout << "T - Tessellate cube" << endl;
	cout << "M - Mixture of Geometry and Lighting Shader" << endl;
	cout << "L - Lighting shader only" << endl;
	cout << "1 - Turn polygons on" << endl;
	cout << "2 - Turn polygons off" << endl;
	cout << "Arrow Keys, Z, X - Change view position" << endl;
	cout << "-------------------------------------------------------" << endl <<endl;


	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {

		float time = w->GetTimer()->GetTimeDelta();
		renderer->Update(time);
		rotation += time * 30;

		renderer->EnableAlphaBlending(true);
		renderer->SetBlendToLinear();
		renderer->EnableDepthBuffer(true);


		Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -10));
		modelMat = modelMat * Matrix4::Rotation(rotation, Vector3(1, 1, 1));
		cube->SetTransform(modelMat);
		
		//Matrix4 modelMatTess = Matrix4::Translation(Vector3(4.21, 3.06, -10));
		Matrix4 modelMatTess = Matrix4::Translation(Vector3(1.6, 1.6, -10));
		modelMatTess = modelMatTess * Matrix4::Rotation(rotation, Vector3(1, 1, 1)) * Matrix4::Scale(Vector3(1, 1, 1));
		cubeTess->SetTransform(modelMatTess);

		renderer->DrawString("OpenGL Rendering!", Vector2(10, 10));
		renderer->Render();


		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}
		
		w->SetTitle(std::to_string(time));


		//reset
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_R)) {
			renderer->DeleteAllRenderObjects();
			renderer = new Renderer(*w);
			back = Background(*renderer);
			cube = Coursework2(*renderer);
			renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

			back->SetBaseTexture(OGLTexture::RGBATextureFromFilename("cw2Back.png"));
			cube->SetBaseTexture(OGLTexture::RGBATextureFromFilename("doge.png"));

			original = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl");
			cube->SetShader(original);
			back->SetShader(original);

			Matrix4 reset = Matrix4::Translation(Vector3(0, 0, -10));
			cube->SetTransform(reset);
			viewPosition = Vector3(0, 0, 0);
		}

		//shrink
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_S)){
			renderer->DeleteAllRenderObjects();
			renderer = new Renderer(*w);
			back = Background(*renderer);
			cube = Coursework2(*renderer);
			renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

			back->SetBaseTexture(OGLTexture::RGBATextureFromFilename("vortex.png"));
			cube->SetBaseTexture(OGLTexture::RGBATextureFromFilename("ohno.png"));

			OGLShader* shrink = new OGLShader("ShrinkVert.glsl", "RasterisationFrag.glsl");
			original = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl");
			cube->SetShader(shrink);
			back->SetShader(original);
		}

		//blend
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_B)) {
			renderer->DeleteAllRenderObjects();
			renderer = new Renderer(*w);
			back = Background(*renderer);
			cube = Coursework2(*renderer);
			renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

			back->SetBaseTexture(OGLTexture::RGBATextureFromFilename("minecraft.png"));
			cube->SetBaseTexture(OGLTexture::RGBATextureFromFilename("woodTex.png"));
			cube->SetSecondTexture(OGLTexture::RGBATextureFromFilename("destroyTex.png"));

			OGLShader* blend = new OGLShader("RasterisationVert.glsl", "BlendFrag.glsl");
			original = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl");
			cube->SetShader(blend);
			back->SetShader(original);
		}

		//fade
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F)) {
			renderer->DeleteAllRenderObjects();
			renderer = new Renderer(*w);
			back = Background(*renderer);
			cube = Coursework2(*renderer);
			renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

			back->SetBaseTexture(OGLTexture::RGBATextureFromFilename("green.png"));
			cube->SetBaseTexture(OGLTexture::RGBATextureFromFilename("sadfrog.png"));

			OGLShader* fade = new OGLShader("RasterisationVert.glsl", "FadeFrag.glsl");
			original = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl");
			cube->SetShader(fade);
			back->SetShader(original);
		}

		//geometry splitting cube
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_G)) {
			renderer->DeleteAllRenderObjects();
			renderer = new Renderer(*w);
			back = Background(*renderer);
			cube = Coursework2(*renderer);
			renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

			back->SetBaseTexture(OGLTexture::RGBATextureFromFilename("triangle.png"));
			cube->SetBaseTexture(OGLTexture::RGBATextureFromFilename("checker.png"));

			OGLShader* geom = new OGLShader("GeomVert.glsl", "RasterisationFrag.glsl", "GeomCube.glsl");
			original = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl");
			cube->SetShader(geom);
			back->SetShader(original);
		}

		//tessellation comet cube
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_T)) {
			renderer->DeleteAllRenderObjects();
			renderer = new Renderer(*w);
			back = Background(*renderer);
			cubeTess = TessCube(*renderer);
			renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

			back->SetBaseTexture(OGLTexture::RGBATextureFromFilename("nightsky.png"));
			cubeTess->SetBaseTexture(OGLTexture::RGBATextureFromFilename("dogeblue.png"));

			OGLShader* tess = new OGLShader("TesselVert.glsl", "TesselFrag.glsl", "", "TesselControl.glsl", "TesselEvaluate.glsl");
			original = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl");
			cubeTess->SetShader(tess);
			back->SetShader(original);
		}

		//change lighting
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_L)) {
			renderer->DeleteAllRenderObjects();
			renderer = new Renderer(*w);
			back = Background(*renderer);
			cube = Coursework2(*renderer);
			renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

			back->SetBaseTexture(OGLTexture::RGBATextureFromFilename("cw2back.png"));
			cube->SetBaseTexture(OGLTexture::RGBATextureFromFilename("marble.png"));

			OGLShader* light = new OGLShader("LightCubeVert.glsl", "LightCubeFrag.glsl");
			original = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl");
			cube->SetShader(light);
			back->SetShader(original);
		}

		//mix of geometry and lighting shader
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_M)) {
			renderer->DeleteAllRenderObjects();
			renderer = new Renderer(*w);
			back = Background(*renderer);
			cube = Coursework2(*renderer);
			renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

			back->SetBaseTexture(OGLTexture::RGBATextureFromFilename("gradient.png"));
			cube->SetBaseTexture(OGLTexture::RGBATextureFromFilename("gold.png"));

			OGLShader* mix = new OGLShader("GeomLightVert.glsl", "GeomLightFrag.glsl", "GeomPoint.glsl");
			original = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl");
			cube->SetShader(mix);
			back->SetShader(original);
		}

		
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT)) { //left
			viewPosition.x += 1.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT)) { //right
			viewPosition.x -= 1.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_UP)) { //up
			viewPosition.y += 1.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN)) { //down
			viewPosition.y -= 1.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_Z)) { //near plane
			viewPosition.z += 1.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_X)) { //far plane
			viewPosition.z -= 1.0f;
		}

		renderer->SetViewMatrix(Matrix4::Translation(viewPosition)); //allowing tranlation of the camera view

	}

	delete renderer;

	Window::DestroyGameWindow();
}