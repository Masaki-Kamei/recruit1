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


    public int time;                    // �S�̂̎���
    private float timeCount;            // ���ԃt���[��
    public float speed;                 // ���x
    private float move;                 // �ړ�
    private float maxSpeed;             // �ő呬�x
    private float jump;                 // �W�����v
    public int key;                     // �v���C���[����
    public int jumpCount;               // �W�����v����
    public int jC;                      // �W�����v��
    public bool goJump = false;        // �W�����v���Ă��邩
    public int playerId;                // �v���C���[ID
    private Rigidbody2D dp;             // ���g �f�t�H���g�v���C���[
    [System.NonSerialized]
    public int CurrentHp;             //���݂�HP
    [System.NonSerialized]
    public float CurrentTemperature;    //���݂̉��x
    private Vector3 OldPos;             //��t���[���O�̍��W
    Renderer rend;
    private float IntervalDistance;     //��t���[���̈ړ�����
    //��������
    [Header("���݂�����̍����̊���")]
    public float stepOnRate;
    //�����蔻��̏�����
    private CapsuleCollider2D capcol = null;
    private bool StopMove = false;
    private float ElapsedTime = 0;
    private Vector2 GroundDist=new Vector2(0,0);
    //�A�j���[�V����----------------------------------------
    private PlayerAnimationControl playerAnimationContorol;
    //�X�e�[�^�X--------------------------------------------
    public int MaxHp=0;
    private float AddDistance = 0;
    private float AddScore = 0;
    private int MaxHpLevel = 0;
    private int ScoreAddLevel = 0;
    private int MaxDistanceLevel = 0;
    public float MaxTemperature = 0;
    public float StartSpeed = 0;

    //���x------------------------------------------------
    //���݂̑��x
    private Vector2 Speed = new Vector2(0,0);
    public float StartAccelSpeed = 0;
    //���݂̉����x
    public float AccelSpeed = 0;
    //�ő�����x
    public float MaxAccelSpeed = 0;
    private float totalFallTime = 0f;
    //�W�����v----------------------------------------------
    public bool AirTrigger = true;
    private float JumpPos = 0.0f;
    private float Hight = 0;
    public float NormalJumpPower = 0;     // �����W�����v��
    public float jumpPower=0;             // �W�����v��
    public float jumpMaxPower=0;             // �ő�W�����v��
    private float jumpKeyTime = 0;
    private float jumpMaxKeyTime = 0.5f;
    private float Gravity = 0;              //�d��
    private int BardJumpSwitch = 0;
    //���݂̉����Ă邩�̃g���K�[
    private bool DamageTrigger = false;
    private bool InvincibleTrigger = false;
    private bool GimmickTrigger = false;
    private float StartPosition = 0;


    public class Playerdata
    {
        //�Z�[�u�̌^
        public int EXP;               //�o���l
        //���x��
        public int ScoreAdd;  //�X�R�A�̑�����
        public int MaxDistance;          //�ō����x
        public int MaxHp;          //�ő�̗�
    }
    public Playerdata LoadPlayerLevelData()
    {
        //���[�h
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
        key = 1;                    // Player����
        playerId = 0;               // PlayerId
        //dp.gravityScale = 1.0f;     // �d��
        CurrentHp = MaxHp;          //HP�ݒ�
        CurrentTemperature =0;     //���x
        jumpPower=NormalJumpPower;//�W�����v
        rend = GetComponent<Renderer>();
        OldPos = transform.position;
        AirTrigger = true;
        Speed.x = StartSpeed;
        Speed.y = Physics2D.gravity.y;
        AccelSpeed=StartAccelSpeed;
        //�����蔻��̎擾
        capcol = GetComponent<CapsuleCollider2D>();
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log("�e�X�g"+ MaxHp);
        Debug.Log("�e�X�g" + AddDistance);
        Debug.Log("�e�X�g" + AddScore);

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
            // ����
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
                case 0:     // �k�t���� 
                    break;
                case 1:     // �ڋʏĂ�
                    if (Input.GetKey(KeyCode.Space))
                    {

                        if (Speed.y < 0&& !goJump)
                        {
                            ResetJumpPower();
                            jump = jumpPower;
                            Debug.Log("����");
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
                case 2:     // ��ŗ�
                    if (Input.GetKeyDown(KeyCode.Space) && AirTrigger == true && jumpCount == 1)
                    {
                        totalFallTime += 1;
                        Gravity = Gravity * 3;
                        Debug.Log("����");
                        jumpCount = 0;
                    }
                    else if (goJump == true||AirTrigger==false)
                    {
                            //�W�����v�͎擾
                            if (!GimmickTrigger) jump = jumpPower * 2;
                            else jump = jumpPower;
                            jumpCount = 1;
                            Gravity = Physics2D.gravity.y;
                            goJump = false;

                        //playerAnimationContorol.JumpAnimation(true);

                    }

                    break;
                case 3:     // ������

                    switch (BardJumpSwitch)
                    {
                        case 0:
                            if (Input.GetKeyUp(KeyCode.Space))
                            {
                                jC = 1;
                                jumpKeyTime = 0;
                                BardJumpSwitch++;
                                Debug.Log("������");
                            }
                            break;
                        case 1:
                            if (Input.GetKeyDown(KeyCode.Space))
                            {
                                AirTrigger = false;
                                totalFallTime = 0;
                                goJump = true;
                                Debug.Log("2�i");
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
                                    Debug.Log("����");
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
            // �W�����v
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
                    //�󒆂ɂ��鎞�Ԃ����Z�b�g����
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
            // �ړ�
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

            // ���[�v
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

            // �e�X�g�R�[�h
            if (Input.GetKeyDown(KeyCode.T))    // ��
            {
                EggType();

            }
            if (Input.GetKeyDown(KeyCode.Y))    // �ڋʏĂ�
            {
                playerId = 1;
                Debug.Log("�ڋʏĂ�");
                playerAnimationContorol.ChangeFriedEggAnimation(true);
            }
            if (Input.GetKeyDown(KeyCode.U))    // ��ŗ�
            {
                playerId = 2;
                Debug.Log("��ŗ�");
                jumpCount = 0;
                playerAnimationContorol.ChangeBoiledEggAnimation(true);

            }
            if (Input.GetKeyDown(KeyCode.I))    // ��
            {
                playerId = 3;
                Debug.Log("��");
                playerAnimationContorol.ChangeBardAnimation(true);
            }*/



            //��ԕω��A�j���[�V����
            /*if (Input.GetKeyDown(KeyCode.X) && playerId == 0 && !AirTrigger)
            {
                playerAnimationContorol.ChangeAnimation(true);
                //SetStopMove();
                //CharacterChanged();
            }*/

            //�W�����v�A�j���[�V����
            playerAnimationContorol.JumpAnimation(AirTrigger);
            //���ꂼ��̃A�j���[�V����
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
            //��t���[���̈ړ��������擾(magnitude������Əd��)
            IntervalDistance = dp.velocity.x;
            //��t���[���O�̍��W���擾
            OldPos = transform.position;

        }
        else
        {
            dp.velocity = new Vector2(0, 0);

        }
    }

    // �^�O�ł̓����蔻��
    private void OnCollisionStay2D(Collision2D collision)
    {
        // �W�����v��
        if (collision.gameObject.tag == "Floor")
        {
            Debug.Log("�`�F�b�N");
            //������������̃I�u�W�F�N�g�̏��擾
            ContactPoint2D[] points = collision.contacts;
            //���݂�����ɂȂ鍂��
            float stepOnHeight = (capcol.size.y * (stepOnRate / 100f));
            //���݂�����̃��[���h���W
            float judgeUpPos = transform.position.y - (capcol.size.y / 2f);
            float judgeDownPos = transform.position.y + (capcol.size.y / 2f) ;
            //�z��S�Ă��Q��
            foreach (ContactPoint2D p in collision.contacts)
            {

                //����̃I�u�W�F�N�g���v���C���[�̍����������Ƃ��̓����蔻��̏���
                if (p.point.y-1 <= judgeUpPos)
                {
                    Debug.Log("���n");
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
                //����̃I�u�W�F�N�g���v���C���[�̍������Ⴂ�Ƃ��̓����蔻��̏���
                else if (p.point.y+2>= judgeDownPos)
                {
                }
                else
                {
                    Debug.Log("�ǂ�������������");
                    dp.velocity = new Vector2(0, Speed.y);
                    break;

                }
            }

        }
        if (collision.gameObject.tag == "SeeThroughFloor")
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
                if (p.point.y - 1 <= transform.position.y - (capcol.size.y / 2f))
                {

                    Debug.Log("�����鏰");
                    jC = 0;
                    AirTrigger = false;
                    totalFallTime = 0.1f;
                    goJump = false;
                    jump = 0;
                    BardJumpSwitch = 0;
                    playerAnimationContorol.OnGroundAnimation();
                    GroundDist = p.point;

                }
                //����̃I�u�W�F�N�g���v���C���[�̍������Ⴂ�Ƃ��̓����蔻��̏���
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
        // �W�����v��
        if (collision.gameObject.tag == "Floor")
        {
            Debug.Log("�`�F�b�N");
            //������������̃I�u�W�F�N�g�̏��擾
            ContactPoint2D[] points = collision.contacts;
            //���݂�����ɂȂ鍂��
            float stepOnHeight = (capcol.size.y * (stepOnRate / 100f));
            //���݂�����̃��[���h���W
            float judgeUpPos = transform.position.y - (capcol.size.y / 2f);
            float judgeDownPos = transform.position.y + (capcol.size.y / 2f);
            //�z��S�Ă��Q��
            foreach (ContactPoint2D p in collision.contacts)
            {

                //����̃I�u�W�F�N�g���v���C���[�̍����������Ƃ��̓����蔻��̏���
                //����̃I�u�W�F�N�g���v���C���[�̍������Ⴂ�Ƃ��̓����蔻��̏���
                if (p.point.y + 2 >= judgeDownPos)
                {
                    totalFallTime = 0;
                    jump = 0;
                    jumpKeyTime = jumpMaxKeyTime;
                    Speed.x = 0;
                    Debug.Log("�V��");
                    break;
                }
            }

        }
    }

 /*   private void OnTriggerEnter2D(Collider2D collision)
    {


        if (collision.gameObject.tag == "Floor")
        {
            Debug.Log("�ǂ̔���");
            transform.position = new Vector2(transform.position.x-0.3f, transform.position.y);
            dp.velocity = new Vector2(0, Speed.y);

        }

    }*/
        /*private void OnCollisionExit2D(Collision2D collision)
        {

            if (collision.gameObject.tag == "Floor")
            {
                 AirTrigger = true;
                 Debug.Log("�m�F");
            }
            if (collision.gameObject.tag == "SeeThroughFloor")
            {
                 collision.collider.isTrigger = false;
                 AirTrigger = true;
            }
        }*/


        //���݂�����
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

    //���˂�����
    public void StepdownEnmObj()
    {
        AirTrigger = true;
        goJump = false;
        jump = (jump*-1);
        jumpKeyTime = jumpMaxKeyTime;
    }


    //�_���[�W����
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
        //�ʏ��Ԃɖ߂�
        InvincibleTrigger = false;
        gameObject.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 1f);
    }

    //�W�����v����
    public void Jump(float fPower)
    {
        //dp.AddForce(new Vector2(0,fPower), ForceMode2D.Impulse);
        //dp.AddForce(transform.up * fPower);
        //transform.position += new Vector3(0, fPower, 0);
        //�W�����v�͎擾
        jump = fPower;
        //�W�����v�g���K�[�𕉂ɂ���
        goJump = false;

    }


    //���x�㏸
    public void AddTemperature()
    {
        if(MaxTemperature>CurrentTemperature)CurrentTemperature++;

    }
    public void DownTemperature()
    {
        if (0< CurrentTemperature) CurrentTemperature--;

    }

    //�Q�[���I�[�o�[
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

        //���ړ�
        //transform.position += new Vector3(Speed, 0, 0);
        dp.velocity = new Vector2(Speed.x,Speed.y);
    }

    public void AddAccelSpeed(float Add)
    {
        //�����x�̐��l�𑝂₷
        if(AccelSpeed<MaxAccelSpeed)
        {
            AccelSpeed += Add;
        }
    }

    public void JumpGravity()
    {

        //�󒆂ɂ��鎞�Ԃ��擾
        if (AirTrigger)
        {
            totalFallTime += Time.deltaTime;
        }
        //�d�͂̏���
        //Y���̃x�N�g��=(�W�����v��(����))+(�d��+����)
        Speed.y = jump + (Gravity * totalFallTime);
        
    }

    public void CharacterChanged()
    {
        if(CurrentTemperature >= 0 && CurrentTemperature <= 3)
        {
            playerId = 0;

        }
        else if (CurrentTemperature>=4&& CurrentTemperature<=6)    // ��ŗ�
        {
            playerId = 2;
            Debug.Log("��ŗ�");
            jumpCount = 0;
            playerAnimationContorol.ChangeBoiledEggAnimation(true);

        }
        else if (CurrentTemperature >= 7 && CurrentTemperature <= 9)    //�ڋʏĂ�
        {
            playerId = 1;
            Debug.Log("�ڋʏĂ�");
            playerAnimationContorol.ChangeFriedEggAnimation(true);

        }
        else     // ��
        {
            playerId = 3;
            Debug.Log("��");
            playerAnimationContorol.ChangeBardAnimation(true);
        }
        playerAnimationContorol.ChangeAnimation(false);

    }

    //�k��Ԃɖ߂�
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
        Debug.Log("�e�X�g");
    }
    public void EggReverseAnimation()
    {
        playerAnimationContorol.ReverseAnimation(false);

    }
    //��ԕω�
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
    


    //���Z�b�g-----------------------------------------------------
    public void ResetJumpPower() { jumpPower = NormalJumpPower; }
    public void ResettotalFallTime() { totalFallTime = 0; }
    public void ResetjumpKeyTime() { jumpKeyTime = 0; }
    public void ResetGravity() { Gravity = Physics2D.gravity.y; }
    public void ResetCurrentTemperature() { CurrentTemperature = 0; }
    //�Z�b�^�[-----------------------------------------------------------
    public void SetStopMove() { StopMove = true; }
    public void SetStartMove() { StopMove = false; }
    public void SetJump(float jumpNum) { jump = jumpNum; }
    public void SetSpeed(Vector2 Sp) { Speed = Sp; }
    public void SetGimmickTrigger(bool Gt) { GimmickTrigger = Gt; }

    //�Q�b�^�[-----------------------------------------------------------
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
