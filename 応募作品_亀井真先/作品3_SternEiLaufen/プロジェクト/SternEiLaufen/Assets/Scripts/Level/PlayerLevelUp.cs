using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class PlayerLevelUp : MonoBehaviour
{
    private int EXPLevel=0;
    //レベル
    private int ScoreAddLevel=0;  //スコアの増加量
    private int MaxDistanceLevel=0;          //最高速度
    private int MaxHpLevel=0;          //最大体力

    public GameObject EXPText = null;
    public GameObject ScoreAddText = null;
    public GameObject MaxDistanceText = null;
    public GameObject MaxHpText = null;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        TextMeshProUGUI EXPTextNum = EXPText.GetComponent<TextMeshProUGUI>();

        EXPTextNum.text = "" + EXPLevel;

        TextMeshProUGUI ScoreAddTextNum = ScoreAddText.GetComponent<TextMeshProUGUI>();

        ScoreAddTextNum.text = "" + ScoreAddLevel;

        TextMeshProUGUI MaxDistanceTextNum = MaxDistanceText.GetComponent<TextMeshProUGUI>();

        MaxDistanceTextNum.text = "" + MaxDistanceLevel;

        TextMeshProUGUI MaxHpTextNum = MaxHpText.GetComponent<TextMeshProUGUI>();

        MaxHpTextNum.text = "" + MaxHpLevel;


    }

    public void SetEXP(int exp) { EXPLevel = exp; }
    public void SetScoreAdd(int scoreadd) { ScoreAddLevel = scoreadd; }
    public void SetMaxDistance(int maxdistancel) { MaxDistanceLevel = maxdistancel; }
    public void SetMaxHp(int maxhp) { MaxHpLevel = maxhp; }

    public int GetEXP() { return EXPLevel; }
    public int GetScoreAdd() { return ScoreAddLevel; }
    public int GetMaxDistance() { return MaxDistanceLevel; }
    public int GetMaxHp() { return MaxHpLevel; }

}
