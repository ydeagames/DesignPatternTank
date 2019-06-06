#pragma once
#ifndef TURRET_DEFINED
#define TURRET_DEFINED

#include "Tank.h"

// �C���N���X
class Turret : public Tank 
{
public:
	// �R���X�g���N�^
	Turret();
	// �p�[�c��ǉ�����
	void AddParts(Tank* tank) override;
	// �p�[�c���擾����
	Tank* GetParts() override;
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
	~Turret() override {}

private:
	Tank* m_tank;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

#endif // TURRET_DEFINED
