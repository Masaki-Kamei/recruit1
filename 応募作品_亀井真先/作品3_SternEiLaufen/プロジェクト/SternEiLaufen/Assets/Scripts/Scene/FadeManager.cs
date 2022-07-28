using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeManager : MonoBehaviour
{
    public static bool isFadeInstance = false;

    public bool isFadeIn = false;//�t�F�[�h�C������t���O
    public bool isFadeOut = false;//�t�F�[�h�A�E�g����t���O

    public float alpha = 0.0f;//���ߗ��A�����ω�������
    public float fadeSpeed = 0.2f;//�t�F�[�h�Ɋ|���鎞��

    private Vector3 Scale;
    void Start()
    {
        Scale = this.transform.localScale;
        if (!isFadeInstance)//�N����
        {
            DontDestroyOnLoad(this);
            isFadeInstance = true;
        }
        else//�N�����ȊO�͏d�����Ȃ��悤�ɂ���
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
            if (alpha <= 0.0f)//�����ɂȂ�����A�t�F�[�h�C�����I��
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
            if (alpha >= 1.0f)//�^�����ɂȂ�����A�t�F�[�h�A�E�g���I��
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