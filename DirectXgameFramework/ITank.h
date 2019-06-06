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

// ITankインターフェイス
class ITank 
{
public:
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(const DX::StepTimer& timer) = 0;
	// 描画する
	virtual void Render(DirectX::SpriteBatch& spriteBatch,
		DirectX::SimpleMath::Vector2& position,
		float angle,
		DirectX::SimpleMath::Vector4& color) = 0;
	// 後処理をおこなう
	virtual void Finalize() = 0;
	// デストラクタ
	virtual ~ITank() = 0;
};

inline ITank::~ITank() {}

#endif // ITANK_DEFINED
