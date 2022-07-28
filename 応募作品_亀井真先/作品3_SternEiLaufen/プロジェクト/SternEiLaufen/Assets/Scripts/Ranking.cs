using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class Ranking : MonoBehaviour
{
    public GameObject ScoreManager1 = null;
    public GameObject ScoreManager2 = null;
    public GameObject ScoreManager3 = null;
    public Scoredata scoredata = new Scoredata();
    Highscore highscore;
    public int SCORE;
    int save;
    private int HighScoreIconRank=0;
    public GameObject HighScoreIcon1;
    public GameObject HighScoreIcon2;
    public GameObject HighScoreIcon3;

    int EXPNum = 0;
    [System.Serializable]
    public class Scoredata
    {
        //セーブの型
        public int score1;
        public int score2;
        public int score3;
    }

    void ScoreCalculate()
    {
        if (scoredata.score3 < SCORE)
        {
            scoredata.score3 = SCORE;
            HighScoreIconRank = 3;

            if (scoredata.score2 <= scoredata.score3)
            {
                save = scoredata.score2;

                scoredata.score2 = scoredata.score3;

                scoredata.score3 = save;
                HighScoreIconRank = 2;

                if (scoredata.score1 <= scoredata.score2)
                {
                    save = scoredata.score1;

                   scoredata.score1 =scoredata.score2;

                   scoredata.score2 = save;

                    HighScoreIconRank = 1;

                }

            }
            SavePlayerData(scoredata);
        }
        SetHighScoreIcon();
    }
    // Start is called before the first frame update
    void Start()
    {
        SCORE = RisultScript.GetScoreRisult();

        ExpUp();
        scoredata = LoadPlayerData();
        //highscore = GameObject.Find("GameObject").GetComponent<Highscore>();
        ScoreCalculate();
        scoredata = LoadPlayerData();
        HighScoreIconRank = 0;
    }
    public void SavePlayerData(Scoredata score)
    {
        //セーブ
        StreamWriter writer;

        string jsonstr = JsonUtility.ToJson(score);

        writer = new StreamWriter(Application.dataPath + "/scoredata.json", false);
        writer.Write(jsonstr);
        writer.Flush();
        writer.Close();
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
    void ExpUp()
    {
        EXPNum = RisultScript.GetScorePoint();
        Level.SetExpUp(EXPNum);
    }
    void SetHighScoreIcon()
    {
        if(HighScoreIconRank == 1)HighScoreIcon1.SetActive(true);
        if (HighScoreIconRank == 2) HighScoreIcon2.SetActive(true);
        if (HighScoreIconRank == 3) HighScoreIcon3.SetActive(true);

    }
    public int  GetEXPNum() { return EXPNum; }
}
