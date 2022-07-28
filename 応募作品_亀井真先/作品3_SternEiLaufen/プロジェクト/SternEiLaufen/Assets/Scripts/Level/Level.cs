using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;

public class Level : MonoBehaviour
{
    public  GameObject PlayerLevelUp;
    public static Playerdata player = new Playerdata();


    [System.Serializable]
    public class Playerdata
    {
        //セーブの型
        public int EXP;               //経験値
        //レベル
        public int ScoreAdd;  //スコアの増加量
        public int MaxDistance;          //最高速度
        public int MaxHp;          //最大体力
    }
    // Start is called before the first frame update
    void Start()
    {
        player = loadPlayerData();
        PlayerLevelUp.GetComponent<PlayerLevelUp>().SetEXP(player.EXP);
        PlayerLevelUp.GetComponent<PlayerLevelUp>().SetScoreAdd(player.ScoreAdd);
        PlayerLevelUp.GetComponent<PlayerLevelUp>().SetMaxDistance(player.MaxDistance);
        PlayerLevelUp.GetComponent<PlayerLevelUp>().SetMaxHp(player.MaxHp);

    }

    public  void savePlayerData()
    {
        //セーブ
        StreamWriter writer;

        player.EXP = PlayerLevelUp.GetComponent<PlayerLevelUp>().GetEXP();
        player.ScoreAdd = PlayerLevelUp.GetComponent<PlayerLevelUp>().GetScoreAdd();
        player.MaxDistance = PlayerLevelUp.GetComponent<PlayerLevelUp>().GetMaxDistance();
        player.MaxHp = PlayerLevelUp.GetComponent<PlayerLevelUp>().GetMaxHp();


        string jsonstr = JsonUtility.ToJson(player);

        writer = new StreamWriter(Application.dataPath + "/Level.json", false);
        writer.Write(jsonstr);
        writer.Flush();
        writer.Close();
    }

    public static Playerdata loadPlayerData()
    {
        //ロード
        string datastr = "";
        StreamReader reader;
        reader = new StreamReader(Application.dataPath + "/Level.json");
        datastr = reader.ReadToEnd();
        reader.Close();

        return JsonUtility.FromJson<Playerdata>(datastr);
    }
    // Update is called once per frame

    void Update()
    {


    }

    public void OnClick()
    {
        savePlayerData();
    }

    public static void SetExpUp(int exp)
    {
        StreamWriter writer;

        player = loadPlayerData();
        player.EXP += exp;
        if (player.EXP >= 999999999) { player.EXP = 999999999; }
        string jsonstr = JsonUtility.ToJson(player);

        writer = new StreamWriter(Application.dataPath + "/Level.json", false);
        writer.Write(jsonstr);
        writer.Flush();
        writer.Close();
    }

    public static int GetScoreAdd()
    {
        player = loadPlayerData();
        return player.ScoreAdd;
    }
    public static int GetMaxDistance()
    {
        player = loadPlayerData();
        return player.MaxDistance;
    }
    public static int GetMaxHp()
    {
        player = loadPlayerData();
        return player.MaxHp;
    }

}
