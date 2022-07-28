using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BaseScore : MonoBehaviour
{

    [SerializeField]
    [Tooltip("����������G�t�F�N�g(�p�[�e�B�N��)")]
    private ParticleSystem particle;
    [SerializeField]
    int AddScore = 0;
    public ColorGamut test;

    ScoreSE scoreSE;
    // Start is called before the first frame update
    void Start()
    {
        scoreSE = GetComponent<ScoreSE>();

    }

    // Update is called once per frame
    void Update()
    {
        
    }


    virtual protected void OnTriggerEnter2D(Collider2D collision)
    {
        // �W�����v��
        if (collision.gameObject.tag == "Player")
        {
            if (particle != null)
            {
                // �p�[�e�B�N���V�X�e���̃C���X�^���X�𐶐�����B
                ParticleSystem newParticle = Instantiate(particle);
                // �p�[�e�B�N���̔����ꏊ�����̃X�N���v�g���A�^�b�`���Ă���GameObject�̏ꏊ�ɂ���B
                newParticle.transform.position = this.transform.position;
                // �p�[�e�B�N���𔭐�������B
                newParticle.Play();
                Destroy(newParticle.gameObject, 1.0f);
            }

            scoreSE.StartSE();
            //����������폜
            Destroy(this.gameObject);
            ScoreUp();

        }

    }

    void ScoreUp()
    {
        Debug.Log("�X�R�A����");
        //�X�R�A�𑝂₷
        ScoreManager.AddScore(AddScore);
    }

}
