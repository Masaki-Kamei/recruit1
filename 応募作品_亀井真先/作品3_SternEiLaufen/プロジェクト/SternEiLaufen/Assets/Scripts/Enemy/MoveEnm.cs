using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveEnm : MonoBehaviour
{
    // Start is called before the first frame update
    private Vector2 pos;
    protected SpriteRenderer sr = null;

    public bool Lateral = false;
    public bool Vertical = false;
    public float WidthNumMin = 0;
    public float WidthNumMax = 0;
    public float Speed = 0;
    private int num = 1;
    private void Start()
    {
        pos = transform.position;
        sr = GetComponent<SpriteRenderer>();

    }
    void Update()
    {
        if (sr.isVisible)
        {

            if (Lateral)
            {
                // （ポイント）マイナスをかけることで逆方向に移動する。
                transform.Translate(transform.right * Time.deltaTime * Speed * num);

                if (transform.position.x > pos.x + WidthNumMax)
                {
                    num = -1;
                }
                if (transform.position.x < pos.x - WidthNumMin)
                {
                    num = 1;
                }
            }
            else if (Vertical)
            {

                transform.Translate(transform.up * Time.deltaTime * Speed * num);

                if (transform.position.y > pos.y + WidthNumMax)
                {
                    num = -1;
                }
                if (transform.position.y < pos.y - WidthNumMin)
                {
                    num = 1;
                }


            }
        }
    }
}
