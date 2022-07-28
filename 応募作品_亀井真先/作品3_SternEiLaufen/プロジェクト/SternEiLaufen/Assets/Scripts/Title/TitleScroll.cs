using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleScroll : MonoBehaviour
{
    public GameObject gameObject1;
    public GameObject gameObject2;

    private bool trigger = false;
    public float AddWidth=0;
    public float AddHight = 0;


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 pos = gameObject1.GetComponent<RectTransform>().anchoredPosition;
        pos.x += AddWidth;
        pos.y += AddHight;
        gameObject1.GetComponent<RectTransform>().anchoredPosition = pos;
        pos = gameObject2.GetComponent<RectTransform>().anchoredPosition;
        pos.x += AddWidth;
        pos.y += AddHight;
        gameObject2.GetComponent<RectTransform>().anchoredPosition = pos;

        if (trigger==false)
        {
            pos = gameObject1.GetComponent<RectTransform>().anchoredPosition;

            if (pos.x<=-600&& pos.y <= -600)
            {
                trigger = true;
                gameObject1.GetComponent<RectTransform>().anchoredPosition = new Vector3(600,600,0);

            }
        }
        else if(trigger == true)
        {
            pos = gameObject2.GetComponent<RectTransform>().anchoredPosition;

            if (pos.x <= -600 && pos.y <= -600)
            {
                trigger = false;
                gameObject2.GetComponent<RectTransform>().anchoredPosition = new Vector3(600, 600, 0);

            }

        }
    }
}
