using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LifeNum : MonoBehaviour
{
    // Start is called before the first frame update

    [SerializeField]
    private GameObject[] Life;
    [SerializeField]
    private GameObject Player;
    private DefaultPlayer defaultPlayer;
    private int MaxLife = 0;
    private int CurrentLife = 0;
    private int OldLife = 0;
    void Start()
    {
        defaultPlayer = Player.GetComponent<DefaultPlayer>();
        for (int i = 0; i < defaultPlayer.GetCurrentHp(); i++)
        {
            Life[i].SetActive(true);
        }


    }

    // Update is called once per frame
    void Update()
    {
        CurrentLife = defaultPlayer.GetCurrentHp();
        if(CurrentLife<OldLife)
        {
            Life[CurrentLife].SetActive(false);
        }
        OldLife = CurrentLife;
    }

    void MaxHp()
    {

    }

}
