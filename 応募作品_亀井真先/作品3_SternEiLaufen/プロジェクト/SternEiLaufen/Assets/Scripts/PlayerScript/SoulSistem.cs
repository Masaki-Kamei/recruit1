using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class SoulSistem : MonoBehaviour
{
    Gamemanager GameManager;

    // Start is called before the first frame update
    void Start()
    {
        GameManager = GameObject.Find("Gamemanager").GetComponent<Gamemanager>();

    }

    // Update is called once per frame
    void Update()
    {
        
    }

    //ゲームオーバー
    public void GameOver()
    {
        SceneManager.LoadScene("result");
    }

}
