#ifndef DIRECTX11_DEFINED
#define DIRECTX11_DEFINED

#include <windows.h>
#include <d3d11.h>
#include <memory>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <SimpleMath.h>
#include <wrl.h>
#include <wrl/client.h>
#include "dx.h"

// Uncopyable�N���X
class Uncopyable 
{
protected:
	Uncopyable() = default;
	~Uncopyable() = default;
private:
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable& operator =(const Uncopyable&) = delete;
};

// Graphics�N���X
class DirectX11 : private Uncopyable 
{
private:
	// �R���X�g���N�^
	DirectX11() 
	{
	}

public:
	// DirectX11 Graphics�N���X�̃C���X�^���X���擾���� 
	static DirectX11& Get() 
	{
		if (m_directX.get() == nullptr) 
		{
			m_directX.reset(new DirectX11());
		}
		return *m_directX.get();
	}
	// DirectX11 Graphics�I�u�W�F�N�g��j������ 
	static void Dispose() 
	{
		m_directX.reset();
	}
	// �E�B���h�E�n���h�����擾���� 
	HWND GetHWnd() const
	{
		return m_hWnd;
	}
	// �E�B���h�E�n���h����ݒ肷�� 
	void SetHWnd(HWND hWnd) 
	{
		m_hWnd = hWnd;
	}
	// �E�B���h�E�����擾���� 
	int GetWidth() const
	{
		return m_width;
	}
	// �E�B���h�E����ݒ肷�� 
	void SetWidth(int width) 
	{
		m_width = width;
	}
	// �E�B���h�E�����擾���� 
	int GetHeight() const
	{
		return m_height;
	}
	// �E�B���h�E����ݒ肷�� 
	void SetHeight(int height) 
	{
		m_height = height;
	}
	// �f�o�C�X���擾���� Get device object
	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const
	{
		return m_device; 
	}
	// �f�o�C�X��ݒ肷�� Set device object
	void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device) 
	{
		m_device = device;
	}
	// �f�o�C�X�R���e�L�X�g���擾���� 
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() const
	{
		return m_context;
	}
	// �f�o�C�X�R���e�L�X�g��ݒ肷�� 
	void SetContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context) 
	{
		m_context = context;
	}

	// �X���b�v�`�F�C�����擾���� 
	Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() const
	{
		return m_swapChain;
	}
	// �X���b�v�`�F�C����ݒ肷��
	void SetSwapChain(Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain) 
	{
		m_swapChain = swapChain;
	}
	// �����_�[�^�[�Q�b�g�r���[���擾����
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const
	{
		return m_renderTargetView;
	}
	// �����_�[�^�[�Q�b�g�r���[��ݒ肷��
	void SetRenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView) {
		m_renderTargetView = renderTargetView;
	}

	// �f�v�X�X�e���V���r���[���擾���� 
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const
	{
		return m_depthStencilView;
	}
	// �f�v�X�X�e���V���r���[��ݒ肷�� 
	void SetDepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView) {
		m_depthStencilView = depthStencilView;
	}

	// �f�o�C�X�𐶐����� 
	void CreateDevice();
	// ���\�[�X�𐶐����� 
	void CreateResources();

	// �f�o�C�X���X�g�����������ꍇ 
	void OnDeviceLost();

private:
	static std::unique_ptr<DirectX11> m_directX;

	HWND m_hWnd;
	int  m_width;
	int  m_height;
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11Device> m_device1;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>	m_context;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context1;
	D3D_FEATURE_LEVEL  m_featureLevel;

	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain1;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
};

#endif	// DirectX11 GRAPHICS

