using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
public class CountStart : MonoBehaviour
{
    Gamemanager GameManager;

    // Start is called before the first frame update
    public TextMeshProUGUI CountText;
    private float CountTime = 3;
    int Count;
    private bool CountStartTrigger = false;
    // Start is called before the first frame update
    void Start()
    {
        GameManager = GameObject.Find("Gamemanager").GetComponent<Gamemanager>();


        CountText.enabled = false;
        CountTime += 0.99f;
    }

    // Update is called once per frame
    void Update()
    {
        if (CountStartTrigger)
        {
            if (CountTime >= 0)
            {
                CountTime -= Time.deltaTime;
                Count = (int)CountTime;
                if (CountTime >= 1)
                {
                    CountText.text = Count.ToString();
                }
                else if (CountTime < 1 && CountTime >= 0)
                {
                    CountText.text = "START";
                    GameManager.SetPLAY();
                }
                else
                {
                    CountText.enabled = false;
                }

            }
        }
    }

    public void OnStartTrigger()
    {
        CountStartTrigger = true;
        CountText.enabled = true;
    }
}
