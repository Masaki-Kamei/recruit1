using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DownTemperatureRange : MonoBehaviour
{
    ScoreSE scoreSE;

    // Start is called before the first frame update
    void Start()
    {
        scoreSE = GetComponent<ScoreSE>();

    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            Debug.Log("寒いよ");
            collision.gameObject.GetComponent<DefaultPlayer>().DownTemperature();
            scoreSE.StartSE();

            //当たったら削除
            Destroy(this.gameObject);


        }

    }

}
