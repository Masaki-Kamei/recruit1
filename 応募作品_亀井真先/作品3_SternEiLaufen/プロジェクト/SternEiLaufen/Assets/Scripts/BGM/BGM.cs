using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGM : MonoBehaviour
{
    public static BGM instance;
    public int count;   //Ç±ÇÃïœêîÇàµÇ§
    AudioSource source;

    void Awake()
    {
        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            Destroy(instance.gameObject);
            instance = this;
            DontDestroyOnLoad(this.gameObject);
        }
    }

    public void ClickStart()
    {
        Destroy(this.gameObject);
        Debug.Log("foihssiohgo");
    }

}
