using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SelectSprite : MonoBehaviour
{
    public Sprite SR;
    public Image image;

    // Start is called before the first frame update
    void Start()
    {
        image.color = new Color(0, 0, 0, 0);

    }

    // Update is called once per frame
    void Update()
    {
    }

    public void OnMouseOver()
    {
        image.color = new Color(1, 1, 1, 1);
        image.sprite = SR;

    }
    public void OnMouseExit()
    {
        image.color= new Color(0,0,0,0);
        Debug.Log("—£‚µ‚½");
    }
}
