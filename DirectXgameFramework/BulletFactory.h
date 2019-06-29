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
	BulletFactory(std::vector<std::unique_ptr<Bullet>>* bullets);

	// �^���N�̃p�[�c�𐶐�����
	template<typename T, typename... Args>
	std::unique_ptr<Bullet> Create(const DirectX::SimpleMath::Vector2& position, Args&&... args)
	{
		auto bullet = std::make_unique<T>(m_texture.Get(), position, std::forward<Args>(args)...);
		bullet->Initialize();
		return bullet;
	}

	template<typename T, typename... Args>
	void Instantiate(const DirectX::SimpleMath::Vector2& position, Args&&... args)
	{
		GetBullets().push_back(Create<T>(position, std::forward<Args>(args)...));
	}

	// ����������
	void Initialize();
	std::vector<std::unique_ptr<Bullet>>& GetBullets();

private:
	std::vector<std::unique_ptr<Bullet>>* m_bullets;
	//// �ʒu 
	//DirectX::SimpleMath::Vector2 m_position;
	//// ���x 
	//DirectX::SimpleMath::Vector2 m_velocity;
	// �F Color
	//DirectX::SimpleMath::Vector4 m_color;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

#endif	// BULLET_FACTORY
