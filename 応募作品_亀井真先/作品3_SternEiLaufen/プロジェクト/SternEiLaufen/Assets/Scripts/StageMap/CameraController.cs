using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    Gamemanager GameManager;

    //カメラが追いたいプレイヤーを格納
    [SerializeField]
    private GameObject Egg;
    //カメラのX座標の調整
    [SerializeField]
    private float CameraAdjustmentX=0;
    //カメラがプレイヤーと一緒に動くトリガー
    private bool PlayerCamera = false;
    //スクリーン内のプレイヤーの位置
    private Vector3 ScreenPlayerPos;
    //スタート時に固定するするカメラの位置
    private Vector3 StartCameraPos;
    //現在固定するカメラの位置
    private Vector3 FixedCameraPos;
    //移動速度
    private float AddPosX = 0;
    //距離
    private float DownTime = 0;
    // Start is called before the first frame update
    void Start()
    {
        GameManager = GameObject.Find("Gamemanager").GetComponent<Gamemanager>();

    }

    // Update is called once per frame
    void Update()
    {
        if (GameManager.GetGamePhase() != GameManager.GetDEAD())
        {
            if (PlayerCamera == false) StartCamera();
            if (PlayerCamera == true) CameraMove();
        }
    }

    //プレイヤーが特定の位置で待つ処理
    void StartCamera()
    {
        //プレイヤーのオブジェクト名と同じものを取得
        GameObject Player = GameObject.Find(Egg.name);
        //格納したものの位置を取得
        Vector3 PlayerPos = Player.transform.position;
        ScreenPlayerPos = Camera.main.WorldToScreenPoint(PlayerPos);
        if (ScreenPlayerPos.x >= CameraAdjustmentX)
        {
            StartCameraPos = PlayerPos;
            PlayerCamera = true;
            CountStart countstartscript; //呼ぶスクリプトにあだなつける
            countstartscript = GameObject.Find("CountCanvas").GetComponent<CountStart>(); //付いているスクリプトを取得
            countstartscript.OnStartTrigger();
        }
    }
    
    //プレイヤーと一緒に動く処理
    void CameraMove()
    {
        //プレイヤーのオブジェクト名と同じものを取得
        GameObject Player = GameObject.Find(Egg.name);
        //格納したものの位置を取得
        Vector3 PlayerPos = Player.transform.position;
        //カメラの位置をX座標だけ格納した位置に合わせる
        /*transform.position = new Vector3(
            PlayerPos.x- (StartCameraPos.x), transform.position.y, transform.position.z);
        */
       float PosX = transform.position.x;
        if (Egg.GetComponent<DefaultPlayer>().GetIntervalDistance() > (Egg.GetComponent<DefaultPlayer>().GetAccelSpeed()-1)) {
            AddPosX = Egg.GetComponent<DefaultPlayer>().GetIntervalDistance();
        }
        //AddPosX = Egg.GetComponent<DefaultPlayer>().GetIntervalDistance();
        //プレイヤーの画面内の位置座標
        ScreenPlayerPos = Camera.main.WorldToScreenPoint(PlayerPos);
        //画面の位置によって処理
        if ((ScreenPlayerPos.x < CameraAdjustmentX))
        {

            //加速スピードが１以上
            if (Egg.GetComponent<DefaultPlayer>().GetSpeed().x > 1)
            {
                //固定位置に戻る為の時間
                if (DownTime > 10)
                {
                    //カメラを減速させる
                    AddPosX -= 1f;
                }
                else
                {
                    DownTime += Time.deltaTime; ;

                }
            }
        }
        else
        {
            DownTime = 0;
        }

        //カメラ移動
        transform.position = new Vector3(
            PosX + ( AddPosX * Time.deltaTime), transform.position.y, transform.position.z);
        //Debug.Log(Egg.GetComponent<DefaultPlayer>().GetIntervalDistance());
    }
}
