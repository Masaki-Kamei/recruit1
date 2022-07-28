using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ButtonOver : MonoBehaviour
{
    public Image image;

    // Start is called before the first frame update
    void Start()
    {
        image.color = new Color((188f / 255f), (188f / 255f), (188f / 255f), 1);

    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void OnMouseOver()
    {
        image.color = new Color(255f, 255f, 255f, 255f);
        Debug.Log("êGÇÍÇΩ");
    }
    public void OnMouseExit()
    {
        image.color = new Color((188f / 255f), (188f / 255f), (188f / 255f), 1);
        Debug.Log("ó£ÇµÇΩ");
    }

}
