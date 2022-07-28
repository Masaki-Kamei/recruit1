using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class Highscore : MonoBehaviour
{
    public Scoredata scoredata = new Scoredata();

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
    // Update is called once per frame
    void Update()
    {
     
    }
}
