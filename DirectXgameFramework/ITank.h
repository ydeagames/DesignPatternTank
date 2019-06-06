#ifndef ITANK_DEFINED
#define ITANK_DEFINED

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <SpriteBatch.h>
#include "StepTimer.h"
#include "dx.h"
#include "DirectX11.h"

// ITank�C���^�[�t�F�C�X
class ITank 
{
public:
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(const DX::StepTimer& timer) = 0;
	// �`�悷��
	virtual void Render(DirectX::SpriteBatch& spriteBatch,
		DirectX::SimpleMath::Vector2& position,
		float angle,
		DirectX::SimpleMath::Vector4& color) = 0;
	// �㏈���������Ȃ�
	virtual void Finalize() = 0;
	// �f�X�g���N�^
	virtual ~ITank() = 0;
};

inline ITank::~ITank() {}

#endif // ITANK_DEFINED
