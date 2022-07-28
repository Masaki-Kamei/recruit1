using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeManager : MonoBehaviour
{
    public static bool isFadeInstance = false;

    public bool isFadeIn = false;//フェードインするフラグ
    public bool isFadeOut = false;//フェードアウトするフラグ

    public float alpha = 0.0f;//透過率、これを変化させる
    public float fadeSpeed = 0.2f;//フェードに掛かる時間

    private Vector3 Scale;
    void Start()
    {
        Scale = this.transform.localScale;
        if (!isFadeInstance)//起動時
        {
            DontDestroyOnLoad(this);
            isFadeInstance = true;
        }
        else//起動時以外は重複しないようにする
        {
            Destroy(this);
        }
    }

    void Update()
    {
        if (isFadeIn)
        {
            alpha -= Time.deltaTime / fadeSpeed;
            Scale = Scale * alpha;
            if (alpha <= 0.0f)//透明になったら、フェードインを終了
            {
                isFadeIn = false;
                alpha = 0.0f;
                this.GetComponentInChildren<Image>().color = new Color(0.0f, 0.0f, 0.0f, alpha);
            }
            //this.GetComponentInChildren<Image>().color = new Color(0.0f, 0.0f, 0.0f, alpha);
            this.transform.localScale = new Vector3((this.transform.localScale.x+ Scale.x), (this.transform.localScale.y +Scale.y), this.transform.localScale.z);
        }
        else if (isFadeOut)
        {
            alpha += Time.deltaTime / fadeSpeed;
            if (alpha >= 1.0f)//真っ黒になったら、フェードアウトを終了
            {
                isFadeOut = false;
                alpha = 1.0f;
                this.GetComponentInChildren<Image>().color = new Color(0.0f, 0.0f, 0.0f, alpha);
            }
            //this.GetComponentInChildren<Image>().color = new Color(0.0f, 0.0f, 0.0f, alpha);
            this.transform.localScale = new Vector3((this.transform.localScale.x - (Scale.x * alpha)), (this.transform.localScale.y - (Scale.y * alpha)), this.transform.localScale.z);

        }
    }

    public void fadeIn()
    {
        isFadeIn = true;
        isFadeOut = false;
    }

    public void fadeOut()
    {
        isFadeOut = true;
        isFadeIn = false;
    }
}