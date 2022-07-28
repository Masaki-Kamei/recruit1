using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndDrop : MonoBehaviour
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

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (GameManager.GetGamePhase() == GameManager.GetPLAY())
        {

            if (collision.gameObject.tag == "Player")
            {
                Debug.Log("ゲームオーバー");
                collision.gameObject.GetComponent<DefaultPlayer>().Dead();


            }
        }

    }
}
