using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartPlayer : MonoBehaviour
{
    //オブジェクト
    [SerializeField]
    private GameObject Player;
    [SerializeField]
    private float PosX = 0;
    [SerializeField]
    private float PosY = 0;

    // Start is called before the first frame update
    void Start()
    {
        StartNewPlayer();
    }

    // Update is called once per frame
    void Update()
    {

    }


    //プレイヤーの生成処理
    void StartNewPlayer()
    {
        /*Vector3 PlayerPos = Vector3.zero;
        GameObject NewPlayer;
        //出現位置の格納
        PlayerPos = new Vector3(PosX, PosY, 0f);
        //生成(生成するもの,出現位置,出現角度（Quaternion.identity=回転のワールドマトリックスをそのまま取得）)
        NewPlayer = Instantiate(Player, PlayerPos, Quaternion.identity);
        //複製される名前を元の名前にする
        NewPlayer.name = Player.name;
        //出現を管理(出現ごとに親子関係にし、Hierarchyを整理)
        NewPlayer.transform.SetParent(transform);
        */
        Player.SetActive(true);
        Player.transform.position = new Vector2(PosX, PosY);

    }

}
