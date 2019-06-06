#ifndef BULLET_FACTORY
#define BULLET_FACTORY

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <wrl/client.h>

#include "Bullet.h"

// Tank�t�@�N�g���N���X
class BulletFactory
{
public:
	// �R���X�g���N�^
	BulletFactory();
	// �^���N�̃p�[�c�𐶐�����
	Bullet* Create(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity);
	// ����������
	void Initialize();

private:
	//// �ʒu 
	//DirectX::SimpleMath::Vector2 m_position;
	//// ���x 
	//DirectX::SimpleMath::Vector2 m_velocity;
	// �F Color
	DirectX::SimpleMath::Vector4 m_color;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

#endif	// BULLET_FACTORY
