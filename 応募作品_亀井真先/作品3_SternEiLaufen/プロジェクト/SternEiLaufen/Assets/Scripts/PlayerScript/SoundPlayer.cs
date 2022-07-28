using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundPlayer : MonoBehaviour
{
    public AudioClip clips;
    public AudioClip clips2;

    AudioSource source;

    private void Start()
    {
        // アタッチしたオーディオソースのうち1番目を使用する
        source = GetComponent<AudioSource>();
    }


    public void JumpSE()
    {

        //.Stop();
        //source = GetComponents<AudioSource>()[0];
        source.PlayOneShot(clips);
    }

    public void DamageSE()
    {
        source.PlayOneShot(clips2);
    }

}
