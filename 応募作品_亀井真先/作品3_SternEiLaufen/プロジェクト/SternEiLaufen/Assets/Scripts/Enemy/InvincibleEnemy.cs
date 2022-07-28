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

            //当たった相手のオブジェクトの情報取得
            ContactPoint2D[] points = collision.contacts;
            //踏みつけ判定のワールド座標
            float judgeUpPos = transform.position.y + (capcol.size.y / 2f);



            foreach (ContactPoint2D p in collision.contacts)
            {
                if (collision.gameObject.GetComponent<DefaultPlayer>().GetPlayerId() == 1)
                {

                    //相手のオブジェクトより高さが高いときの当たり判定の処理
                    if (p.point.y >= judgeUpPos)
                    {
                        Debug.Log("無敵");

                        break;

                    }
                    else if (collision.gameObject.GetComponent<DefaultPlayer>().GetInvincibleTrigger() == false)
                    {
                            Debug.Log("ダメージ");
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
                        Debug.Log("ダメージ");
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
