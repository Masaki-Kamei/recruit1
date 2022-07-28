using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class SwitchScript : MonoBehaviour
{
    // Start is called before the first frame update
    public string sceneName;
    public Image image;

    private void Start()
    {
        image.color = new Color((188f / 255f), (188f / 255f), (188f / 255f), 1);

    }
    public void OnMouseDown()
    {
        //GameObject.Find("Main Camera").GetComponent<SceneController>().sceneChange();
        SceneManager.LoadScene(sceneName);
    }
    public void OnMouseOver()
    {
        image.color =new Color(255f, 255f, 255f, 255f);
        Debug.Log("êGÇÍÇΩ");
    }
    public void OnMouseExit()
    {
        image.color = new Color((188f/255f), (188f / 255f), (188f / 255f), 1);
        Debug.Log("ó£ÇµÇΩ");
    }

}
