using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class ExpScript : MonoBehaviour
{
    public TextMeshProUGUI CountEXP;
    Ranking ranking;
    // Start is called before the first frame update
    void Start()
    {
        ranking = GameObject.Find("RankingObject").GetComponent<Ranking>();
    }

    // Update is called once per frame
    void Update()
    {
        CountEXP.text = ranking.GetEXPNum().ToString();

    }
}
