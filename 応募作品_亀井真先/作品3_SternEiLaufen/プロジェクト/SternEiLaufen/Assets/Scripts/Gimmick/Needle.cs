using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Needle : MonoBehaviour
{

    protected SpriteRenderer sr = null;

    //��������
    [Header("���݂�����̍����̊���")]
    protected float stepOnRate;
    //�����蔻��̏�����
    protected BoxCollider2D capcol = null;

    private GameObject Player;
    // Start is called before the first frame update
    public void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        //�����蔻��̎擾
        capcol = GetComponent<BoxCollider2D>();
        Player = GameObject.Find("Egg 1");
    }

    // Update is called once per frame
    public void Update()
    {
        //��ʂɉf���Ă���Ȃ�
        if (sr.isVisible)
        {
            Debug.Log("��ʂɌ����Ă���");

        }

        if (Player.GetComponent<DefaultPlayer>().playerId == 1)
        {
            this.GetComponent<Collider2D>().isTrigger = false;
        }
        else
        {
            this.GetComponent<Collider2D>().isTrigger = true;

        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {

        if (collision.gameObject.tag == "Player")
        {

            if (collision.gameObject.GetComponent<DefaultPlayer>().GetInvincibleTrigger() == false)
            {
                Debug.Log("�_���[�W");
                collision.gameObject.GetComponent<DefaultPlayer>().Damage();

                Destroy(this.gameObject);
            }
        }


    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {

            //������������̃I�u�W�F�N�g�̏��擾
            ContactPoint2D[] points = collision.contacts;
            //���݂�����̃��[���h���W
            float judgeUpPos = transform.position.y + (capcol.size.y / 2f);



            foreach (ContactPoint2D p in collision.contacts)
            {

                //����̃I�u�W�F�N�g��荂���������Ƃ��̓����蔻��̏���
                if (p.point.y >= judgeUpPos)
                {
                    Debug.Log("���G");

                    break;

                }
                else
                {
                    Debug.Log("�_���[�W");
                    collision.gameObject.GetComponent<DefaultPlayer>().Damage();

                }

            }

        }

    }
}
