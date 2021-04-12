#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <DirectXMath.h>
#include "Light.h"
#include "Vertex.h"
#include "Animation.h"

using SHAPE = vector<Vertex>;

class Object;
class Material;
class MESH_DATA {
public:
	string name;
	SHAPE shape;
	bool isFbx = false;
};
struct VertexIdx {
	int vid, vtid, vnid;
};
struct OBJECT_DESC {
	XMFLOAT3	position		= XMFLOAT3(0, 0, 0);
	XMFLOAT3	rotation		= XMFLOAT3(0, 0, 0);
	string		model			= "";
	string		material		= "defaultMaterial";
	bool isMaterial = false;
};

class IImporter {
protected:
	XMFLOAT3	GetFloat3(stringstream& ss);
	XMFLOAT2	GetFloat2(stringstream& ss);
	float		GetFloat(stringstream& ss);
	bool		GetBool(stringstream& ss);
	string		GetPath(stringstream& ss);
	VertexIdx GetIdx(stringstream& ss) {
		string token;
		VertexIdx output;
		char* str_buff = new char[256];
		char* tok;
		char* next_tok = NULL;
		char seps[] = " ,\t\n/";

		getline(ss, token, ' ');
		strcpy_s(str_buff, 256, token.c_str());
		tok = strtok_s(str_buff, seps, &next_tok);
		output.vid = atoi(tok) - 1;
		cout << output.vid << " ";
		tok = strtok_s(next_tok, seps, &next_tok);
		output.vtid = atoi(tok) - 1;
		cout << output.vtid << " ";
		tok = strtok_s(next_tok, seps, &next_tok);
		output.vnid = atoi(tok) - 1;
		cout << output.vnid << " ";

		return output;
	}
};


class ObjectDataImporter : public IImporter {
public:
	vector<OBJECT_DESC> Load(const char* filePath);
};
class LightDataImporter : public IImporter {
public:
	vector<LIGHT_DESC> Load(const char* filePath);
};
class MeshDataImporter : public IImporter {
public:
	vector<MESH_DATA> Load(const char* filePath);
	vector<MESH_DATA> FBXLoad(const char* filePath);
};
class MaterialDataImporter : public IImporter {
public:
	void Load(const char* filePath);
};
class AssetListDataImporter : public IImporter {
public:
	void Load(
		ID3D12Device* pd3dDevice,
		ID3D12GraphicsCommandList* pd3dCommandList,
		D3D12_CPU_DESCRIPTOR_HANDLE& srvCpuHandle,
		D3D12_GPU_DESCRIPTOR_HANDLE& srvGpuHandle);
};
class AnimClipDataImporter : public IImporter {
public:
	AnimClip Load(const char* filePath);
};