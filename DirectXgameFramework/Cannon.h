#pragma once
#ifndef CANNON_DEFINED
#define CANNON_DEFINED

#include <vector>
#include "Tank.h"
#include "IShotStrategy.h"
#include "StepTimer.h"
#include "SpriteFont.h"

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
	void Shot(const DX::StepTimer& timer) override;
	// �V���b�g��؂�ւ���
	void SwitchShot(int d = 1) override;
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
	void SetBulletFactory(BulletFactory* bulletFactory) override;

private:
	BulletFactory* m_bulletFactory;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ����
	float m_angle;
	// �V���b�g�̎��
	int m_shotType;
	// �t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_font;
};

#endif // CANNON_DEFINED
