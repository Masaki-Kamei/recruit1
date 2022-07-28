using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisionDetection : MonoBehaviour
{
    //高さ割合
   /* [Header("踏みつけ判定の高さの割合")]
    public float stepOnRate;
    //当たり判定の初期化
    private CapsuleCollider2D capcol = null;
    void Start()
    {
        //当たり判定の取得
        capcol = GetComponent<CapsuleCollider2D>();
    }

    //当たった時の処理
    private void OnCollisionEnter2D(Collision2D collision)
    {
        //床だったら
        if (collision.gameObject.tag == "Floor")
        {
            //当たった相手のオブジェクトの情報取得
            ContactPoint2D[] points = collision.contacts;
            //踏みつけ判定になる高さ
            float stepOnHeight = (capcol.size.y * (stepOnRate / 100f));
            //踏みつけ判定のワールド座標
            float judgePos = transform.position.y - (capcol.size.y / 2f) + stepOnHeight;
            //配列全てを参照
            foreach (ContactPoint2D p in collision.contacts)
            {
                //相手のオブジェクトよりプレイヤーの高さが高いときの当たり判定の処理
                if (p.point.y <= transform.position.y - (capcol.size.y / 2f))
                {
                    Debug.Log("着地");
                }
                //相手のオブジェクトよりプレイヤーの高さが低いときの当たり判定の処理
                else if (p.point.y > transform.position.y - (capcol.size.y / 2f))
                {
                    Debug.Log("壁だああああああ");

                }
            }
        }
    }*/
}
