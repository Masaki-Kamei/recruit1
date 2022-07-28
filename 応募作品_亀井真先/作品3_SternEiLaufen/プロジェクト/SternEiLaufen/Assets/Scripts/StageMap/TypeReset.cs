using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TypeReset : MonoBehaviour
{
    DefaultPlayer player;
    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Egg 1").GetComponent<DefaultPlayer>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {

        if (collision.gameObject.tag == "Player")
        {
            Debug.Log("èÛë‘ÇñﬂÇµÇ‹Ç∑");
            collision.gameObject.GetComponent<DefaultPlayer>().EggType();
            player.ResetCurrentTemperature();
            player.AddAccelSpeed(0.5f);


        }


    }

}
