using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Collector : MonoBehaviour
{


    //当たったオブジェクトを非表示にする
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Ground")|| collision.CompareTag("GroundBonus"))
        {
            //オブジェクトを削除
            Destroy(collision.gameObject);
            //スクリプトを指定して変数を受け渡す
            //床を生成するクラスを用意
            //BackImageGenerator backImageGenerator;
            //指定したい変数が入っているオブジェクト名で参照
            // GameObject obj = GameObject.Find("BackImageGenerator");
            //参照したものを用意したものに代入
            // backImageGenerator = obj.GetComponent<BackImageGenerator>();
            //現在出現しているオブジェクトの数を減らす
            //backImageGenerator.GroundNum--;
        }
    }
}
