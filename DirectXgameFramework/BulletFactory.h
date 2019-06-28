#ifndef BULLET_FACTORY
#define BULLET_FACTORY

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <wrl/client.h>
#include <vector>

#include "Bullet.h"

// Tank�t�@�N�g���N���X
class BulletFactory
{
public:
	// �R���X�g���N�^
	BulletFactory(std::vector<Bullet*>* bullets);
	// �^���N�̃p�[�c�𐶐�����
	Bullet* Create(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity);
	Bullet* CreateBomb(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity);
	Bullet* CreateScattering(const DirectX::SimpleMath::Vector2 & position, const std::deque<Scattering::Task>& tasks);
	// ����������
	void Initialize();
	std::vector<Bullet*>& GetBullets();

private:
	std::vector<Bullet*>* m_bullets;
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
