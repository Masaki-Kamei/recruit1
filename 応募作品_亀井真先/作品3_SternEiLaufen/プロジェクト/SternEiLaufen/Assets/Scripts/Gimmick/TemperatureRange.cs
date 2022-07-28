using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TemperatureRange : MonoBehaviour
{
    ScoreSE scoreSE;

    // Start is called before the first frame update
    void Start()
    {
        scoreSE = GetComponent<ScoreSE>();

    }

    // Update is called once per frame

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            Debug.Log("îMÇ¢ÇÊ");
            collision.gameObject.GetComponent<DefaultPlayer>().AddTemperature();
            scoreSE.StartSE();

            //ìñÇΩÇ¡ÇΩÇÁçÌèú
            Destroy(this.gameObject);


        }

    }

}
