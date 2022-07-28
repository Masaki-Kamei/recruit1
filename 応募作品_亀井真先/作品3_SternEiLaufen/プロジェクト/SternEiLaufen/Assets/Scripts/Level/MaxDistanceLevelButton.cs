using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class MaxDistanceLevelButton : MonoBehaviour
{
    private ButtonLevelSE buttonLevelSE;

    // Start is called before the first frame update
    public GameObject playerlevelup;
    private int MDLevel;
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
        MDLevel = playerlevelup.GetComponent<PlayerLevelUp>().GetMaxDistance();
        Exp = playerlevelup.GetComponent<PlayerLevelUp>().GetEXP();
        SetNextLevelEXP();
        CountScore.text = NextLevelExp.ToString();
        if (Exp < NextLevelExp) CountScore.color = new Color(1f, 0f, 0f, 1);
        else if (MDLevel == 10)
        {
            CountScore.color = new Color(1f, 0f, 0f, 1);
            CountScore.text = "Max";

        }

    }

    public void OnClick()
    {
        if (MDLevel < 10)
        {
            if (Exp >= NextLevelExp)
            {
                MDLevel++;
                Exp -= NextLevelExp;
                playerlevelup.GetComponent<PlayerLevelUp>().SetEXP(Exp);
                playerlevelup.GetComponent<PlayerLevelUp>().SetMaxDistance(MDLevel);
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
        if (MDLevel == 1)
        {
            NextLevelExp = Level2;
        }
        else if (MDLevel == 2)
        {
            NextLevelExp = Level3;

        }
        else if (MDLevel == 3)
        {
            NextLevelExp = Level4;

        }
        else if (MDLevel == 4)
        {
            NextLevelExp = Level5;

        }
        else if (MDLevel == 5)
        {
            NextLevelExp = Level6;

        }
        else if (MDLevel == 6)
        {
            NextLevelExp = Level7;

        }
        else if (MDLevel == 7)
        {
            NextLevelExp = Level8;

        }
        else if (MDLevel == 8)
        {
            NextLevelExp = Level9;

        }
        else if (MDLevel == 9)
        {
            NextLevelExp = Level10;

        }
        else
        {
            NextLevelExp = 99999;

        }


    }
}
