// -----------------------------------------------------------------------
// 
// MPRのシェーダー
// 
//                                                              MPR.hlsli
// -----------------------------------------------------------------------

// グローバル変数	
Texture2D g_Texture: register(t0);   //テクスチャーは レジスターt(n)

SamplerState g_samLinear : register(s0);//サンプラーはレジスターs(n)
SamplerState g_samBorder : register(s1);//サンプラーはレジスターs(n)

// MPR用のコンスタントバッファ
cbuffer global:register(b0)
{
	float2 g_ViewPort;  // ビューポート（スクリーン）サイズ
	float2 g_Info;      // 指定情報（x:エフェクト種別 y:種別サブ）
};

// 構造体
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

//
// 1:色のぼかし関数
//
float4 Blur(VS_OUTPUT In, float2 Dim )
{
	float4 Color;
	float4 border = float4(0, 0, 0, 0);
	float  BW = 2.0f;      // どれだけ離れた点を隣と見なすか

	// 近接９点
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y));  // 上左
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y));            // 上
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y));   // 上右
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0));            // 左
	border += g_Texture.Sample(g_samBorder, In.Tex);                                     // 自分
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0));             // 右
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y));   // 下左
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y));             // 下
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y));    // 下右
	border /= 9;
	Color.rgb = border.rgb;
	Color.a = 1.0f;

	return Color;
}

//
// 2:エンボス関数
//
float4 Emboss(VS_OUTPUT In, float2 Dim )
{
	float4 Color;

	float4 texColor = g_Texture.Sample(g_samLinear, In.Tex);

	float4 border = float4(0, 0, 0, 0);
	float  BW = 1.0f;      // どれだけ離れた点を隣と見なすか

	// 近接９点
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * 0;  // 上左
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * 1;         // 上
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * 2;   // 上右
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;         // 左
	border += g_Texture.Sample(g_samBorder, In.Tex) * 1.5;                             // 自分
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0))* 1;          // 右
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -2;  // 下左
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;         // 下
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * 0;    // 下右

	// 効果のモノクロ化
	// RGB → YUV に変換。Yは輝度を表す
	// 公式 Y = 0.299R + 0.587G + 0.114B
	float Y = dot(border.rgb, float3(0.299, 0.587, 0.114));
	Color.rgb = texColor.rgb * Y * 1.0f;

	// 効果モノクロ化しない
	//Color.rgb = border.rgb;

	Color.a = 1.0f;
	
	return Color;
}

//
// 3:シャープネス関数
//
float4 Sharpness(VS_OUTPUT In, float2 Dim)
{
	float4 Color;

	float4 texColor = g_Texture.Sample(g_samLinear, In.Tex);

	float4 border = float4(0, 0, 0, 0);
	float  BW = -100.2f;      // どれだけ離れた点を隣と見なすか

	// 近接９点
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * -0.5;  // 上左
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * -1;           // 上
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * -0.5;   // 上右
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;           // 左
	border += g_Texture.Sample(g_samBorder, In.Tex) * 8;                                  // 自分
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -1;            // 右
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -0.5;   // 下左
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;            // 下
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -0.5;    // 下右

	// 効果のモノクロ化
	// RGB → YUV に変換。Yは輝度を表す
	// 公式 Y = 0.299R + 0.587G + 0.114B
	float Y = dot(border.rgb, float3(0.299, 0.587, 0.114));
	Color.rgb = texColor.rgb * Y;

	//Color.rgb = border.rgb;

	Color.a = 1.0f;

	return Color;
}

//
// 4:輪郭線抽出関数
//
float4 BorderLine(VS_OUTPUT In, float2 Dim)
{
	float4 Color;

	float4 texColor = g_Texture.Sample(g_samLinear, In.Tex);

	float4 border = float4(0, 0, 0, 0);
	float  BW = 1.1f;      // どれだけ離れた点を隣と見なすか
	float  Y;


	// 輪郭線抽出の方法
	if (g_Info.y == 0)
	{
		// エッジの強調手法により輪郭線を抽出する

		float  BW = 1.1f;      // どれだけ離れた点を隣と見なすか

		// 上下左右の４＋１点のみ
		//border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * -1;  // 上
		//border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;  // 左
		//border += g_Texture.Sample(g_samBorder, In.Tex) * 4;                            // 自分
		//border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -1;   // 右
		//border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;   // 下

		// 近接９点
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * -0.5;  // 上左
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * -1;              // 上
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * -0.5;   // 上右
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;              // 左
		border += g_Texture.Sample(g_samBorder, In.Tex) * 6;                                        // 自分
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -1;               // 右
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -0.5;   // 下左
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;               // 下
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -0.5;    // 下右

		// モノクロ化
		// RGB → YUV に変換。Yは輝度を表す
		// 公式 Y = 0.299R + 0.587G + 0.114B
		Y = dot(border.rgb, float3(0.299, 0.587, 0.114));

		// ここで反転して、強調するためPowする
		//Y = pow(1.0f - Y, 30.0f);
		Y = pow(1.0f - Y, 15.0f);

		// step関数。第１引数が第２引数より小さいときは１をそれ以外は０を返す
		//Y = step(0.2, Y);
		Y = step(0.1, Y);

	}
	else {		// 視線と法線の内積値を使用して輪郭線を抽出する

		float  BW = 1.0f;      // どれだけ離れた点を隣と見なすか
/*
		// 近接９点(縦方向)
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * 1;  // 上左
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * 0;              // 上
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * -1;   // 上右
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * 2;              // 左
		border += g_Texture.Sample(g_samBorder, In.Tex) * 0;                                        // 自分
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -2;               // 右
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * 1;   // 下左
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * 0;               // 下
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -1;    // 下右

		// 近接９点(横方向)
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * 1;  // 上左
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * 2;              // 上
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * 1;   // 上右
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * 0;              // 左
		border += g_Texture.Sample(g_samBorder, In.Tex) * 0;                                        // 自分
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * 0;               // 右
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -1;   // 下左
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -2;               // 下
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -1;    // 下右
*/

		// 近接９点
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * -0.5;  // 上左
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * -1;              // 上
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * -0.5;   // 上右
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;              // 左
		border += g_Texture.Sample(g_samBorder, In.Tex) * 6;                                        // 自分
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -1;               // 右
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -0.5;   // 下左
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;               // 下
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -0.5;    // 下右

		// 透明度ａの中に入っている視線と法線の内積値を使用して輪郭線を抽出する
		Y = border.a;

		// ここで反転して、強調するためPowする
		//Y = pow(1.0f - Y, 30.0f);
		Y = pow(1.0f - Y, 10.0f);

		// step関数。第１引数が第２引数より小さいときは１をそれ以外は０を返す
		//Y = step(0.2, Y);
		Y = step(0.1, Y);
	}

	Color.rgb = texColor.rgb * Y;
	//Color.rgb = float3(Y, Y, Y);         //
	//Color.rgb = float3(texColor.a, texColor.a, texColor.a);         //

	Color.a = 1.0f;

	return Color;
}

//
// バーテックスシェーダー
//
VS_OUTPUT VS(float4 Pos : POSITION, float2 UV : TEXCOORD)
{
	VS_OUTPUT Out;

	Out.Pos = Pos;

	Out.Pos.x = (Out.Pos.x / g_ViewPort.x) * 2 - 1;
	Out.Pos.y = 1 - (Out.Pos.y / g_ViewPort.y) * 2;

	Out.Tex = UV;

	return Out;
}

//
// ピクセルシェーダー	
//
float4 PS(VS_OUTPUT In) : SV_Target
{
	float4 Color;

	float2 Dim;
	float w, h;
	g_Texture.GetDimensions(w, h);
	Dim.x = 1.0f / w;
	Dim.y = 1.0f / h;

	switch (g_Info.x)
	{
	case 0:		// 通常描画（加工無し）
		float4 border = float4(0, 0, 0, 0);
		border += g_Texture.Sample(g_samLinear, In.Tex);
		Color.rgb = border.rgb;
		Color.a = 1.0f;

		break;
	case 1:		// 色のぼかし
		Color = Blur(In, Dim);
		break;
	case 2:		// エンボス
		Color = Emboss(In, Dim);
		break;
	case 3:		// シャープネス
		Color = Sharpness(In, Dim);
		break;
	case 4:		// 輪郭線抽出
		Color = BorderLine(In, Dim);
		break;
	}

	return Color;
}
