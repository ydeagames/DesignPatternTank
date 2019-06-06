#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "SimpleMath.h"
#include "WICTextureLoader.h"
#include "SpriteBatch.h"
#include "StepTimer.h"

class Bullet
{
	// �ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ���x
	DirectX::SimpleMath::Vector2 m_velocity;
	// �e�N�X�`���|�C���^
	ID3D11ShaderResourceView* m_texture;
	// �F
	DirectX::SimpleMath::Vector4 m_color;

public:
	Bullet(ID3D11ShaderResourceView* m_texture, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& velocity, DirectX::SimpleMath::Vector4& color);

	// ����������
	void Initialize();
	// �X�V����
	void Update(const DX::StepTimer& timer);
	// �`�悷��
	void Render(DirectX::SpriteBatch& spriteBatch);
	// �㏈���������Ȃ�
	void Finalize();

};

