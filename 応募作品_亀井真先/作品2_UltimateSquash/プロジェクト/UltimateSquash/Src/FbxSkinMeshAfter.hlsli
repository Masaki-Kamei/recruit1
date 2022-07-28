// -----------------------------------------------------------------------
// 
// �e�����X�L�����b�V���̃V�F�[�_�[
// (�g�D�[�������_�����O  �֊s���`��i�Q�p�X�j����)
// 
//                                                   FbxSkinMeshToon.hlsli
// -----------------------------------------------------------------------

#define MAX_BONE 255

// �O���[�o���ϐ�	
Texture2D g_Texture: register(t0);   //�e�N�X�`���[�� ���W�X�^�[t(n)
Texture2D g_NormalTexture : register(t1);   // �@���}�b�v
Texture2D g_ToonTexture: register(t4);   // Toon�e�N�X�`��

SamplerState g_samLinear : register(s0);//�T���v���[�̓��W�X�^�[s(n)

// �R���X�^���g�o�b�t�@
// ���[���h����ˉe�܂ł̕ϊ��s��E��(b0)
cbuffer global : register(b0)
{
	matrix g_mW;          // ���[���h�s��
	matrix g_mWVP;        // ���[���h����ˉe�܂ł̕ϊ��s��
	float4 g_LightDir;    // ���C�g�̕����x�N�g��
	float4 g_EyePos;      // ���_�ʒu
	float4 g_Diffuse;     // �f�B�t���[�Y�F	
	float4 g_DRawInfo;     // �e����@x:�e�N�X�`���L�薳���B(�g���Ă��Ȃ�)
};

// �{�[���s��(b1)
cbuffer cbBones : register(b1)
{
	matrix BoneFramePose[MAX_BONE];		// �w��t���[���ł̃��b�V���ɉe����^����S�Ă̍��̃|�[�Y�s��
};

// �}�e���A���J���[�̃R���X�^���g�o�b�t�@
cbuffer global : register(b3)   
{
	float4 g_MatDiffuse = float4(0.5, 0.5, 0.5, 1);   // �f�B�t���[�Y�F	
	float4 g_MatSpecular = float4(0, 0, 0, 0);        // �X�y�L�����F
};

// �X�L�j���O��̒��_�E�@��������
struct Skin
{
	float4 Pos4;
	float3 Normal;
	float3 Tangent; // �ڐ�    
	float3 Binormal; // �]�@��  
};

// �o�[�e�b�N�X�V�F�[�_�[�̓��̓p�����[�^(���_�t�H�[�}�b�g�Ɠ���)
struct VS_IN
{
	float3 Pos     : POSITION;		// ���_���W
	float3 Normal  : NORMAL;		// �@��
	float2 Tex     : TEXCOORD;		// �e�N�Z��
	uint4  Bones   : BONE_INDEX;	// �{�[���̃C���f�b�N�X
	float4 Weights : BONE_WEIGHT;	// �E�F�C�g
	float3 Tangent : TANGENT; // �ڐ�
	float3 Binormal : BINORMAL; // �]�@��

};

// �o�[�e�b�N�X�V�F�[�_�[�̏o�͍\����
// (�s�N�Z���V�F�[�_�[�̓��͂ƂȂ�)
struct VS_OUTPUT
{
	float4 Pos    : SV_POSITION;
	float3 Normal : NORMAL;
	float2 Tex    : TEXCOORD;
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


// ���_���X�L�j���O�i�{�[���ɂ��ό`�j����T�u�֐�   
// �i�o�[�e�b�N�X�V�F�[�_�[�Ŏg�p�j
Skin SkinVert(VS_IN In)
{
	Skin Out;
	Out.Pos4 = float4(0.0f, 0.0f, 0.0f, 0.0f);
	Out.Normal = float3(0.0f, 0.0f, 0.0f);
	Out.Tangent = float3(0.0f, 0.0f, 0.0f);
	Out.Binormal = float3(0.0f, 0.0f, 0.0f);

	float4 pos4 = float4(In.Pos, 1);
	float3 normal = In.Normal;
	float3 tangent = In.Tangent;
	float3 binormal = In.Binormal;


	// �{�[��0
	uint iBone = In.Bones.x;
	float fWeight = In.Weights.x;
	matrix m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);
	// �{�[��1
	iBone = In.Bones.y;
	fWeight = In.Weights.y;
	m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);
	// �{�[��2
	iBone = In.Bones.z;
	fWeight = In.Weights.z;
	m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);
	// �{�[��3
	iBone = In.Bones.w;
	fWeight = In.Weights.w;
	m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);

	return Out;
}


//
// �o�[�e�b�N�X�V�F�[�_�[ Pass1
//         �g�D�[���C���N�i�֊s���j��`�悷��
//
VS_OUTPUT VS_AFTER1( VS_IN In )
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4x4 inverseTangentMat;
	float4 NormalWVP;

	Skin vSkinned = SkinVert(In);		// �X�L�j���O

	output.Pos = mul(vSkinned.Pos4, g_mWVP);  // ���_�����[���h�E�r���[�E�v���W�F�N�V�����ϊ�����

	// �@�������[���h�E�r���[�E�v���W�F�N�V�����ϊ�����
	//NormalWVP = normalize(float4(mul(vSkinned.Normal, (float3x3)g_mWVP),0));
	NormalWVP = float4(mul(normalize(vSkinned.Normal), (float3x3)g_mWVP), 0);
	//NormalWVP.z = 0;                      // �J�������猩�Ăy�����͂O�ɂ���
	NormalWVP = normalize(NormalWVP);

	// �g�D�[���C���N�i�֊s���j�p�ɏ����g�債�����_���o��
	// (�@�������Ɋg��)
	// �Ȃ��APos��w�l�ɂ͎�����̊g�嗦�������Ă���B�J�������牓���قǑ傫���l�ƂȂ�B
	output.Pos = output.Pos;
	//output.Pos.x += 0.1;

	return output;
}

//
// �o�[�e�b�N�X�V�F�[�_�[ Pass2
//            �g�D�[���y�C���g�i�A�e�𕽒R�ɂ��ĕ`�悷��j
//
VS_OUTPUT VS_AFTER2( VS_IN In )
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4x4 inverseTangentMat;

	Skin vSkinned = SkinVert(In);		// �X�L�j���O

	output.Pos = mul(vSkinned.Pos4, g_mWVP);  // ���_�����[���h�E�r���[�E�v���W�F�N�V�����ϊ�����
	output.Normal = mul(vSkinned.Normal, (float3x3)g_mW);     // �@�������[���h�ϊ�����
	output.Normal = normalize(output.Normal);     // �@���𐳋K������

	// �ڋ�ԍs��̋t�s����Z�o
	inverseTangentMat = InverseTangentMatrix(normalize(vSkinned.Tangent), normalize(vSkinned.Binormal), normalize(vSkinned.Normal));

	// ���C�g�x�N�g����ڋ�ԏ�ɕϊ�
	output.lightTangentSpace = mul(float4(g_LightDir.xyz, 1.0), inverseTangentMat);

	output.Tex = In.Tex;     // �e�N�X�`�����W�͂��̂܂܏o��

	// �g�D�[���y�C���g�i�A�e�j�̃e�N�X�`�����WToonUV���쐬����B
	// ���̕\�ʂ̖��邳0.01�`0.99���e�N�X�`���̂t���W�ɂ���B
	// �i�{�[�_�[���C���̈ʒu�i0��1�j�������悤�ɂ���j
	output.ToonUV.x = min( 0.99f, max(0.01f, dot(output.Normal, normalize(g_LightDir.xyz))));

	output.ToonUV.y = 0.01f;

	return output;
}


//
// �s�N�Z���V�F�[�_�[ Pass1
//         �g�D�[���C���N�i�֊s���j��`�悷��
//
float4 PS_AFTER1(VS_OUTPUT In) : SV_Target
{
	return float4(0, 183, 206, 0.5); // �C���N�̐F
}

//
// �s�N�Z���V�F�[�_�[ Pass2
//            �g�D�[���y�C���g�i�A�e�𕽒R�ɂ��ĕ`�悷��j
//
float4 PS_AFTER2(VS_OUTPUT In) : SV_Target
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

	if (g_LightDir.x == 0 && g_LightDir.y == 0 && g_LightDir.z == 0)
	{
		// ���̕�����0,0,0�̏ꍇ�͌��̌v�Z�����Ȃ��ŕ`��
		Color.rgb = texColor.rgb * g_Diffuse.rgb;
		Color.a = texColor.a - (1 - g_Diffuse.a); 
	}
	else {
		if (texNormal.w == 1.0f) {
			// �@���}�b�v������ꍇ�͖@���}�b�s���O�t���̃��C�e�B���O

			// �@���}�b�s���O�̖��邳�v�Z
			float4 normalVector = 2.0 * texNormal - 1.0f;  // �x�N�g���֕ϊ�(�@���}�b�v�̐F��0�`1.0�B�����-1.0�`1.0�̃x�N�g���͈͂ɂ���)
			normalVector = normalize(normalVector);  // �@���x�N�g���̐��K��
			//float NMbright = dot(normalize(In.lightTangentSpace), normalVector);// ���C�g�̌����Ɩ@���}�b�v�̖@���ƂŖ��x�Z�o
			float NMbright = dot(normalize(In.lightTangentSpace), normalVector) * 0.9f + 0.5f;// ���C�g�̌����Ɩ@���}�b�v�̖@���ƂŖ��x�Z�o
			NMbright = max(0.0f, NMbright);   // �}�C�i�X��0�ɕ␳

			// �g�D�[�������_�����O
			// �ʏ�̃e�N�X�`���F�itexColor�j�Ƀg�D�[���y�C���g�iToonUV�̃T���v���j���|�����킹��
			Color.rgb = texColor.rgb * 1.1f * texToon.rgb * g_Diffuse.rgb;         // �o���v�}�b�s���O�Ȃ�(�������邭)
			//Color.rgb = texColor.rgb * 1.2f * NMbright * texToon.rgb * g_Diffuse.rgb;  // �o���v�}�b�s���O����(�������邭)
			Color.a = texColor.a - (1 - g_Diffuse.a); 

		}
		else {
			// �@���}�b�v���Z�b�g����Ă��Ȃ��ꍇ�́A�g�D�[�������_�����O
			// �ʏ�̃e�N�X�`���F�itexColor�j�Ƀg�D�[���y�C���g�iToonUV�̃T���v���j���|�����킹��
			Color.rgb = texColor.rgb * 1.1f * texToon.rgb * g_Diffuse.rgb;    // (�������邭)
			Color.a = texColor.a - (1 - g_Diffuse.a); 
		}
	}
	return saturate(Color);  // �ŏI�o�͒l��0�`�P�͈̔͂ɐ�������
}

