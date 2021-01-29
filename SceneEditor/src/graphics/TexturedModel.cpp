#include "graphics/TexturedModel.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

TexturedModel::TexturedModel()
{
}

TexturedModel::~TexturedModel()
{
}

void TexturedModel::init(std::string path, VertexShader * vertexShader, PixelShader * pixelShader, ID3D11Device * device)
{
	this->m_vertexShader = vertexShader;
	this->m_pixelShader = pixelShader;

	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err = "";

	tinyobj::LoadObj(&attribs, &shapes, &materials, &err, path.c_str());

	std::vector<VertexTexture> list_vertices;
	std::vector<unsigned int> list_indices;

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];

				VertexTexture vertex = { Vec3(vx, vy, vz), Vec2(tx, ty) };
				list_vertices.push_back(vertex);
				list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

	this->m_vertexBuffer.load(&(list_vertices[0]), sizeof(VertexTexture), (UINT) list_vertices.size(), device);

	this->m_indexBuffer.load(&(list_indices[0]), (UINT) list_indices.size(), device);

	Mat4 identityMatrix;
	identityMatrix.setIdentity();
	this->m_matrices.m_model = identityMatrix;
	this->m_matrices.m_proj = identityMatrix;
	this->m_matrices.m_view = identityMatrix;

	this->m_constantBuffer.load(&(m_matrices), sizeof(CoordinateSystemMatrices), device);
}

void TexturedModel::setTexture(Texture * texture)
{
	this->m_texture = texture;
}

void TexturedModel::update(float deltaTime)
{
}

void TexturedModel::draw(DeviceContext * deviceContext, ViewportParams viewportParams)
{
	Mat4 modelMatrix;
	Mat4 translateMatrix;
	Mat4 scaleMatrix;
	Mat4 rotationXMatrix;
	Mat4 rotationYMatrix;
	Mat4 rotationZMatrix;

	scaleMatrix.setScale(this->m_localScale);
	rotationZMatrix.setRotationZ(this->m_localRotation.m_z);
	rotationYMatrix.setRotationY(this->m_localRotation.m_y);
	rotationXMatrix.setRotationX(this->m_localRotation.m_x);
	translateMatrix.setTranslation(this->m_localPosition);
	modelMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix * scaleMatrix * translateMatrix;

	this->m_matrices.m_model = modelMatrix;
	this->m_matrices.m_proj = viewportParams.m_projection;
	this->m_matrices.m_view = viewportParams.m_view;

	this->m_constantBuffer.update(deviceContext, &m_matrices);

	deviceContext->setVertexShader(this->m_vertexShader);
	deviceContext->setVertexConstantBuffer(this->m_constantBuffer.getBuffer());
	deviceContext->setPixelShader(this->m_pixelShader);
	deviceContext->setVertexBuffer(&(m_vertexBuffer));
	deviceContext->setIndexBuffer(&(m_indexBuffer));
	deviceContext->setTexture(this->m_texture);
	deviceContext->drawIndexedTriangleList(this->m_indexBuffer.getSizeIndexList(), 0, 0);
}

void TexturedModel::release()
{
	this->m_vertexBuffer.release();
	this->m_constantBuffer.release();
	this->m_indexBuffer.release();
	this->m_texture->release();
	delete m_texture;
}
