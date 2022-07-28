using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonLevelSE : MonoBehaviour
{
    public AudioClip clips;
    public AudioClip clips2;

    AudioSource source;


    // Start is called before the first frame update
    void Start()
    {
        source = GetComponent<AudioSource>();

    }

    // Update is called once per frame
    public void ClickLevelSE()
    {
        source.PlayOneShot(clips);
    }

    public void ClickNotLevelSE()
    {
        source.PlayOneShot(clips2); 

    }
}
