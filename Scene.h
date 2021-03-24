#pragma once
#include "stdafx.h"


class Object;
class DebugWindowObject;
class Camera;
class RenderToTextureClass;
class ShadowMapRenderer;
class Framework;
class Texture;
class LightManager;
class TextureManager;

struct CB_PASS_INFO {
	XMFLOAT4X4	m_xmf4x4CameraView;
	XMFLOAT4X4	m_xmf4x4CameraProjection;
	XMFLOAT4X4	m_xmf4x4CameraViewInv;
	XMFLOAT4X4	m_xmf4x4CameraProjectionInv;
	XMFLOAT4X4	m_xmf4x4TextureTransform;
	XMFLOAT3	m_xmf3CameraPosition;
	float		m_xmfCurrentTime;
};


class Scene
{
protected:
	ID3D12RootSignature*		m_pd3dRootSignature;
	ID3D12Device*				m_pd3dDevice;
	ID3D12GraphicsCommandList*	m_pd3dCommandList;
	ID3D12DescriptorHeap*		m_pd3dCbvSrvDescriptorHeap;

	D3D12_CPU_DESCRIPTOR_HANDLE	m_d3dCbvCPUDescriptorStartHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE	m_d3dCbvGPUDescriptorStartHandle;
	D3D12_CPU_DESCRIPTOR_HANDLE	m_d3dSrvCPUDescriptorStartHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE	m_d3dSrvGPUDescriptorStartHandle;


	vector<DebugWindowObject*>					m_vecDebugWindow;
	vector<Object*>								m_vecObject;
	unordered_map<string, ID3D12PipelineState*> m_uomPipelineStates;

	LightManager*								m_LightMng;
	TextureManager* m_TextureMng;

	ID3D12Resource*								m_pd3dcbPassInfo;
	CB_PASS_INFO*								m_pcbMappedPassInfo;
	D3D12_GPU_DESCRIPTOR_HANDLE					m_d3dCbvGPUPassInfoHandle;


	Framework*									m_pFramework;
	Camera*										m_pCamera;
	float										m_fCurrentTime = 0;


public:



	bool test = false;
	UINT camLightIdx = 0;

public:
	virtual void Init(Framework* pFramework, ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void RenderPass1();
	virtual void RenderPass2();
	virtual void Update(float fTimeElapsed);
	virtual void Input(UCHAR* pKeyBuffer, float fTimeElapsed);

	virtual void Release();

protected:
	virtual ID3D12RootSignature* CreateRootSignature();
	virtual void CreateDescriptorHeap();
	virtual void CreateCBV() {}
	virtual void CreateSRV() {}
	virtual void CreatePSO();


	void CreatePassInfoShaderResource();
	void UpdatePassInfoAboutCamera();


protected:
	/*==============================================================================
	* For Test!!
	*
	==============================================================================*/
	void ReloadLight();



};

