// -----------------------------------------------------------------------
// 
// �e�����X�^�e�B�b�N���b�V���̃V�F�[�_�[
// (�g�D�[�������_�����O  �Q�p�X����)
// 
//                                                FbxStaticMeshToon.hlsli
// -----------------------------------------------------------------------

// �O���[�o���ϐ�	
Texture2D g_Texture: register(t0);   //�e�N�X�`���[�� ���W�X�^�[t(n)
Texture2D g_NormalTexture : register(t1);   // �@���}�b�v
Texture2D g_ToonTexture: register(t4);   // Toon�e�N�X�`��

SamplerState g_samLinear : register(s0);//�T���v���[�̓��W�X�^�[s(n)


//  �R���X�^���g�o�b�t�@
cbuffer global
{
	matrix g_mW;          // ���[���h�s��
	matrix g_mWVP;        // ���[���h����ˉe�܂ł̕ϊ��s��
	float4 g_LightDir;    // ���C�g�̕����x�N�g��
	float4 g_EyePos;      // ���_�ʒu
	float4 g_Diffuse;     // �f�B�t���[�Y�F	
	float4 g_DrawInfo;     // �e����@x:�e�N�X�`���L�薳���B(�g���Ă��Ȃ�)
};

// �}�e���A���J���[�̃R���X�^���g�o�b�t�@
cbuffer global : register(b3)  
{
	float4 g_MatDiffuse = float4(0.5, 0.5, 0.5, 1);   // �f�B�t���[�Y�F	
	float4 g_MatSpecular = float4(0, 0, 0, 0);        // �X�y�L�����F
};

// �o�[�e�b�N�X�V�F�[�_�[�̏o�͍\����
// (�s�N�Z���V�F�[�_�[�̓��͂ƂȂ�)
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
	float3 normal : NORMAL;
	float4 lightTangentSpace : TEXCOORD1; // �ڋ�Ԃɕϊ����ꂽ���C�g�x�N�g��
	float2 ToonUV : TEXCOORD2;

};

// �ڋ�ԍs��̋t�s����Z�o
float4x4 InverseTangentMatrix(float3 tangent, float3 binormal, float3 normal)
{
	tangent = normalize(mul(tangent, (float3x3)g_mW));     // �ڐ������[���h�ϊ�����    
	binormal = normalize(mul(binormal, (float3x3)g_mW));   // �]�@�������[���h�ϊ�����
	normal = normalize(mul(normal, (float3x3)g_mW));       // �@�������[���h�ϊ�����

	float4x4 mat = { float4(tangent, 0.0f),
					float4(binormal, 0.0f), 
					float4(normal, 0.0f),
					{ 0.0f, 0.0f, 0.0f, 1.0f } };

	return transpose(mat); // �]�u�s��ɂ���
}

//
// �o�[�e�b�N�X�V�F�[�_�[  Pass1
//

VS_OUTPUT VS_TOON1(float3 Pos : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD, float3 Tangent : TANGENT, float3 Binormal : BINORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 Pos4 = float4(Pos, 1);
	float4 NormalWVP;

	output.Pos = mul(Pos4, g_mWVP);  // ���_�����[���h�E�r���[�E�v���W�F�N�V�����ϊ�����

	// �@�������[���h�E�r���[�E�v���W�F�N�V�����ϊ�����
	//NormalWVP = normalize(float4(mul(normalize(Normal), (float3x3)g_mWVP),0));
	NormalWVP = float4(mul(normalize(Normal), (float3x3)g_mWVP), 0);
	NormalWVP.z = 0;                      // �J�������猩�Ăy�����͂O�ɂ���
	NormalWVP = normalize(NormalWVP);

	// �g�D�[���C���N�i�֊s���j�p�ɏ����g�債�����_���o��
	// (�@�������Ɋg��)
	// �Ȃ��APos��w�l�ɂ͎�����̊g�嗦�������Ă���B�J�������牓���قǑ傫���l�ƂȂ�B
	output.Pos = output.Pos + NormalWVP*0.005f*output.Pos.w;

	return output;
}

//
// �o�[�e�b�N�X�V�F�[�_�[  Pass2
//

VS_OUTPUT VS_TOON2(float3 Pos : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD, float3 Tangent : TANGENT, float3 Binormal : BINORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 Pos4 = float4(Pos, 1);
	float4x4 inverseTangentMat;

	output.Pos = mul(Pos4, g_mWVP);  // ���_�����[���h�E�r���[�E�v���W�F�N�V�����ϊ�����

	// �ڐ��̌v�Z
	// �ڋ�ԍs��̋t�s����Z�o
	inverseTangentMat = InverseTangentMatrix(normalize(Tangent), normalize(Binormal), normalize(Normal));

	// ���C�g�x�N�g����ڋ�ԏ�ɕϊ�
	output.lightTangentSpace = mul(float4(g_LightDir.xyz, 1.0), inverseTangentMat);

	// �@�������[���h�ϊ�����
	output.normal = normalize(mul(Normal, (float3x3)g_mW));

	// �e�N�X�`�����W�͂��̂܂܏o��
	output.Tex = Tex;

	// �g�D�[���y�C���g�i�A�e�j�̃e�N�X�`�����WToonUV���쐬����B
	// ���̕\�ʂ̖��邳0.01�`0.99���e�N�X�`���̂t���W�ɂ���B
	// �i�{�[�_�[���C���̈ʒu�i0��1�j�������悤�ɂ���j
	output.ToonUV.x = min( 0.99f, max(0.01f, dot( output.normal, normalize(g_LightDir.xyz))));
	output.ToonUV.y = 0.01f;

	return output;
}


//
// �s�N�Z���V�F�[�_�[ Pass1
//

float4 PS_TOON1(VS_OUTPUT In) : SV_Target
{
	return float4(0, 0, 0, 1); // �C���N�̐F
}

//
// �s�N�Z���V�F�[�_�[ Pass2
//

float4 PS_TOON2(VS_OUTPUT In) : SV_Target
{
	float4 Color;      // �ŏI�o�͒l
	uint width, height;
	g_Texture.GetDimensions(width, height);  // �f�B�t���[�Y�e�N�X�`���̃T�C�Y�𓾂�

	// �e�N�X�`���J���[
	float4 texColor;

	if (width == 0)  // �f�B�t���[�Y�e�N�X�`�����Ȃ��Ƃ�  
	{
		texColor = g_MatDiffuse;    
	}
	else {
	    texColor = g_Texture.Sample(g_samLinear, In.Tex);
	}
	float4 texNormal = g_NormalTexture.Sample(g_samLinear, In.Tex);
	float4 texToon   = g_ToonTexture.Sample(g_samLinear, In.ToonUV);

	// �����̕������ݒ肳��Ă��邩�ǂ����̃`�F�b�N
	if (g_LightDir.x == 0 && g_LightDir.y == 0 && g_LightDir.z == 0)
	{
		// ���̕�����0,0,0�̏ꍇ�͌��̌v�Z�����Ȃ��ŕ`��
		Color.rgb = texColor.rgb * g_Diffuse.rgb;
		Color.a = texColor.a - (1 - g_Diffuse.a); 
	}
	else {
		if (texNormal.w == 1.0f) {
			// �@���}�b�v������ꍇ�͖@���}�b�s���O�t���̃��C�e�B���O
			float4 normalVector = 2.0 * texNormal - 1.0f;  // �x�N�g���֕ϊ�(�@���}�b�v�̐F��0�`1.0�B�����-1.0�`1.0�̃x�N�g���͈͂ɂ���)
			normalVector = normalize(normalVector);  // �@���x�N�g���̐��K��
			float NMbright = dot(normalize(In.lightTangentSpace), normalVector);// ���C�g�̌����Ɩ@���}�b�v�̖@���ƂŖ��x�Z�o
			NMbright = max(0.0f, NMbright);   // �}�C�i�X��0�ɕ␳

			// �g�D�[�������_�����O
			Color.rgb = texColor.rgb * 1.0f * texToon.rgb * g_Diffuse.rgb;         // �o���v�}�b�s���O�Ȃ�
			//Color.rgb = texColor.rgb * 1.2f * NMbright * texToon.rgb * g_Diffuse.rgb;  // �o���v�}�b�s���O����(�������邭)
			Color.a = texColor.a - (1 - g_Diffuse.a); 
		}
		else {
			// �@���}�b�v���Z�b�g����Ă��Ȃ��ꍇ�́A�g�D�[�������_�����O
			Color.rgb = texColor.rgb * 1.0f * texToon.rgb * g_Diffuse.rgb;
			Color.a = texColor.a - (1 - g_Diffuse.a); 
		}
	}
	return saturate(Color);  // �ŏI�o�͒l��0�`�P�͈̔͂ɐ�������

}

