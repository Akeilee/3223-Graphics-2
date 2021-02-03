//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#include "Renderer.h"
#include "../../Common/Window.h"
#include "../../Common/TextureWriter.h"
#include "../../Common/Maths.h"
#include "../../Common/Matrix3.h"

using namespace NCL;
using namespace Rendering;
using namespace CSC3223;

Renderer::Renderer(Window& w) : OGLRenderer(w)
{
	defaultShader = new OGLShader("rasterisationVert.glsl", "rasterisationFrag.glsl");
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}

Renderer::~Renderer()
{
	delete defaultShader;
}

void Renderer::RenderFrame() {
	OGLShader* activeShader = nullptr;

	int modelLocation = 0;

	for (const RenderObject* object : renderObjects) {
		OGLShader* objectShader = (OGLShader*)object->GetShader();
		if (!object->GetMesh()) {
			continue;
		}
		if (objectShader == nullptr) {
			objectShader = defaultShader;
		}
		if (objectShader != activeShader) {
			activeShader = objectShader;
			BindShader(activeShader);
			int projLocation = glGetUniformLocation(activeShader->GetProgramID(), "projMatrix");
			int viewLocation = glGetUniformLocation(activeShader->GetProgramID(), "viewMatrix");
			modelLocation = glGetUniformLocation(activeShader->GetProgramID(), "modelMatrix");

			glUniformMatrix4fv(projLocation, 1, false, (float*)&projMatrix);
			glUniformMatrix4fv(viewLocation, 1, false, (float*)&viewMatrix);

			//tut 13
			ApplyLightToShader(activeLight, activeShader);
			Matrix3 rotation = Matrix3(viewMatrix);
			Vector3 invCamPos = viewMatrix.GetPositionVector();
			Vector3 camPos = rotation * -invCamPos; // view mat is an 'inverse '
			glUniform3fv(glGetUniformLocation(activeShader->GetProgramID(), "cameraPos"), 1, (float*)&camPos);


			//tut 9
			int timeLocation = glGetUniformLocation(activeShader->GetProgramID(), "time");
			if (timeLocation >= 0) {
				float totalTime = frameTimer.GetTotalTime();
				glUniform1f(timeLocation, totalTime);
			}
			//tut 9
		}


		Matrix4 mat = object->GetTransform();
		glUniformMatrix4fv(modelLocation, 1, false, (float*)&mat);

		BindTextureToShader(object->GetBaseTexture(), "mainTex", 0);
		//tut 10
		BindTextureToShader(object->GetSecondTexture(), "secondTex", 1);
		//tut 10
		BindMesh(object->GetMesh());
		DrawBoundMesh();

		//tut1 part 3
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_1)) // toggles debug on/off
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Draw only lines no fill
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_2)) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // normal mode
		}

	}
}


void Renderer::OnWindowResize(int w, int h) {
	OGLRenderer::OnWindowResize(w, h);
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}

//tut 6
void Renderer::WriteDepthBuffer(const string& filepath) const {
	float* data = new float[currentWidth * currentHeight];
	glReadPixels(0, 0, currentWidth, currentHeight, GL_DEPTH_COMPONENT, GL_FLOAT, data);

	char* pixels = new char[currentWidth * currentHeight * 3];
	char* pixelPointer = pixels;

	for (int y = 0; y < currentHeight; ++y) {
		for (int x = 0; x < currentWidth; ++x) {
			float depthValue = data[(y * currentWidth) + x];
			float mult = 1.0f / 0.333f;

			float redAmount = Maths::Clamp(depthValue, 0.0f, 0.333f) * mult;
			float greenAmount = (Maths::Clamp(depthValue, 0.333f, 0.666f) - 0.333f) * mult;
			float blueAmount = (Maths::Clamp(depthValue, 0.666f, 1.0f) - 0.666f) * mult;

			unsigned char redByte = (char)(redAmount * 255);
			unsigned char greenByte = (char)(greenAmount * 255);
			unsigned char blueByte = (char)(blueAmount * 255);
			*pixelPointer++ = (char)(redAmount * 255);

			*pixelPointer++ = (char)(greenAmount * 255);
			*pixelPointer++ = (char)(blueAmount * 255);
		}
	}

	TextureWriter::WritePNG(filepath, pixels, currentWidth, currentHeight, 3);
	delete pixels;
	delete data;
}

//tut7
void Renderer::EnableBilinearFiltering(OGLTexture& t) {
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::EnableMipMapFiltering(OGLTexture& t) {
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::EnableTextureRepeating(OGLTexture& t, bool uRepeat, bool vRepeat) {
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uRepeat ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vRepeat ? GL_REPEAT : GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, 0);
}

//tut8
void Renderer::SetBlendToLinear() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::SetBlendToAdditive() {
	glBlendFunc(GL_ONE, GL_ONE);
}

void Renderer::SetBlendToInvert() {
	glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
}

//tut 13
void Renderer::SetLightProperties(Vector3 position, Vector3 colour, float radius) {
	activeLight.position = position;
	activeLight.colour = colour;
	activeLight.radius = radius;
}

void Renderer::ApplyLightToShader(const Light& l, const OGLShader* s) {
	glUniform3fv(glGetUniformLocation(s->GetProgramID(), "lightColour"), 1, (float*)&l.colour);
	glUniform3fv(glGetUniformLocation(s->GetProgramID(), "lightPos"), 1, (float*)&l.position);
	glUniform1f(glGetUniformLocation(s->GetProgramID(), "lightRadius"), l.radius);
}

//tut 14
void Renderer::RenderScene(RenderObject* root) {
	BeginFrame();
	RenderNode(root);
	EndFrame();
}

void Renderer::RenderNode(RenderObject* node) {
	if (node->GetMesh()) {
		OGLShader* objectShader = (OGLShader*)node->GetShader();
		BindShader(objectShader);

		int projLocation = glGetUniformLocation(objectShader->GetProgramID(), "projMatrix");
		int viewLocation = glGetUniformLocation(objectShader->GetProgramID(), "viewMatrix");
		int modelLocation = glGetUniformLocation(objectShader->GetProgramID(), "modelMatrix");
		glUniformMatrix4fv(projLocation, 1, false, (float*)&projMatrix);
		glUniformMatrix4fv(viewLocation, 1, false, (float*)&viewMatrix);

		Matrix4 mat = node->GetTransform();
		glUniformMatrix4fv(modelLocation, 1, false, (float*)&mat);

		BindTextureToShader(node->GetBaseTexture(), "mainTex", 0);
		BindMesh(node->GetMesh());
		DrawBoundMesh();
	}

	//const std::vector <RenderObject*>& children = node->GetChildNodes();
	//for (auto& i : children) {
	//	RenderNode(i);
	//}
}