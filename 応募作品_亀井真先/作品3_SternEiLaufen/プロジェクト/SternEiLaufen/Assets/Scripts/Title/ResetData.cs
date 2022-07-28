using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class ResetData : MonoBehaviour
{
    public Scoredata scoredata = new Scoredata();
    public  Playerdata player = new Playerdata();

    [System.Serializable]
    public class Scoredata
    {
        //�Z�[�u�̌^
        public int score1;
        public int score2;
        public int score3;
    }
    [System.Serializable]
    public class Playerdata
    {
        //�Z�[�u�̌^
        public int EXP;               //�o���l
        //���x��
        public int ScoreAdd;  //�X�R�A�̑�����
        public int MaxDistance;          //�ō����x
        public int MaxHp;          //�ő�̗�
    }

    void ScoreCalculate()
    {
    }
    public void SavePlayerData(Scoredata score)
    {
        //�Z�[�u
        StreamWriter writer;

        string jsonstr = JsonUtility.ToJson(score);

        writer = new StreamWriter(Application.dataPath + "/scoredata.json", false);
        writer.Write(jsonstr);
        writer.Flush();
        writer.Close();
    }

    public Scoredata LoadPlayerData()
    {
        //���[�h
        string datastr = "";
        StreamReader reader;
        reader = new StreamReader(Application.dataPath + "/scoredata.json");
        datastr = reader.ReadToEnd();
        reader.Close();

        return JsonUtility.FromJson<Scoredata>(datastr);
    }

    public void SavePlayerLavelData(Playerdata playerdata)
    {
        //�Z�[�u
        StreamWriter writer;

        string jsonstr = JsonUtility.ToJson(playerdata);

        writer = new StreamWriter(Application.dataPath + "/Level.json", false);
        writer.Write(jsonstr);
        writer.Flush();
        writer.Close();
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

    void Update()
    {
    }
    public void LoadData()
    {
        scoredata = LoadPlayerData();
        scoredata.score1 = 10000;
        scoredata.score2 = 5000;
        scoredata.score3 = 1000;
        SavePlayerData(scoredata);
        player=LoadPlayerLevelData();
        player.EXP = 0;
        player.ScoreAdd = 1;
        player.MaxDistance = 1;
        player.MaxHp = 1;
        SavePlayerLavelData(player);
    }
}
