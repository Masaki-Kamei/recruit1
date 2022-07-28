using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;

public class save : MonoBehaviour
{
    public GameObject HpManager = null;
    public GameObject SpeedManager = null;
    public Playerdata player = new Playerdata();

    [System.Serializable]
    public class Playerdata
    {
        //セーブの型
        public int hp;               //HP
        public int Initialvelocity;  //初速度(スピード）
        public int Fastest;          //最高速度
    }
    // Start is called before the first frame update
    void Start()
    {        
      player = loadPlayerData();
    }

    public void savePlayerData(Playerdata player)
    {
        //セーブ
        StreamWriter writer;

        string jsonstr = JsonUtility.ToJson(player);

        writer = new StreamWriter(Application.dataPath + "/savedata.json", false);
        writer.Write(jsonstr);
        writer.Flush();
        writer.Close();
    }

    public Playerdata loadPlayerData()
    {
        //ロード
        string datastr = "";
        StreamReader reader;
        reader = new StreamReader(Application.dataPath + "/savedata.json");
        datastr = reader.ReadToEnd();
        reader.Close();

        return JsonUtility.FromJson<Playerdata>(datastr);
    }
    // Update is called once per frame
 
    void Update()
    {
        //育成画面での表示
        Text HpText = HpManager.GetComponent<Text>();

        HpText.text = "    " + player.hp;

        Text SpeedText = SpeedManager.GetComponent<Text>();

        SpeedText.text = "    " + player.Initialvelocity;

    }
}
