#pragma once
#ifndef CANNON_DEFINED
#define CANNON_DEFINED

#include <vector>
#include "Tank.h"

// �C���N���X
class Cannon : public Tank
{
public:
	// �R���X�g���N�^
	Cannon();
	// �p�[�c��ǉ�����
	void AddParts(Tank* tank) override;
	// �p�[�c���擾����
	Tank* GetParts() override;
	// �V���b�g�ł�
	void Shot(std::vector<Bullet*>& bullets, BulletFactory* bulletFactory) override;
	// ���������� 
	void Initialize() override;
	// �X�V���� 
	void Update(const DX::StepTimer& timer) override;
	// �`�悷��
	void Render(DirectX::SpriteBatch& spriteBatch,
		DirectX::SimpleMath::Vector2& position,
		float angle,
		DirectX::SimpleMath::Vector4& color) override;
	// �㏈���������Ȃ�
	void Finalize() override;
	// �f�X�g���N�^
	~Cannon() override {}

private:
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ����
	float m_angle;
};

#endif // CANNON_DEFINED
