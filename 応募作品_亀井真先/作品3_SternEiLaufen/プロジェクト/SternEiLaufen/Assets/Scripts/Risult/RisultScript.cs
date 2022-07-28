using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class RisultScript : MonoBehaviour
{
    public static float Distance = 0;
    public static int Score = 0;
    private float SaveScore = 0;
    public static int ScorePoint = 0;
    public TextMeshProUGUI CountScore;

    // Start is called before the first frame update
    void Start()
    {
        ScorePoint = (int)(ScoreManager.GetScore() / 10);
        Debug.Log(ScoreManager.GetDistance());
        Score = ScorePoint + (int)ScoreManager.GetDistance();
        SaveScore = Score * ScoreManager.GetAddScoreUp();
        Score = (int)SaveScore;
    }

    // Update is called once per frame
    void Update()
    {
        CountScore.text = Score.ToString();

    }

    public static int GetScoreRisult() { return Score; }
    public static int GetScorePoint() { return ScorePoint; }

}
