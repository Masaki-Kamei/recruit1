using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;

public class DefaultPlayer : MonoBehaviour
{
    Gamemanager GameManager;
    //public SpriteRenderer Sp;
    public GameObject Trila;
    public GameObject Soul;
    public GameObject ChangeAnimation;
    public GameObject ReverseAnimationObj;
    public Playerdata player = new Playerdata();
    public SoundPlayer soundPlayer;


    public int time;                    // 全体の時間
    private float timeCount;            // 時間フレーム
    public float speed;                 // 速度
    private float move;                 // 移動
    private float maxSpeed;             // 最大速度
    private float jump;                 // ジャンプ
    public int key;                     // プレイヤー向き
    public int jumpCount;               // ジャンプ条件
    public int jC;                      // ジャンプ回数
    public bool goJump = false;        // ジャンプしているか
    public int playerId;                // プレイヤーID
    private Rigidbody2D dp;             // 自身 デフォルトプレイヤー
    [System.NonSerialized]
    public int CurrentHp;             //現在のHP
    [System.NonSerialized]
    public float CurrentTemperature;    //現在の温度
    private Vector3 OldPos;             //一フレーム前の座標
    Renderer rend;
    private float IntervalDistance;     //一フレームの移動距離
    //高さ割合
    [Header("踏みつけ判定の高さの割合")]
    public float stepOnRate;
    //当たり判定の初期化
    private CapsuleCollider2D capcol = null;
    private bool StopMove = false;
    private float ElapsedTime = 0;
    private Vector2 GroundDist=new Vector2(0,0);
    //アニメーション----------------------------------------
    private PlayerAnimationControl playerAnimationContorol;
    //ステータス--------------------------------------------
    public int MaxHp=0;
    private float AddDistance = 0;
    private float AddScore = 0;
    private int MaxHpLevel = 0;
    private int ScoreAddLevel = 0;
    private int MaxDistanceLevel = 0;
    public float MaxTemperature = 0;
    public float StartSpeed = 0;

    //速度------------------------------------------------
    //現在の速度
    private Vector2 Speed = new Vector2(0,0);
    public float StartAccelSpeed = 0;
    //現在の加速度
    public float AccelSpeed = 0;
    //最大加速度
    public float MaxAccelSpeed = 0;
    private float totalFallTime = 0f;
    //ジャンプ----------------------------------------------
    public bool AirTrigger = true;
    private float JumpPos = 0.0f;
    private float Hight = 0;
    public float NormalJumpPower = 0;     // 初期ジャンプ力
    public float jumpPower=0;             // ジャンプ力
    public float jumpMaxPower=0;             // 最大ジャンプ力
    private float jumpKeyTime = 0;
    private float jumpMaxKeyTime = 0.5f;
    private float Gravity = 0;              //重力
    private int BardJumpSwitch = 0;
    //現在の何してるかのトリガー
    private bool DamageTrigger = false;
    private bool InvincibleTrigger = false;
    private bool GimmickTrigger = false;
    private float StartPosition = 0;


    public class Playerdata
    {
        //セーブの型
        public int EXP;               //経験値
        //レベル
        public int ScoreAdd;  //スコアの増加量
        public int MaxDistance;          //最高速度
        public int MaxHp;          //最大体力
    }
    public Playerdata LoadPlayerLevelData()
    {
        //ロード
        string datastr = "";
        StreamReader reader;
        reader = new StreamReader(Application.dataPath + "/Level.json");
        datastr = reader.ReadToEnd();
        reader.Close();

        return JsonUtility.FromJson<Playerdata>(datastr);
    }

    void Start()
    {
        player=LoadPlayerLevelData();
        MaxHpLevel = player.MaxHp;
        MaxDistanceLevel = player.MaxDistance;
        ScoreAddLevel = player.ScoreAdd;
        MaxHp = MaxHpLevel;
        AddDistance =MaxDistanceLevel*0.5f;
        AddScore = 1 + (ScoreAddLevel * 0.1f);


        GameManager = GameObject.Find("Gamemanager").GetComponent<Gamemanager>();
        playerAnimationContorol = GetComponent<PlayerAnimationControl>();
        soundPlayer = GetComponent<SoundPlayer>();
        dp = GetComponent<Rigidbody2D>();
        key = 1;                    // Player向き
        playerId = 0;               // PlayerId
        //dp.gravityScale = 1.0f;     // 重力
        CurrentHp = MaxHp;          //HP設定
        CurrentTemperature =0;     //温度
        jumpPower=NormalJumpPower;//ジャンプ
        rend = GetComponent<Renderer>();
        OldPos = transform.position;
        AirTrigger = true;
        Speed.x = StartSpeed;
        Speed.y = Physics2D.gravity.y;
        AccelSpeed=StartAccelSpeed;
        //当たり判定の取得
        capcol = GetComponent<CapsuleCollider2D>();
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log("テスト"+ MaxHp);
        Debug.Log("テスト" + AddDistance);
        Debug.Log("テスト" + AddScore);

        if (GameManager.GetGamePhase()!= GameManager.GetDEAD())
        {
            if (GameManager.GetGamePhase() == GameManager.GetSTART()) SetStartPosition();
            if (playerId != 2) Gravity = Physics2D.gravity.y;
            if (!AirTrigger)
            {
                ResetJumpPower();
            }
            if((GroundDist.y+0.1f)< (transform.position.y - (capcol.size.y / 2f)))
            {
                AirTrigger = true;
                GroundDist = new Vector2(0, -100);
            }else if((GroundDist.y -0.7) > (transform.position.y - (capcol.size.y / 2f)))
            {
                AirTrigger = true;
                GroundDist = new Vector2(0, -100);

            }
            if (InvincibleTrigger)
            {
                float level = Mathf.Abs(Mathf.Sin(Time.time * 10));
                gameObject.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, level);
            }
            if (CurrentHp<=0)
            {
                Dead();
                gameObject.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 1f);
            }
            // 時間
            timeCount++;
            if (timeCount >= 60)
            {
                timeCount = 0;
                time++;
                //CurrentHp -= 1;
            }
            if (time >= maxSpeed * 2)
            {
                key = 1;
            }
            ElapsedTime+= Time.deltaTime;
            //kkkkkkkkkkkkkkkkk
            switch (playerId)
            {
                case 0:     // 殻付き卵 
                    break;
                case 1:     // 目玉焼き
                    if (Input.GetKey(KeyCode.Space))
                    {

                        if (Speed.y < 0&& !goJump)
                        {
                            ResetJumpPower();
                            jump = jumpPower;
                            Debug.Log("滑空");
                            Gravity = Gravity - (Gravity / 3);
                            totalFallTime = 1;
                            playerAnimationContorol.FlyAnimation(true);

                        }
                    }
                    else
                    {
                        playerAnimationContorol.FlyAnimation(false);

                    }
                    break;
                case 2:     // ゆで卵
                    if (Input.GetKeyDown(KeyCode.Space) && AirTrigger == true && jumpCount == 1)
                    {
                        totalFallTime += 1;
                        Gravity = Gravity * 3;
                        Debug.Log("落下");
                        jumpCount = 0;
                    }
                    else if (goJump == true||AirTrigger==false)
                    {
                            //ジャンプ力取得
                            if (!GimmickTrigger) jump = jumpPower * 2;
                            else jump = jumpPower;
                            jumpCount = 1;
                            Gravity = Physics2D.gravity.y;
                            goJump = false;

                        //playerAnimationContorol.JumpAnimation(true);

                    }

                    break;
                case 3:     // 鳥さん

                    switch (BardJumpSwitch)
                    {
                        case 0:
                            if (Input.GetKeyUp(KeyCode.Space))
                            {
                                jC = 1;
                                jumpKeyTime = 0;
                                BardJumpSwitch++;
                                Debug.Log("離した");
                            }
                            break;
                        case 1:
                            if (Input.GetKeyDown(KeyCode.Space))
                            {
                                AirTrigger = false;
                                totalFallTime = 0;
                                goJump = true;
                                Debug.Log("2段");
                                BardJumpSwitch++;
                                playerAnimationContorol.DoubleJumpAnimation();
                                soundPlayer.JumpSE();

                            }
                            break;
                        case 2:
                            AirTrigger = true;
                            if (Input.GetKey(KeyCode.Space))
                            {

                                if (Speed.y < 0 && !goJump)
                                {

                                    ResetJumpPower();
                                    jump = jumpPower;
                                    Debug.Log("滑空");
                                    Gravity = Gravity - (Gravity / 3);
                                    totalFallTime = 1;
                                    playerAnimationContorol.FlyAnimation(true);

                                }
                            }
                            else
                            {
                                playerAnimationContorol.FlyAnimation(false);

                            }
                            break;
                    }
                    break;

            }
            // ジャンプ
            if (playerId != 2)//kkkkkkkkkkkkk
            {
                if (goJump)
                {
                    Jump(jumpPower);
                    Debug.Log(jumpPower);
                }
                if (Input.GetKeyDown(KeyCode.Space) && AirTrigger == false)
                {
                    jumpCount = 0;
                    soundPlayer.JumpSE();

                }
                else if (Input.GetKey(KeyCode.Space) && jumpCount == 0 && jumpKeyTime < jumpMaxKeyTime)
                {
                    //空中にいる時間をリセットする
                    totalFallTime = 0;
                    jumpKeyTime += Time.deltaTime;
                    goJump = true;
                }
                else if (Input.GetKeyUp(KeyCode.Space))
                {
                    jumpCount = 1;
                    jumpKeyTime = 0;

                }
            }
            Debug.Log(jumpCount);
            // 移動
            /* float speedx = Mathf.Abs(dp.velocity.x);
               //key = 1;
             if (speedx < maxSpeed)
             {
                 //dp.AddForce(transform.right * key * speed);
                 dp.velocity = new Vector2(dp.velocity.x+(key * speed), dp.velocity.y);
             }

             if (dp.velocity.x <= -2.0f)
             {
                 key = 0;
             }*/

            // ループ
            /*if (transform.position.x > 10)
            {
                transform.position = new Vector2(-9.5f, -1.5f);
            }
            if (transform.position.x < -10)
            {
                transform.position = new Vector2(9.5f, -1.5f);
            }*/

           /* if(Input.GetKeyDown(KeyCode.L))
            {
                Dead();
            }

            // テストコード
            if (Input.GetKeyDown(KeyCode.T))    // 卵
            {
                EggType();

            }
            if (Input.GetKeyDown(KeyCode.Y))    // 目玉焼き
            {
                playerId = 1;
                Debug.Log("目玉焼き");
                playerAnimationContorol.ChangeFriedEggAnimation(true);
            }
            if (Input.GetKeyDown(KeyCode.U))    // ゆで卵
            {
                playerId = 2;
                Debug.Log("ゆで卵");
                jumpCount = 0;
                playerAnimationContorol.ChangeBoiledEggAnimation(true);

            }
            if (Input.GetKeyDown(KeyCode.I))    // 鳥
            {
                playerId = 3;
                Debug.Log("鳥");
                playerAnimationContorol.ChangeBardAnimation(true);
            }*/



            //状態変化アニメーション
            /*if (Input.GetKeyDown(KeyCode.X) && playerId == 0 && !AirTrigger)
            {
                playerAnimationContorol.ChangeAnimation(true);
                //SetStopMove();
                //CharacterChanged();
            }*/

            //ジャンプアニメーション
            playerAnimationContorol.JumpAnimation(AirTrigger);
            //それぞれのアニメーション
            if (!AirTrigger)
            {
                playerAnimationContorol.FlyAnimation(false);
                playerAnimationContorol.RunAnimation(true);

            }

            JumpGravity();
            Move();
            if ( ElapsedTime>10) {
                ElapsedTime = 0;
            }

            if (Speed.y < 0) GimmickTrigger = false;

            //IntervalDistance=transform.position.x - OldPos.x;
            //一フレームの移動距離を取得(magnitudeちょっと重い)
            IntervalDistance = dp.velocity.x;
            //一フレーム前の座標を取得
            OldPos = transform.position;

        }
        else
        {
            dp.velocity = new Vector2(0, 0);

        }
    }

    // タグでの当たり判定
    private void OnCollisionStay2D(Collision2D collision)
    {
        // ジャンプ回数
        if (collision.gameObject.tag == "Floor")
        {
            Debug.Log("チェック");
            //当たった相手のオブジェクトの情報取得
            ContactPoint2D[] points = collision.contacts;
            //踏みつけ判定になる高さ
            float stepOnHeight = (capcol.size.y * (stepOnRate / 100f));
            //踏みつけ判定のワールド座標
            float judgeUpPos = transform.position.y - (capcol.size.y / 2f);
            float judgeDownPos = transform.position.y + (capcol.size.y / 2f) ;
            //配列全てを参照
            foreach (ContactPoint2D p in collision.contacts)
            {

                //相手のオブジェクトよりプレイヤーの高さが高いときの当たり判定の処理
                if (p.point.y-1 <= judgeUpPos)
                {
                    Debug.Log("着地");
                    jC = 0;
                    AirTrigger = false;
                    totalFallTime = 0.1f;
                    goJump = false;
                    jump = 0;
                    BardJumpSwitch = 0;
                    playerAnimationContorol.OnGroundAnimation();
                    GroundDist = p.point;
                    break;
                }
                //相手のオブジェクトよりプレイヤーの高さが低いときの当たり判定の処理
                else if (p.point.y+2>= judgeDownPos)
                {
                }
                else
                {
                    Debug.Log("壁だああああああ");
                    dp.velocity = new Vector2(0, Speed.y);
                    break;

                }
            }

        }
        if (collision.gameObject.tag == "SeeThroughFloor")
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
                if (p.point.y - 1 <= transform.position.y - (capcol.size.y / 2f))
                {

                    Debug.Log("透ける床");
                    jC = 0;
                    AirTrigger = false;
                    totalFallTime = 0.1f;
                    goJump = false;
                    jump = 0;
                    BardJumpSwitch = 0;
                    playerAnimationContorol.OnGroundAnimation();
                    GroundDist = p.point;

                }
                //相手のオブジェクトよりプレイヤーの高さが低いときの当たり判定の処理
                else
                {
                   collision.collider.isTrigger = true;

                }
            }


        }

        /* if (collision.gameObject.tag == "Wall")
         {
             key = -1;
             dp.AddForce(transform.right * key * speed);
             goJump = true;
             Destroy(collision.gameObject);
             time = 0;
         }*/


    }


    private void OnCollisionEnter2D(Collision2D collision)
    {
        // ジャンプ回数
        if (collision.gameObject.tag == "Floor")
        {
            Debug.Log("チェック");
            //当たった相手のオブジェクトの情報取得
            ContactPoint2D[] points = collision.contacts;
            //踏みつけ判定になる高さ
            float stepOnHeight = (capcol.size.y * (stepOnRate / 100f));
            //踏みつけ判定のワールド座標
            float judgeUpPos = transform.position.y - (capcol.size.y / 2f);
            float judgeDownPos = transform.position.y + (capcol.size.y / 2f);
            //配列全てを参照
            foreach (ContactPoint2D p in collision.contacts)
            {

                //相手のオブジェクトよりプレイヤーの高さが高いときの当たり判定の処理
                //相手のオブジェクトよりプレイヤーの高さが低いときの当たり判定の処理
                if (p.point.y + 2 >= judgeDownPos)
                {
                    totalFallTime = 0;
                    jump = 0;
                    jumpKeyTime = jumpMaxKeyTime;
                    Speed.x = 0;
                    Debug.Log("天井");
                    break;
                }
            }

        }
    }

 /*   private void OnTriggerEnter2D(Collider2D collision)
    {


        if (collision.gameObject.tag == "Floor")
        {
            Debug.Log("壁の判定");
            transform.position = new Vector2(transform.position.x-0.3f, transform.position.y);
            dp.velocity = new Vector2(0, Speed.y);

        }

    }*/
        /*private void OnCollisionExit2D(Collision2D collision)
        {

            if (collision.gameObject.tag == "Floor")
            {
                 AirTrigger = true;
                 Debug.Log("確認");
            }
            if (collision.gameObject.tag == "SeeThroughFloor")
            {
                 collision.collider.isTrigger = false;
                 AirTrigger = true;
            }
        }*/


        //踏みつけ処理
        public void SteponEnmObj()
    {
        if (Input.GetKey(KeyCode.Space))
        {
            jumpCount = 0;

        }
        jC = 0;

        AirTrigger = true;
        totalFallTime = 0;
        goJump = true;
        BardJumpSwitch=1;

    }

    //頭突き処理
    public void StepdownEnmObj()
    {
        AirTrigger = true;
        goJump = false;
        jump = (jump*-1);
        jumpKeyTime = jumpMaxKeyTime;
    }


    //ダメージ処理
    public void Damage()
    {
        transform.position = new Vector2(transform.position.x-1f, transform.position.y);
        soundPlayer.DamageSE();
        CurrentHp --;
        StartCoroutine(Invincible());
    }


    public IEnumerator Invincible()
    {
        InvincibleTrigger = true;
        yield return new WaitForSeconds(AddDistance);
        //通常状態に戻る
        InvincibleTrigger = false;
        gameObject.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 1f);
    }

    //ジャンプ処理
    public void Jump(float fPower)
    {
        //dp.AddForce(new Vector2(0,fPower), ForceMode2D.Impulse);
        //dp.AddForce(transform.up * fPower);
        //transform.position += new Vector3(0, fPower, 0);
        //ジャンプ力取得
        jump = fPower;
        //ジャンプトリガーを負にする
        goJump = false;

    }


    //温度上昇
    public void AddTemperature()
    {
        if(MaxTemperature>CurrentTemperature)CurrentTemperature++;

    }
    public void DownTemperature()
    {
        if (0< CurrentTemperature) CurrentTemperature--;

    }

    //ゲームオーバー
    public void GameOver()
    {
        //SceneManager.LoadScene("result");
    }

    public void Dead()
    {
        //SceneManager.LoadScene("result");
        GameManager.SetDEAD();
        dp.velocity = new Vector2(0, 0);
        playerAnimationContorol.DeadAnimation(true);
        Trila.SetActive(false);
        //GetComponent<Collision2D>().collider.isTrigger = false;

    }
    public void AppSoul()
    {
        Soul.SetActive(true);

    }

    public void Move()
    {
        //if(!AirTrigger)
        if(!GimmickTrigger)Speed.x = StartSpeed * AccelSpeed;

        //横移動
        //transform.position += new Vector3(Speed, 0, 0);
        dp.velocity = new Vector2(Speed.x,Speed.y);
    }

    public void AddAccelSpeed(float Add)
    {
        //加速度の数値を増やす
        if(AccelSpeed<MaxAccelSpeed)
        {
            AccelSpeed += Add;
        }
    }

    public void JumpGravity()
    {

        //空中にいる時間を取得
        if (AirTrigger)
        {
            totalFallTime += Time.deltaTime;
        }
        //重力の処理
        //Y軸のベクトル=(ジャンプ力(初速))+(重力+時間)
        Speed.y = jump + (Gravity * totalFallTime);
        
    }

    public void CharacterChanged()
    {
        if(CurrentTemperature >= 0 && CurrentTemperature <= 3)
        {
            playerId = 0;

        }
        else if (CurrentTemperature>=4&& CurrentTemperature<=6)    // ゆで卵
        {
            playerId = 2;
            Debug.Log("ゆで卵");
            jumpCount = 0;
            playerAnimationContorol.ChangeBoiledEggAnimation(true);

        }
        else if (CurrentTemperature >= 7 && CurrentTemperature <= 9)    //目玉焼き
        {
            playerId = 1;
            Debug.Log("目玉焼き");
            playerAnimationContorol.ChangeFriedEggAnimation(true);

        }
        else     // 鳥
        {
            playerId = 3;
            Debug.Log("鳥");
            playerAnimationContorol.ChangeBardAnimation(true);
        }
        playerAnimationContorol.ChangeAnimation(false);

    }

    //殻状態に戻る
    public void EggType()
    {
        if (playerId != 0)
        {

            playerId = 0;
            playerAnimationContorol.ChangeFriedEggAnimation(false);
            playerAnimationContorol.ChangeBoiledEggAnimation(false);
            playerAnimationContorol.ChangeBardAnimation(false);
            playerAnimationContorol.RunAnimation(false);
            ReverseAnimationObj.SetActive(true);
            playerAnimationContorol.ReverseAnimation(true);

        }
        else if (playerId == 0)
        {
        }
        Debug.Log("テスト");
    }
    public void EggReverseAnimation()
    {
        playerAnimationContorol.ReverseAnimation(false);

    }
    //状態変化
    public void ChangeType()
    {
        if (CurrentTemperature >= 0 && CurrentTemperature <= 3)
        {
            CharacterChanged();
            ChangeAnimation.SetActive(true);

        }
        else
        {
            playerAnimationContorol.ChangeAnimation(true);
            ChangeAnimation.SetActive(true);

        }
    }

    public void ColorAlfaReset()
    {
        gameObject.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 1f);

    }
    public void ColorAlfaNot()
    {
        gameObject.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 0);

    }
    public void SetStartPosition() {
        StartPosition = transform.position.x;
    }
    


    //リセット-----------------------------------------------------
    public void ResetJumpPower() { jumpPower = NormalJumpPower; }
    public void ResettotalFallTime() { totalFallTime = 0; }
    public void ResetjumpKeyTime() { jumpKeyTime = 0; }
    public void ResetGravity() { Gravity = Physics2D.gravity.y; }
    public void ResetCurrentTemperature() { CurrentTemperature = 0; }
    //セッター-----------------------------------------------------------
    public void SetStopMove() { StopMove = true; }
    public void SetStartMove() { StopMove = false; }
    public void SetJump(float jumpNum) { jump = jumpNum; }
    public void SetSpeed(Vector2 Sp) { Speed = Sp; }
    public void SetGimmickTrigger(bool Gt) { GimmickTrigger = Gt; }

    //ゲッター-----------------------------------------------------------
    public float GetIntervalDistance() { return IntervalDistance; }
    public Vector2 GetSpeed() { return Speed; }
    public float GetMaxAccelSpeed() { return MaxAccelSpeed; } 
    public float GetAccelSpeed() { return AccelSpeed; }
    public bool GetInvincibleTrigger() { return InvincibleTrigger; }
    public int GetPlayerId() { return playerId; }
    public int GetMaxHp() { return MaxHp; }
    public int GetCurrentHp() { return CurrentHp; }
    public float GetStartPosition() { return StartPosition; }
    public float GetAddScore() { return AddScore; }
    public float GetAddDistance() { return AddDistance; }
    public float GetCurrentTemperature() { return CurrentTemperature; }
}
