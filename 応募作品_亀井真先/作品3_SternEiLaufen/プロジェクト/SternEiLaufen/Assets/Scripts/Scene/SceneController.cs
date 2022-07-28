using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading.Tasks;
using UnityEngine.SceneManagement;

public class SceneController : MonoBehaviour
{
    public GameObject fade;//インスペクタからPrefab化したCanvasを入れる
    public GameObject fadeCanvas;//操作するCanvas、タグで探す

    void Start()
    {
        if (!FadeManager.isFadeInstance)//生成フラグが呼び出されてないなら
        {
            Instantiate(fade);      //生成
        }
        Invoke("findFadeObject", 0.02f);//起動時用にCanvasの召喚をちょっと待つ
    }

    void findFadeObject()
    {
        fadeCanvas = GameObject.FindGameObjectWithTag("Fade");//Canvasのタグをみつける
        fadeCanvas.GetComponent<FadeManager>().fadeIn();//フェードインフラグを立てる
    }

    public async void sceneChange()//ボタン操作などで呼び出す
    {
        fadeCanvas.GetComponent<FadeManager>().fadeOut();//フェードアウトフラグを立てる
        await Task.Delay(200);//暗転するまで待つ
    }
}