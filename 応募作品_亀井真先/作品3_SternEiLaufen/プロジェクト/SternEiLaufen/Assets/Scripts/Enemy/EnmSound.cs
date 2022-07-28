using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnmSound : MonoBehaviour
{
    // Start is called before the first frame update
    public AudioClip clips;

    AudioSource source;

    private void Start()
    {
        source = GetComponent<AudioSource>();
    }


    public void DeadSE()
    {

        Debug.Log("–Â‚Á‚½");
        //.Stop();
        //source = GetComponents<AudioSource>()[0];
        AudioSource.PlayClipAtPoint(clips, transform.position);
    }

}
