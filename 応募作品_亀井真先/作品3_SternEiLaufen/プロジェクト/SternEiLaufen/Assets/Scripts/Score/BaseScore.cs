using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BaseScore : MonoBehaviour
{

    [SerializeField]
    [Tooltip("発生させるエフェクト(パーティクル)")]
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
        // ジャンプ回数
        if (collision.gameObject.tag == "Player")
        {
            if (particle != null)
            {
                // パーティクルシステムのインスタンスを生成する。
                ParticleSystem newParticle = Instantiate(particle);
                // パーティクルの発生場所をこのスクリプトをアタッチしているGameObjectの場所にする。
                newParticle.transform.position = this.transform.position;
                // パーティクルを発生させる。
                newParticle.Play();
                Destroy(newParticle.gameObject, 1.0f);
            }

            scoreSE.StartSE();
            //当たったら削除
            Destroy(this.gameObject);
            ScoreUp();

        }

    }

    void ScoreUp()
    {
        Debug.Log("スコア増加");
        //スコアを増やす
        ScoreManager.AddScore(AddScore);
    }

}
