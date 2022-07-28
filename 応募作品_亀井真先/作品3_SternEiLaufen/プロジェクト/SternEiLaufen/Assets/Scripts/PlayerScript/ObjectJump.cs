using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectJump : MonoBehaviour
{
    [SerializeField]
    public float boundHeight;
    [HideInInspector]
    public bool playerStepOn;
    [SerializeField]
    public float stepOnRate;

    // Start is called before the first frame update
    private CapsuleCollider2D capcol = null;
    void Start()
    {
        capcol = GetComponent<CapsuleCollider2D>();
    }
    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.tag == "Enemy")
        {
            //“¥‚İ‚Â‚¯”»’è‚É‚È‚é‚‚³
            float stepOnHeight = (capcol.size.y * (stepOnRate / 100f));
            //“¥‚İ‚Â‚¯”»’è‚Ìƒ[ƒ‹ƒhÀ•W
            float judgePos = transform.position.y - (capcol.size.y / 2f) + stepOnHeight;
            foreach (ContactPoint2D p in collision.contacts)
            {
                if (p.point.y < judgePos)
                {

                }
                else
                {

                }
            }
        }
    }

}
