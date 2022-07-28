using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeAnimation : MonoBehaviour
{
    private Onomatopoeia onomatopoeia;
    private GameObject Player;
    public GameObject onomatopoeiaObj;

    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        onomatopoeia = onomatopoeiaObj.GetComponent<Onomatopoeia>();
        Player = GameObject.Find("Egg 1");

    }

    public void ChangeNotActiv()
    {
        float CurrentTemperature = Player.GetComponent<DefaultPlayer>().GetCurrentTemperature();
        gameObject.SetActive(false);
        if(CurrentTemperature >= 0 && CurrentTemperature <= 3) onomatopoeia.OnoEgg();
        else if(CurrentTemperature >= 4 && CurrentTemperature <= 6) onomatopoeia.OnoBoild_Egg(); 
        else if(CurrentTemperature >= 7 && CurrentTemperature <= 9) onomatopoeia.OnoFried_Egg();
        else  onomatopoeia.OnoBard();

    }

}
