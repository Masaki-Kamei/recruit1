using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackImageGenerator : MonoBehaviour
{
    //変数
    //オブジェクト
    [SerializeField]
    private GameObject[] GroundPrefab;
    [SerializeField]
    private GameObject[] GroundBonusPrefab;

    //出現数
    [SerializeField]
    private float GroundSpawn = 0;
    //リスト管理
    private List<GameObject> GroundPool = new List<GameObject>();
    //リスト管理
    private List<GameObject> GroundBonusPool = new List<GameObject>();

    //位置調整
    [SerializeField]
    private float GroundAdjustmentPosY = 0.0f;
    //生成する幅
    [SerializeField]
    private float GroundDistanceX = 17.82f;
    //位置調整
    [SerializeField]
    private float GroundBonusAdjustmentPosY = 0.0f;
    //生成する幅
    [SerializeField]
    private float GroundBonusDistanceX = 17.82f;

    //表示する位置
    private float NextGroundPosX;
    //種類ごとに生成する数
    //private int GenerationKindsNum = 3;
    //スタート時のマップ表示数
    private int StartNewGroundNum = 1;

    //生成されている現在の数
    private int GroundNum = 0;
    //生成されているオブジェクト
    GameObject[] GroundNumObjects;

    // Start is called before the first frame update
    void Start()
    {
        GroundGeneration();
        StartNewGround();
    }

    // Update is called once per frame
    void Update()
    {
        NumCheck("Ground");
        GroundSetNum();

    }

    //床の生成処理
    void GroundGeneration()
    {
        for (int i = 0; i < GroundPrefab.Length; i++)
        {
            Vector3 GroudPos = Vector3.zero;
            GameObject NewGround;
            //出現位置の格納
            GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
            //生成(生成するもの,出現位置,出現角度（Quaternion.identity=回転のワールドマトリックスをそのまま取得）)
            NewGround = Instantiate(GroundPrefab[i], GroudPos, Quaternion.identity);
            //出現を管理(出現ごとに親子関係にし、Hierarchyを整理)
            NewGround.transform.SetParent(transform);
            //リストに追加(種類ごとの数)
            GroundPool.Add(NewGround);
            //オブジェクトを非表示
            GroundPool[i].SetActive(false);


        }
        //ボーナスステージ
        for(int i=0;i< GroundBonusPrefab.Length;i++)
        {
            Vector3 GroudPos = Vector3.zero;
            GameObject NewGround;
            //出現位置の格納
            GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
            //生成(生成するもの,出現位置,出現角度（Quaternion.identity=回転のワールドマトリックスをそのまま取得）)
            NewGround = Instantiate(GroundPrefab[i], GroudPos, Quaternion.identity);
            //出現を管理(出現ごとに親子関係にし、Hierarchyを整理)
            NewGround.transform.SetParent(transform);
            //リストに追加(種類ごとの数)
            GroundBonusPool.Add(NewGround);
            //オブジェクトを非表示
            GroundBonusPool[i].SetActive(false);

        }
    }

    void StartNewGround()
    {
        Vector3 GroudPos = Vector3.zero;

        for (int i = 0; i < StartNewGroundNum; i++)
        {
            //種類ごとのマップの表示させる数
            GameObject NewGround;
            GameObject NewGroundBonus;

            if (i == 0)
            {
                //出現位置の格納
                GroudPos = new Vector3(0, GroundAdjustmentPosY, 0f);
                //生成(生成するもの,出現位置,出現角度（Quaternion.identity=回転のワールドマトリックスをそのまま取得）)
                NewGround = Instantiate(GroundPrefab[0], GroudPos, Quaternion.identity);
                //出現を管理(出現ごとに親子関係にし、Hierarchyを整理)
                NewGround.transform.SetParent(transform);
                NextGroundPosX += GroundDistanceX;

                //出現位置の格納
                GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
                //生成(生成するもの,出現位置,出現角度（Quaternion.identity=回転のワールドマトリックスをそのまま取得）)
                NewGroundBonus = Instantiate(GroundBonusPrefab[0], GroudPos, Quaternion.identity);
                //出現を管理(出現ごとに親子関係にし、Hierarchyを整理)
                NewGroundBonus.transform.SetParent(transform);
                NextGroundPosX += GroundBonusDistanceX;

            }
            //出現位置の格納
            //GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
            //生成(生成するもの,出現位置,出現角度（Quaternion.identity=回転のワールドマトリックスをそのまま取得）)
            //NewGround = Instantiate(GroundPrefab[0], GroudPos, Quaternion.identity);
            //出現を管理(出現ごとに親子関係にし、Hierarchyを整理)
            //NewGround.transform.SetParent(transform);
            //次の床の出現位置
            //NextGroundPosX += GroundDistanceX;
            //GroundNum++;

        }

    }

    //出現させる
    void SetNewGround()
    {
        Vector3 GroudPos = Vector3.zero;
        //  ランダムで種類を決める
        int RandomKinds = Random.Range(0, GroundPool.Count);
        //種類ごとのマップの表示させる数
        GameObject NewGround;
        //出現位置の格納
        GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
        //生成(生成するもの,出現位置,出現角度（Quaternion.identity=回転のワールドマトリックスをそのまま取得）)
        NewGround = Instantiate(GroundPrefab[RandomKinds], GroudPos, Quaternion.identity);
        //出現を管理(出現ごとに親子関係にし、Hierarchyを整理)
        NewGround.transform.SetParent(transform);
        //次の床の出現位置
        NextGroundPosX += GroundDistanceX;

        //ボーナスステージ
        Vector3 GroudBonusPos = Vector3.zero;
        RandomKinds = Random.Range(0, GroundBonusPool.Count);
        GameObject NewGroundBounus;
        //出現位置の格納
        GroudBonusPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
        //生成(生成するもの,出現位置,出現角度（Quaternion.identity=回転のワールドマトリックスをそのまま取得）)
        NewGroundBounus = Instantiate(GroundBonusPrefab[RandomKinds], GroudBonusPos, Quaternion.identity);
        //出現を管理(出現ごとに親子関係にし、Hierarchyを整理)
        NewGroundBounus.transform.SetParent(transform);
        //次の床の出現位置
        NextGroundPosX += GroundBonusDistanceX;

        //GroundNum++;

    }


    //現在表示されている数を取得
    void GroundSetNum()
    {


        if (GroundNum < GroundSpawn)
        {
            //マップ表示
            SetNewGround();
            NumCheck("Ground");

        }

    }

    //現在のオブジェクトの生成されている数を取得
    //  string TagName  指定したオブジェクトのタグ名
    void NumCheck(string TagName)
    {
        //生成されているオブジェクトを格納
        GroundNumObjects = GameObject.FindGameObjectsWithTag(TagName);
        //現在のオブジェクトの数
        GroundNum = GroundNumObjects.Length;
    }

}

