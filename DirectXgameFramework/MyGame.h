#ifndef MYGAME_DEFINED
#define MYGAME_DEFINED

#include "Game.h"
#include "Player.h"

class MyGame : public Game 
{
public:
	// �R���X�g���N�^
	MyGame(int width, int height);
	// ��������
	void Initialize() override;
	// �X�V����
	void Update(const DX::StepTimer& timer) override;
	// �`�悷��
	void Render(const DX::StepTimer& timer) override;
	// ��n��������
	void Finalize() override;

private:
	// DirectX11�O���t�B�b�N�X 
	DirectX11& m_directX = DirectX11::Get();

	// �v���C��
	std::unique_ptr<Player> m_player;
};

#endif	// MYGAME_DEFINED

