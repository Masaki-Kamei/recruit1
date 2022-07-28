using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gamemanager : MonoBehaviour
{
    private int GamePhase=0;

    private int START=1;
    private int PLAY = 2;
    private int RISULT = 3;
    private int DEAD = 4;
    // Start is called before the first frame update
    void Start()
    {
        GamePhase = 1;
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void SetSTART() { GamePhase = START; }
    public int GetSTART() { return START; }

    public void SetPLAY() { GamePhase = PLAY; }
    public int GetPLAY() { return PLAY; }

    public void SetRISULT() { GamePhase = RISULT; }
    public int GetRISULT() { return RISULT; }

    public void SetDEAD() { GamePhase = DEAD; }
    public int GetDEAD() { return DEAD; }


    public int GetGamePhase() { return GamePhase; }

}
