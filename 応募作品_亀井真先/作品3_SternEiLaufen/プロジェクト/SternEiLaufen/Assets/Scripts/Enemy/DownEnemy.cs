using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DownEnemy : MonoBehaviour
{
    protected SpriteRenderer sr = null;
    EnmSound enmSound;

    //��������
    [Header("���݂�����̍����̊���")]
    protected float stepOnRate;
    //�����蔻��̏�����
    protected BoxCollider2D capcol = null;
    // Start is called before the first frame update
    virtual public void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        //�����蔻��̎擾
        capcol = GetComponent<BoxCollider2D>();
        enmSound = GetComponent<EnmSound>();

    }

    // Update is called once per frame
    virtual public void Update()
    {
        //��ʂɉf���Ă���Ȃ�
        if (sr.isVisible)
        {
            Debug.Log("��ʂɌ����Ă���");

        }

    }


    virtual protected void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            //������������̃I�u�W�F�N�g�̏��擾
            ContactPoint2D[] points = collision.contacts;
            //���݂�����ɂȂ鍂��
            float stepOnHeight = (capcol.size.y * (stepOnRate / 100f));
            //���݂�����̃��[���h���W
            float judgeUpPos = transform.position.y + (capcol.size.y / 2f);
            float judgeDownPos = transform.position.y - (capcol.size.y / 2f) + 0.1f;

            //�z��S�Ă��Q��
            foreach (ContactPoint2D p in collision.contacts)
            {

                //����̃I�u�W�F�N�g��荂���������Ƃ��̓����蔻��̏���
                if (p.point.y >= judgeUpPos)
                {
                    Debug.Log("����");
                    collision.gameObject.GetComponent<DefaultPlayer>().SteponEnmObj();
                    ScoreManager.AddScore(100);
                    enmSound.DeadSE();
                    Destroy(this.gameObject);
                    break;

                }
                //����̃I�u�W�F�N�g��荂�����Ⴂ�Ƃ��̓����蔻��̏���
                else if (collision.gameObject.GetComponent<DefaultPlayer>().GetInvincibleTrigger() == false)
                {
                    Debug.Log("�_���[�W");
                    collision.gameObject.GetComponent<DefaultPlayer>().Damage();
                    Destroy(this.gameObject);
                    break;


                }
                else if (collision.gameObject.GetComponent<DefaultPlayer>().GetInvincibleTrigger() == true)
                {
                    Destroy(this.gameObject);
                    break;

                }

            }

        }


    }
}
