using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimationControl : MonoBehaviour
{
    private Animator animator;

    private void Awake()
    {
        animator = GetComponent<Animator>();
    }
    // Start is called before the first frame update

    //鳥のアニメーション
    public void ChangeBardAnimation(bool bard)
    {
        animator.SetBool("Bard", bard);
    }
    public void ChangeBoiledEggAnimation(bool boiledegg)
    {
        animator.SetBool("Boiled_Egg", boiledegg);
    }
    public void ChangeFriedEggAnimation(bool friedegg)
    {
        animator.SetBool("Fried_Egg", friedegg);
    }

    public void RunAnimation(bool run)
    {
        animator.SetBool("Run", run);
    }
    public void JumpAnimation(bool jump)
    {
        animator.SetBool("Jump", jump);
    }
    public void DoubleJumpAnimation()
    {
        animator.SetTrigger("DoubleJump");
    }
    public void FlyAnimation(bool fly)
    {
        animator.SetBool("Fly", fly);
    }

    public void ChangeAnimation(bool change)
    {
        animator.SetBool("Change", change);

    }
    public void DeadAnimation(bool dead)
    {
        animator.SetBool("Dead", dead);
    }

    public void TestAnimation(bool fly)
    {
        animator.SetBool("test", fly);
    }
    public void OnGroundAnimation()
    {
        animator.SetTrigger("OnGround");

    }
    public void ReverseAnimation(bool reverse)
    {
        animator.SetBool("Reverse", reverse);

    }
}
