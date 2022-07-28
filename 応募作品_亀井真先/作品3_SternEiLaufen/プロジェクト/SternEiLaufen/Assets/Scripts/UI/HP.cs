using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class HP : MonoBehaviour
{
        public int DecreaseTime=3;

         public Color color_1, color_2, color_3, color_4;
        [SerializeField]
        private Image Gauge;
        [SerializeField]
        private Image GaugeSub;
        private float valueDecreaseTo=0;
        public GameObject player;


        private float CurrentHp;
        private float MaxHp;

    void Start()
    {
        valueDecreaseTo = CurrentHp / MaxHp;
    }
    private void Update()
    {
        CurrentHp = player.GetComponent<DefaultPlayer>().CurrentHp;
        MaxHp = player.GetComponent<DefaultPlayer>().MaxHp;

        GaugeReduction(CurrentHp);



    }
    public void GaugeReduction(float reducationValue)
    {
        float valueTo = reducationValue / MaxHp;

        if (valueTo > 0.25f)
        {
            Gauge.color = Color.Lerp(color_2, color_1, (valueTo - 0.25f) * 4f);
        }
        else if (valueTo > 0.1f)
        {
            Gauge.color = Color.Lerp(color_3, color_2, (valueTo - 0.1f) * 4f);
        }
        else
        {
            Gauge.color = Color.Lerp(color_4, color_3, valueTo * 4f);
        }
        
        // óŒÉQÅ[ÉWå∏è≠
        Gauge.fillAmount = valueTo;

    }



    
}
