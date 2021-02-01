#include "graphics/OBJModel.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

OBJModel::OBJModel()
{
}

OBJModel::~OBJModel()
{
}

void OBJModel::init(std::string path, VertexShader * vertexShader, PixelShader * pixelShader, ID3D11Device * device)
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
	this->m_constantBuffer.load(&(m_shaderInput), sizeof(DefaultShaderInput), device);
}


void OBJModel::update(float deltaTime)
{
}
