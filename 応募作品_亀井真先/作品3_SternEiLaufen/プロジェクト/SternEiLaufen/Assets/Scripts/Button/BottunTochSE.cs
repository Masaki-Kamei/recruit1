using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BottunTochSE : MonoBehaviour
{
    // Start is called before the first frame update
    public AudioClip clips;

    AudioSource source;


    // Start is called before the first frame update
    void Start()
    {
        source = GetComponent<AudioSource>();

    }

    public void TochLevelSE()
    {
        source.PlayOneShot(clips);
    }

}
