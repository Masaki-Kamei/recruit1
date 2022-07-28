// -----------------------------------------------------------------------
// 
// MPR�̃V�F�[�_�[
// 
//                                                              MPR.hlsli
// -----------------------------------------------------------------------

// �O���[�o���ϐ�	
Texture2D g_Texture: register(t0);   //�e�N�X�`���[�� ���W�X�^�[t(n)

SamplerState g_samLinear : register(s0);//�T���v���[�̓��W�X�^�[s(n)
SamplerState g_samBorder : register(s1);//�T���v���[�̓��W�X�^�[s(n)

// MPR�p�̃R���X�^���g�o�b�t�@
cbuffer global:register(b0)
{
	float2 g_ViewPort;  // �r���[�|�[�g�i�X�N���[���j�T�C�Y
	float2 g_Info;      // �w����ix:�G�t�F�N�g��� y:��ʃT�u�j
};

// �\����
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

//
// 1:�F�̂ڂ����֐�
//
float4 Blur(VS_OUTPUT In, float2 Dim )
{
	float4 Color;
	float4 border = float4(0, 0, 0, 0);
	float  BW = 2.0f;      // �ǂꂾ�����ꂽ�_��ׂƌ��Ȃ���

	// �ߐڂX�_
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y));  // �㍶
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y));            // ��
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y));   // ��E
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0));            // ��
	border += g_Texture.Sample(g_samBorder, In.Tex);                                     // ����
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0));             // �E
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y));   // ����
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y));             // ��
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y));    // ���E
	border /= 9;
	Color.rgb = border.rgb;
	Color.a = 1.0f;

	return Color;
}

//
// 2:�G���{�X�֐�
//
float4 Emboss(VS_OUTPUT In, float2 Dim )
{
	float4 Color;

	float4 texColor = g_Texture.Sample(g_samLinear, In.Tex);

	float4 border = float4(0, 0, 0, 0);
	float  BW = 1.0f;      // �ǂꂾ�����ꂽ�_��ׂƌ��Ȃ���

	// �ߐڂX�_
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * 0;  // �㍶
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * 1;         // ��
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * 2;   // ��E
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;         // ��
	border += g_Texture.Sample(g_samBorder, In.Tex) * 1.5;                             // ����
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0))* 1;          // �E
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -2;  // ����
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;         // ��
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * 0;    // ���E

	// ���ʂ̃��m�N����
	// RGB �� YUV �ɕϊ��BY�͋P�x��\��
	// ���� Y = 0.299R + 0.587G + 0.114B
	float Y = dot(border.rgb, float3(0.299, 0.587, 0.114));
	Color.rgb = texColor.rgb * Y * 1.0f;

	// ���ʃ��m�N�������Ȃ�
	//Color.rgb = border.rgb;

	Color.a = 1.0f;
	
	return Color;
}

//
// 3:�V���[�v�l�X�֐�
//
float4 Sharpness(VS_OUTPUT In, float2 Dim)
{
	float4 Color;

	float4 texColor = g_Texture.Sample(g_samLinear, In.Tex);

	float4 border = float4(0, 0, 0, 0);
	float  BW = -100.2f;      // �ǂꂾ�����ꂽ�_��ׂƌ��Ȃ���

	// �ߐڂX�_
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * -0.5;  // �㍶
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * -1;           // ��
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * -0.5;   // ��E
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;           // ��
	border += g_Texture.Sample(g_samBorder, In.Tex) * 8;                                  // ����
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -1;            // �E
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -0.5;   // ����
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;            // ��
	border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -0.5;    // ���E

	// ���ʂ̃��m�N����
	// RGB �� YUV �ɕϊ��BY�͋P�x��\��
	// ���� Y = 0.299R + 0.587G + 0.114B
	float Y = dot(border.rgb, float3(0.299, 0.587, 0.114));
	Color.rgb = texColor.rgb * Y;

	//Color.rgb = border.rgb;

	Color.a = 1.0f;

	return Color;
}

//
// 4:�֊s�����o�֐�
//
float4 BorderLine(VS_OUTPUT In, float2 Dim)
{
	float4 Color;

	float4 texColor = g_Texture.Sample(g_samLinear, In.Tex);

	float4 border = float4(0, 0, 0, 0);
	float  BW = 1.1f;      // �ǂꂾ�����ꂽ�_��ׂƌ��Ȃ���
	float  Y;


	// �֊s�����o�̕��@
	if (g_Info.y == 0)
	{
		// �G�b�W�̋�����@�ɂ��֊s���𒊏o����

		float  BW = 1.1f;      // �ǂꂾ�����ꂽ�_��ׂƌ��Ȃ���

		// �㉺���E�̂S�{�P�_�̂�
		//border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * -1;  // ��
		//border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;  // ��
		//border += g_Texture.Sample(g_samBorder, In.Tex) * 4;                            // ����
		//border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -1;   // �E
		//border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;   // ��

		// �ߐڂX�_
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * -0.5;  // �㍶
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * -1;              // ��
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * -0.5;   // ��E
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;              // ��
		border += g_Texture.Sample(g_samBorder, In.Tex) * 6;                                        // ����
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -1;               // �E
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -0.5;   // ����
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;               // ��
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -0.5;    // ���E

		// ���m�N����
		// RGB �� YUV �ɕϊ��BY�͋P�x��\��
		// ���� Y = 0.299R + 0.587G + 0.114B
		Y = dot(border.rgb, float3(0.299, 0.587, 0.114));

		// �����Ŕ��]���āA�������邽��Pow����
		//Y = pow(1.0f - Y, 30.0f);
		Y = pow(1.0f - Y, 15.0f);

		// step�֐��B��P��������Q������菬�����Ƃ��͂P������ȊO�͂O��Ԃ�
		//Y = step(0.2, Y);
		Y = step(0.1, Y);

	}
	else {		// �����Ɩ@���̓��ϒl���g�p���ė֊s���𒊏o����

		float  BW = 1.0f;      // �ǂꂾ�����ꂽ�_��ׂƌ��Ȃ���
/*
		// �ߐڂX�_(�c����)
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * 1;  // �㍶
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * 0;              // ��
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * -1;   // ��E
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * 2;              // ��
		border += g_Texture.Sample(g_samBorder, In.Tex) * 0;                                        // ����
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -2;               // �E
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * 1;   // ����
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * 0;               // ��
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -1;    // ���E

		// �ߐڂX�_(������)
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * 1;  // �㍶
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * 2;              // ��
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * 1;   // ��E
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * 0;              // ��
		border += g_Texture.Sample(g_samBorder, In.Tex) * 0;                                        // ����
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * 0;               // �E
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -1;   // ����
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -2;               // ��
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -1;    // ���E
*/

		// �ߐڂX�_
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, -BW * Dim.y)) * -0.5;  // �㍶
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, -BW * Dim.y)) * -1;              // ��
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, -BW * Dim.y)) * -0.5;   // ��E
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, 0)) * -1;              // ��
		border += g_Texture.Sample(g_samBorder, In.Tex) * 6;                                        // ����
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, 0)) * -1;               // �E
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(-BW * Dim.x, BW * Dim.y)) * -0.5;   // ����
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(0, BW * Dim.y)) * -1;               // ��
		border += g_Texture.Sample(g_samBorder, In.Tex + float2(BW * Dim.x, BW * Dim.y)) * -0.5;    // ���E

		// �����x���̒��ɓ����Ă��鎋���Ɩ@���̓��ϒl���g�p���ė֊s���𒊏o����
		Y = border.a;

		// �����Ŕ��]���āA�������邽��Pow����
		//Y = pow(1.0f - Y, 30.0f);
		Y = pow(1.0f - Y, 10.0f);

		// step�֐��B��P��������Q������菬�����Ƃ��͂P������ȊO�͂O��Ԃ�
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
// �o�[�e�b�N�X�V�F�[�_�[
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
// �s�N�Z���V�F�[�_�[	
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
	case 0:		// �ʏ�`��i���H�����j
		float4 border = float4(0, 0, 0, 0);
		border += g_Texture.Sample(g_samLinear, In.Tex);
		Color.rgb = border.rgb;
		Color.a = 1.0f;

		break;
	case 1:		// �F�̂ڂ���
		Color = Blur(In, Dim);
		break;
	case 2:		// �G���{�X
		Color = Emboss(In, Dim);
		break;
	case 3:		// �V���[�v�l�X
		Color = Sharpness(In, Dim);
		break;
	case 4:		// �֊s�����o
		Color = BorderLine(In, Dim);
		break;
	}

	return Color;
}
