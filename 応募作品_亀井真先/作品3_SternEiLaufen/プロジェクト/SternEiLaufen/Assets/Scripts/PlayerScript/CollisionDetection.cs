using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisionDetection : MonoBehaviour
{
    //��������
   /* [Header("���݂�����̍����̊���")]
    public float stepOnRate;
    //�����蔻��̏�����
    private CapsuleCollider2D capcol = null;
    void Start()
    {
        //�����蔻��̎擾
        capcol = GetComponent<CapsuleCollider2D>();
    }

    //�����������̏���
    private void OnCollisionEnter2D(Collision2D collision)
    {
        //����������
        if (collision.gameObject.tag == "Floor")
        {
            //������������̃I�u�W�F�N�g�̏��擾
            ContactPoint2D[] points = collision.contacts;
            //���݂�����ɂȂ鍂��
            float stepOnHeight = (capcol.size.y * (stepOnRate / 100f));
            //���݂�����̃��[���h���W
            float judgePos = transform.position.y - (capcol.size.y / 2f) + stepOnHeight;
            //�z��S�Ă��Q��
            foreach (ContactPoint2D p in collision.contacts)
            {
                //����̃I�u�W�F�N�g���v���C���[�̍����������Ƃ��̓����蔻��̏���
                if (p.point.y <= transform.position.y - (capcol.size.y / 2f))
                {
                    Debug.Log("���n");
                }
                //����̃I�u�W�F�N�g���v���C���[�̍������Ⴂ�Ƃ��̓����蔻��̏���
                else if (p.point.y > transform.position.y - (capcol.size.y / 2f))
                {
                    Debug.Log("�ǂ�������������");

                }
            }
        }
    }*/
}
