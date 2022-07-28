using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class StartClick : MonoBehaviour
{
    bool StartText = false;
    public GameObject Button1;
    public GameObject Button2;
    public Image image;

    public float speed = 0.0f;
    private float time;
    // Start is called before the first frame update
    void Start()
    {
        StartText = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0)&& StartText==false)
        {
            StartText = true;
            Button1.SetActive(true);
            Button2.SetActive(true);
            this.gameObject.SetActive(false);

        }
        image.color=GetAlphaColor(image.color);
    }

    Color GetAlphaColor(Color color)
    {

        time += Time.deltaTime * 0.5f * speed;
        color.a = Mathf.Sin(time);
        return color;
    }
}
