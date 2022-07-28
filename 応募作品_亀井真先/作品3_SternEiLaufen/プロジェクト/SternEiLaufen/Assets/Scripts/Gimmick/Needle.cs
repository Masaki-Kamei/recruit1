using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Needle : MonoBehaviour
{

    protected SpriteRenderer sr = null;

    //高さ割合
    [Header("踏みつけ判定の高さの割合")]
    protected float stepOnRate;
    //当たり判定の初期化
    protected BoxCollider2D capcol = null;

    private GameObject Player;
    // Start is called before the first frame update
    public void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        //当たり判定の取得
        capcol = GetComponent<BoxCollider2D>();
        Player = GameObject.Find("Egg 1");
    }

    // Update is called once per frame
    public void Update()
    {
        //画面に映っているなら
        if (sr.isVisible)
        {
            Debug.Log("画面に見えている");

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
                Debug.Log("ダメージ");
                collision.gameObject.GetComponent<DefaultPlayer>().Damage();

                Destroy(this.gameObject);
            }
        }


    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {

            //当たった相手のオブジェクトの情報取得
            ContactPoint2D[] points = collision.contacts;
            //踏みつけ判定のワールド座標
            float judgeUpPos = transform.position.y + (capcol.size.y / 2f);



            foreach (ContactPoint2D p in collision.contacts)
            {

                //相手のオブジェクトより高さが高いときの当たり判定の処理
                if (p.point.y >= judgeUpPos)
                {
                    Debug.Log("無敵");

                    break;

                }
                else
                {
                    Debug.Log("ダメージ");
                    collision.gameObject.GetComponent<DefaultPlayer>().Damage();

                }

            }

        }

    }
}
