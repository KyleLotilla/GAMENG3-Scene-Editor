#include "game/DefaultGraphicsPrimitive.h"

DefaultGraphicsPrimitive::DefaultGraphicsPrimitive()
{
	Mat4 identityMatrix;
	identityMatrix.setIdentity();
	this->m_shaderInput.m_model = identityMatrix;
	this->m_shaderInput.m_proj = identityMatrix;
	this->m_shaderInput.m_view = identityMatrix;
	this->m_shaderInput.m_red = 1.0f;
	this->m_shaderInput.m_green = 1.0f;
	this->m_shaderInput.m_blue = 1.0f;
	this->m_shaderInput.m_alpha = 1.0f;
}

DefaultGraphicsPrimitive::~DefaultGraphicsPrimitive()
{
}

void DefaultGraphicsPrimitive::update(float deltaTime)
{
}

void DefaultGraphicsPrimitive::draw(DeviceContext* deviceContext, ViewportParams viewportParams)
{
	Mat4 modelMatrix;
	Mat4 translateMatrix;
	Mat4 scaleMatrix;
	Mat4 rotationMatrix;
	reactphysics3d::Matrix3x3 quaternionMatrix = this->m_localRotation.getMatrix();
	rotationMatrix.m_mat[0][0] = quaternionMatrix[0][0];
	rotationMatrix.m_mat[0][1] = quaternionMatrix[1][0];
	rotationMatrix.m_mat[0][2] = quaternionMatrix[2][0];
	rotationMatrix.m_mat[0][3] = 0.0f;

	rotationMatrix.m_mat[1][0] = quaternionMatrix[0][1];
	rotationMatrix.m_mat[1][1] = quaternionMatrix[1][1];
	rotationMatrix.m_mat[1][2] = quaternionMatrix[2][1];
	rotationMatrix.m_mat[1][3] = 0.0f;

	rotationMatrix.m_mat[2][0] = quaternionMatrix[0][2];
	rotationMatrix.m_mat[2][1] = quaternionMatrix[1][2];
	rotationMatrix.m_mat[2][2] = quaternionMatrix[2][2];
	rotationMatrix.m_mat[2][3] = 0.0f;

	rotationMatrix.m_mat[3][0] = 0.0f;
	rotationMatrix.m_mat[3][1] = 0.0f;
	rotationMatrix.m_mat[3][2] = 0.0f;
	rotationMatrix.m_mat[3][3] = 1.0f;


	scaleMatrix.setScale(this->m_localScale);


	translateMatrix.setTranslation(this->m_localPosition);
	modelMatrix = rotationMatrix * scaleMatrix * translateMatrix;

	this->m_shaderInput.m_model = modelMatrix;
	this->m_shaderInput.m_proj = viewportParams.m_projection;
	this->m_shaderInput.m_view = viewportParams.m_view;
	TextureComponent* textureComponent = this->findComponent<TextureComponent>(ComponentType::TEXTURE);
	if (textureComponent)
	{
		deviceContext->setTexture(textureComponent->getTexture());
		Vec4 textureColor = textureComponent->getColor();
		this->m_shaderInput.m_red = textureColor.m_x;
		this->m_shaderInput.m_green = textureColor.m_y;
		this->m_shaderInput.m_blue = textureColor.m_z;
		this->m_shaderInput.m_alpha = textureColor.m_w;
	}
	else
	{
		deviceContext->setDefaultTexture();
		this->m_shaderInput.m_red = 1.0f;
		this->m_shaderInput.m_green = 1.0f;
		this->m_shaderInput.m_blue = 1.0f;
		this->m_shaderInput.m_alpha = 1.0f;
	}

	this->m_constantBuffer.update(deviceContext, &m_shaderInput);

	deviceContext->setVertexShader(this->m_vertexShader);
	deviceContext->setVertexConstantBuffer(this->m_constantBuffer.getBuffer());
	deviceContext->setPixelShader(this->m_pixelShader);
	deviceContext->setPixelConstantBuffer(this->m_constantBuffer.getBuffer());
	deviceContext->setVertexBuffer(&(m_vertexBuffer));
	deviceContext->setIndexBuffer(&(m_indexBuffer));
	deviceContext->drawIndexedTriangleList(this->m_indexBuffer.getSizeIndexList(), 0, 0);
}

void DefaultGraphicsPrimitive::release()
{
	this->m_vertexBuffer.release();
	this->m_constantBuffer.release();
	this->m_indexBuffer.release();
}
