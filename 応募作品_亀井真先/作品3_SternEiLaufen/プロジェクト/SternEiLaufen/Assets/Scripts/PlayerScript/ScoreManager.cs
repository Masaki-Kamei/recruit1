using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class ScoreManager : MonoBehaviour
{
    Gamemanager GameManager;


    [SerializeField]
    GameObject Player;
    public static float Distance=0;
    public static int Score = 0;

    public TextMeshProUGUI CountDistance;
    public TextMeshProUGUI CountScore;
    DefaultPlayer player;
    public static float AddScoreUp;
    // Start is called before the first frame update
    void Start()
    {
        Distance = 0;
        Score = 0;
        GameManager = GameObject.Find("Gamemanager").GetComponent<Gamemanager>();
        player = GameObject.Find("Egg 1").GetComponent<DefaultPlayer>();
    }

    // Update is called once per frame
    void Update()
    {
        AddScoreUp = player.GetAddScore();
        if (GameManager.GetGamePhase() != GameManager.GetSTART()) Distance=Player.transform.position.x- Player.GetComponent<DefaultPlayer>().GetStartPosition();
        if(0< Distance) CountDistance.text = Distance.ToString("f1");
        CountScore.text = Score.ToString();
        /*if (Input.GetKey(KeyCode.S) && Input.GetKey(KeyCode.T) && Input.GetKey(KeyCode.B))
        {
            Score += 100000;
        }*/

    }

    static public void AddScore(int add)
    {
        Score += add;
    }


    public static float GetDistance() { return Distance; }
    public static float GetScore() { return Score; }
    public static float GetAddScoreUp() { return AddScoreUp; }

}
