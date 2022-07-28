using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class RankingDisplay : MonoBehaviour
{
    public GameObject ScoreManager1 = null;
    public GameObject ScoreManager2 = null;
    public GameObject ScoreManager3 = null;
    public Scoredata scoredata = new Scoredata();
    Highscore highscore;
    public int SCORE;
    int save;

    [System.Serializable]
    public class Scoredata
    {
        //セーブの型
        public int score1;
        public int score2;
        public int score3;
    }

    // Start is called before the first frame update
    void Start()
    {
        scoredata = LoadPlayerData();
        //highscore = GameObject.Find("GameObject").GetComponent<Highscore>();
    }

    public Scoredata LoadPlayerData()
    {
        //ロード
        string datastr = "";
        StreamReader reader;
        reader = new StreamReader(Application.dataPath + "/scoredata.json");
        datastr = reader.ReadToEnd();
        reader.Close();

        return JsonUtility.FromJson<Scoredata>(datastr);
    }
    void Update()
    {
        TextMeshProUGUI ScoreText1 = ScoreManager1.GetComponent<TextMeshProUGUI>();

        ScoreText1.text = "    " + scoredata.score1;

        TextMeshProUGUI ScoreText2 = ScoreManager2.GetComponent<TextMeshProUGUI>();

        ScoreText2.text = "    " + scoredata.score2;

        TextMeshProUGUI ScoreText3 = ScoreManager3.GetComponent<TextMeshProUGUI>();

        ScoreText3.text = "    " + scoredata.score3;
    }
}
