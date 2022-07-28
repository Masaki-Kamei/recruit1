using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JumpPad : MonoBehaviour
{
    public float Hight = 0;
    public float Width = 0;
    // Start is called before the first frame update

    // Update is called once per frame

    private void OnCollisionStay2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            collision.gameObject.GetComponent<DefaultPlayer>().AirTrigger = true;
            collision.gameObject.GetComponent<DefaultPlayer>().ResettotalFallTime();
            collision.gameObject.GetComponent<DefaultPlayer>().ResetGravity();
            collision.gameObject.GetComponent<DefaultPlayer>().goJump = true;
            collision.gameObject.GetComponent<DefaultPlayer>().ResetjumpKeyTime();
            collision.gameObject.transform.position = new Vector2(collision.gameObject.transform.position.x, (collision.gameObject.transform.position.y + 0.1f));
            Debug.Log("ジャンプパッド" + collision.gameObject.GetComponent<DefaultPlayer>().goJump);
            //collision.gameObject.GetComponent<DefaultPlayer>().SetJump(Hight);
            //collision.gameObject.GetComponent<DefaultPlayer>().jumpPower = collision.gameObject.GetComponent<DefaultPlayer>().jumpPower * 2.0f;
            collision.gameObject.GetComponent<DefaultPlayer>().jumpPower = Hight;
            Vector2 v=new Vector2( Width, collision.gameObject.GetComponent<DefaultPlayer>().GetSpeed().y);
            collision.gameObject.GetComponent<DefaultPlayer>().SetSpeed(v);
            collision.gameObject.GetComponent<DefaultPlayer>().SetGimmickTrigger(true);


        }


    }
}
