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
        //�Z�[�u�̌^
        public int hp;               //HP
        public int Initialvelocity;  //�����x(�X�s�[�h�j
        public int Fastest;          //�ō����x
    }
    // Start is called before the first frame update
    void Start()
    {        
      player = loadPlayerData();
    }

    public void savePlayerData(Playerdata player)
    {
        //�Z�[�u
        StreamWriter writer;

        string jsonstr = JsonUtility.ToJson(player);

        writer = new StreamWriter(Application.dataPath + "/savedata.json", false);
        writer.Write(jsonstr);
        writer.Flush();
        writer.Close();
    }

    public Playerdata loadPlayerData()
    {
        //���[�h
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
        //�琬��ʂł̕\��
        Text HpText = HpManager.GetComponent<Text>();

        HpText.text = "    " + player.hp;

        Text SpeedText = SpeedManager.GetComponent<Text>();

        SpeedText.text = "    " + player.Initialvelocity;

    }
}
