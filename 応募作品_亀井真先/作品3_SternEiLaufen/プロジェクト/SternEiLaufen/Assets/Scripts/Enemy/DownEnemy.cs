using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DownEnemy : MonoBehaviour
{
    protected SpriteRenderer sr = null;
    EnmSound enmSound;

    //高さ割合
    [Header("踏みつけ判定の高さの割合")]
    protected float stepOnRate;
    //当たり判定の初期化
    protected BoxCollider2D capcol = null;
    // Start is called before the first frame update
    virtual public void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        //当たり判定の取得
        capcol = GetComponent<BoxCollider2D>();
        enmSound = GetComponent<EnmSound>();

    }

    // Update is called once per frame
    virtual public void Update()
    {
        //画面に映っているなら
        if (sr.isVisible)
        {
            Debug.Log("画面に見えている");

        }

    }


    virtual protected void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            //当たった相手のオブジェクトの情報取得
            ContactPoint2D[] points = collision.contacts;
            //踏みつけ判定になる高さ
            float stepOnHeight = (capcol.size.y * (stepOnRate / 100f));
            //踏みつけ判定のワールド座標
            float judgeUpPos = transform.position.y + (capcol.size.y / 2f);
            float judgeDownPos = transform.position.y - (capcol.size.y / 2f) + 0.1f;

            //配列全てを参照
            foreach (ContactPoint2D p in collision.contacts)
            {

                //相手のオブジェクトより高さが高いときの当たり判定の処理
                if (p.point.y >= judgeUpPos)
                {
                    Debug.Log("踏んだ");
                    collision.gameObject.GetComponent<DefaultPlayer>().SteponEnmObj();
                    ScoreManager.AddScore(100);
                    enmSound.DeadSE();
                    Destroy(this.gameObject);
                    break;

                }
                //相手のオブジェクトより高さが低いときの当たり判定の処理
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

        }


    }
}
