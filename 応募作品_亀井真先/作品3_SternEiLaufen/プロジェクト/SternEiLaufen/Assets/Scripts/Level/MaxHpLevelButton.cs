using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class MaxHpLevelButton : MonoBehaviour
{
    private ButtonLevelSE buttonLevelSE;

    // Start is called before the first frame update
    public GameObject playerlevelup;
    private int MHLevel;
    private int Exp;
    private int NextLevelExp;
    public TextMeshProUGUI CountScore;

    public int Level2 = 0;
    public int Level3 = 0;
    public int Level4 = 0;
    public int Level5 = 0;
    public int Level6 = 0;
    public int Level7 = 0;
    public int Level8 = 0;
    public int Level9 = 0;
    public int Level10 = 0;

    // Start is called before the first frame update
    void Start()
    {
        buttonLevelSE = GetComponent<ButtonLevelSE>();
    }

    // Update is called once per frame
    void Update()
    {
        //ŒoŒ±’l‚ÆƒŒƒxƒ‹‚ðŽæ“¾
        MHLevel = playerlevelup.GetComponent<PlayerLevelUp>().GetMaxHp();
        Exp = playerlevelup.GetComponent<PlayerLevelUp>().GetEXP();
        SetNextLevelEXP();
        CountScore.text = NextLevelExp.ToString();
        if (Exp < NextLevelExp) CountScore.color = new Color(1f, 0f, 0f, 1);
        else if (MHLevel == 10)
        {
            CountScore.color = new Color(1f, 0f, 0f, 1);
            CountScore.text = "Max";

        }
    }

    public void OnClick()
    {
        if (MHLevel < 10)
        {
            if (Exp >= NextLevelExp)
            {
                MHLevel++;
                Exp -= NextLevelExp;
                playerlevelup.GetComponent<PlayerLevelUp>().SetEXP(Exp);
                playerlevelup.GetComponent<PlayerLevelUp>().SetMaxHp(MHLevel);
                buttonLevelSE.ClickLevelSE();

            }
            else
            {
                buttonLevelSE.ClickNotLevelSE();

            }
        }
        else
        {
            buttonLevelSE.ClickNotLevelSE();

        }

    }

    public void SetNextLevelEXP()
    {
        if (MHLevel == 1)
        {
            NextLevelExp = Level2;
        }
        else if (MHLevel == 2)
        {
            NextLevelExp = Level3;

        }
        else if (MHLevel == 3)
        {
            NextLevelExp = Level4;

        }
        else if (MHLevel == 4)
        {
            NextLevelExp = Level5;

        }
        else if (MHLevel == 5)
        {
            NextLevelExp = Level6;

        }
        else if (MHLevel == 6)
        {
            NextLevelExp = Level7;

        }
        else if (MHLevel == 7)
        {
            NextLevelExp = Level8;

        }
        else if (MHLevel == 8)
        {
            NextLevelExp = Level9;

        }
        else if (MHLevel == 9)
        {
            NextLevelExp = Level10;

        }
        else
        {
            NextLevelExp = 99999;

        }


    }
}
