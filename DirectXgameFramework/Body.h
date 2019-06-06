#ifndef BODY_DEFINED
#define BODY_DEFINED

#include <vector>

#include "Tank.h"

// Body�N���X
class Body : public Tank 
{
public:
	// �R���X�g���N�^
	Body();
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
	~Body()override {}

private:
	Tank* m_tank;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

#endif // TANK_BODY
