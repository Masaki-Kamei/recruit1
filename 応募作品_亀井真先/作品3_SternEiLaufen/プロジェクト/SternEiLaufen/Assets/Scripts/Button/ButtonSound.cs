using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonSound : MonoBehaviour
{

    public static ButtonSound instance;

    // Start is called before the first frame update
    public AudioClip clips;
    public AudioClip clips2;

    AudioSource source;

    void Awake()
    {
        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(this.gameObject);
            source = GetComponent<AudioSource>();
        }
        else
        {
            Destroy(instance.gameObject);
            instance = this;
            DontDestroyOnLoad(this.gameObject);
            source = GetComponent<AudioSource>();

        }

    }



    public void ClickSE()
    {

        Debug.Log("–Â‚Á‚½");
        //.Stop();
        //source = GetComponents<AudioSource>()[0];
        source.PlayOneShot(clips);

    }

    public void TouchSE()
    {
        source.PlayOneShot(clips2);

    }

}
