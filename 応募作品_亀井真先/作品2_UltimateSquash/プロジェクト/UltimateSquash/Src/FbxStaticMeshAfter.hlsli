// -----------------------------------------------------------------------
// 
// Ｆｂｘスタティックメッシュのシェーダー
// (トゥーンレンダリング  輪郭線描画（２パス）方式)
// 
//                                                FbxStaticMeshToon.hlsli
// -----------------------------------------------------------------------

// グローバル変数	
Texture2D g_Texture: register(t0);   //テクスチャーは レジスターt(n)
Texture2D g_NormalTexture : register(t1);   // 法線マップ
Texture2D g_ToonTexture: register(t4);   // Toonテクスチャ

SamplerState g_samLinear : register(s0);//サンプラーはレジスターs(n)


//  コンスタントバッファ
cbuffer global
{
	matrix g_mW;          // ワールド行列
	matrix g_mWVP;        // ワールドから射影までの変換行列
	float4 g_LightDir;    // ライトの方向ベクトル
	float4 g_EyePos;      // 視点位置
	float4 g_Diffuse;     // ディフューズ色	
	float4 g_DrawInfo;     // 各種情報　x:テクスチャ有り無し。(使っていない)
};

// マテリアルカラーのコンスタントバッファ
cbuffer global : register(b3)   
{
	float4 g_MatDiffuse = float4(0.5, 0.5, 0.5, 1);   // ディフューズ色	
	float4 g_MatSpecular = float4(0, 0, 0, 0);        // スペキュラ色
};

// バーテックスシェーダーの出力構造体
// (ピクセルシェーダーの入力となる)
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
	float3 normal : NORMAL;
	float4 lightTangentSpace : TEXCOORD1; // 接空間に変換されたライトベクトル
	float2 ToonUV : TEXCOORD2;

};

// 接空間行列の逆行列を算出
float4x4 InverseTangentMatrix(float3 tangent, float3 binormal, float3 normal)
{
	float4x4 mat = { float4(tangent, 0.0f), 
					float4(binormal, 0.0f), 
					float4(normal, 0.0f),
					{ 0.0f, 0.0f, 0.0f, 1.0f } };

	return transpose(mat); // 転置行列にする
}

//
// バーテックスシェーダー  Pass1
//
VS_OUTPUT VS_AFTER1(float3 Pos : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD, float3 Tangent : TANGENT, float3 Binormal : BINORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 Pos4 = float4(Pos, 1);
	float4 NormalWVP;

	output.Pos = mul(Pos4, g_mWVP);  // 頂点をワールド・ビュー・プロジェクション変換する

	// 法線をワールド・ビュー・プロジェクション変換する
	//NormalWVP = normalize(float4(mul(normalize(Normal), (float3x3)g_mWVP),0));
	NormalWVP = float4(mul(normalize(Normal), (float3x3)g_mWVP), 0);
	NormalWVP.z = 0;                      // カメラから見てＺ方向は０にする
	NormalWVP = normalize(NormalWVP);

	// トゥーンインク（輪郭線）用に少し拡大した頂点を出力
	// (法線方向に拡大)
	// なお、Posのw値には視錐台の拡大率が入っている。カメラから遠いほど大きい値となる。
	output.Pos = output.Pos + NormalWVP*0.005f*output.Pos.w;

	return output;
}

//
// バーテックスシェーダー  Pass2
//
VS_OUTPUT VS_AFTER2(float3 Pos : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD, float3 Tangent : TANGENT, float3 Binormal : BINORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 Pos4 = float4(Pos, 1);
	float4x4 inverseTangentMat;

	output.Pos = mul(Pos4, g_mWVP);  // 頂点をワールド・ビュー・プロジェクション変換する

	// 接線の計算
	// 接空間行列の逆行列を算出
	inverseTangentMat = InverseTangentMatrix(normalize(Tangent), normalize(Binormal), normalize(Normal));

	// ライトベクトルを接空間上に変換
	output.lightTangentSpace = mul(float4(g_LightDir.xyz, 1.0), inverseTangentMat);

	// 法線をワールド変換する
	output.normal = normalize(mul(Normal, (float3x3)g_mW));

	// テクスチャ座標はそのまま出力
	output.Tex = Tex;

	// トゥーンペイント（陰影）のテクスチャ座標ToonUVを作成する。
	// 物体表面の明るさ0.01〜0.99をテクスチャのＵ座標にする。
	// （ボーダーラインの位置（0や1）を避けるようにする）
	output.ToonUV.x = min( 0.99f, max(0.01f, dot( output.normal, normalize(g_LightDir.xyz))));
	output.ToonUV.y = 0.01f;

	return output;
}


//
// ピクセルシェーダー Pass1
//
float4 PS_AFTER1(VS_OUTPUT In) : SV_Target
{
	return float4(0, 0, 0, 1); // インクの色
}

//
// ピクセルシェーダー Pass2
//
float4 PS_AFTER2(VS_OUTPUT In) : SV_Target
{
	float4 Color;      // 最終出力値
	uint width, height;
	g_Texture.GetDimensions(width, height);  // ディフューズテクスチャのサイズを得る

	// テクスチャカラー
	float4 texColor;

	if (width == 0)  // ディフューズテクスチャがないとき 
	{
		texColor = g_MatDiffuse; 
	}
	else {
	    texColor = g_Texture.Sample(g_samLinear, In.Tex);
	}
	float4 texNormal = g_NormalTexture.Sample(g_samLinear, In.Tex);
	float4 texToon   = g_ToonTexture.Sample(g_samLinear, In.ToonUV);

	// 光源の方向が設定されているかどうかのチェック
	if (g_LightDir.x == 0 && g_LightDir.y == 0 && g_LightDir.z == 0)
	{
		// 光の方向が0,0,0の場合は光の計算をしないで描画
		Color.rgb = texColor.rgb * g_Diffuse.rgb;
		Color.a = texColor.a - (1 - g_Diffuse.a); 
	}
	else {
		if (texNormal.w == 1.0f) {
			// 法線マップがある場合は法線マッピング付きのライティング
			float4 normalVector = 2.0 * texNormal - 1.0f;  // ベクトルへ変換(法線マップの色は0〜1.0。これを-1.0〜1.0のベクトル範囲にする)
			normalVector = normalize(normalVector);  // 法線ベクトルの正規化
			float NMbright = dot(normalize(In.lightTangentSpace), normalVector);// ライトの向きと法線マップの法線とで明度算出
			NMbright = max(0.0f, NMbright);   // マイナスは0に補正

			// トゥーンレンダリング
			Color.rgb = texColor.rgb * 1.0f * texToon.rgb * g_Diffuse.rgb;         // バンプマッピングなし
			//Color.rgb = texColor.rgb * 1.2f * NMbright * texToon.rgb * g_Diffuse.rgb;  // バンプマッピングあり(少し明るく)
			Color.a = texColor.a - (1 - g_Diffuse.a); 
		}
		else {
			// 法線マップがセットされていない場合は、トゥーンレンダリング
			Color.rgb = texColor.rgb * 1.0f * texToon.rgb * g_Diffuse.rgb;
			Color.a = texColor.a - (1 - g_Diffuse.a); 
		}
	}
	return saturate(Color);  // 最終出力値を0〜１の範囲に制限する

}

