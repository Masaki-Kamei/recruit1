using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class InvincibleEnemy : NormalEnemy
{
    // Start is called before the first frame update
    void Start()
    {
        base.Start();
    }

    // Update is called once per frame
    void Update()
    {
        base.Update();

    }

    override protected void OnCollisionEnter2D(Collision2D collision)
    {

        if (collision.gameObject.tag == "Player")
        {

            //������������̃I�u�W�F�N�g�̏��擾
            ContactPoint2D[] points = collision.contacts;
            //���݂�����̃��[���h���W
            float judgeUpPos = transform.position.y + (capcol.size.y / 2f);



            foreach (ContactPoint2D p in collision.contacts)
            {
                if (collision.gameObject.GetComponent<DefaultPlayer>().GetPlayerId() == 1)
                {

                    //����̃I�u�W�F�N�g��荂���������Ƃ��̓����蔻��̏���
                    if (p.point.y >= judgeUpPos)
                    {
                        Debug.Log("���G");

                        break;

                    }
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
                else
                {
                    if (collision.gameObject.GetComponent<DefaultPlayer>().GetInvincibleTrigger() == false)
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

}
