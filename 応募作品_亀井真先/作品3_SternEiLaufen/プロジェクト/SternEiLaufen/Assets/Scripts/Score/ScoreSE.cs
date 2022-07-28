using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreSE : MonoBehaviour
{
    // Start is called before the first frame update
    public AudioClip clips;

    AudioSource source;

    private void Start()
    {
        source = GetComponent<AudioSource>();
    }


    public void StartSE()
    {

        Debug.Log("–Â‚Á‚½");
        //.Stop();
        //source = GetComponents<AudioSource>()[0];
        AudioSource.PlayClipAtPoint(clips, transform.position);
    }
}
