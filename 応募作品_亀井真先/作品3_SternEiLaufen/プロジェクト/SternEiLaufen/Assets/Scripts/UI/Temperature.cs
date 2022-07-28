using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Temperature : MonoBehaviour
{

    [SerializeField]
    private Image Gauge;
    [SerializeField]
    private Image GaugeSub;
    private float valueDecreaseTo = 0;
    public GameObject player;
    private float GaugeLength;

    private float CurrentTemperature;
    private float MaxTemperature;

    void Start()
    {
        GaugeLength = 0;
        valueDecreaseTo = CurrentTemperature / MaxTemperature;
    }
    private void Update()
    {
        CurrentTemperature = player.GetComponent<DefaultPlayer>().CurrentTemperature;
        MaxTemperature = player.GetComponent<DefaultPlayer>().MaxTemperature;
        Debug.Log(CurrentTemperature);

        GaugeReduction(CurrentTemperature);

    }
    public void GaugeReduction(float reducationValue)
    {
        if (reducationValue == 0) GaugeLength = 0.0f;
        if (reducationValue == 1) GaugeLength = 0.083f;
        if (reducationValue == 2) GaugeLength = 0.17f;
        if (reducationValue == 3) GaugeLength = 0.245f;
        if (reducationValue == 4) GaugeLength = 0.334f;
        if (reducationValue == 5) GaugeLength = 0.432f;
        if (reducationValue == 6) GaugeLength = 0.5f;
        if (reducationValue == 7) GaugeLength = 0.58f;
        if (reducationValue == 8) GaugeLength = 0.662f;
        if (reducationValue == 9) GaugeLength = 0.75f;
        if (reducationValue == 10) GaugeLength = 1.0f;

        if (GaugeLength > Gauge.fillAmount) {
            Gauge.fillAmount += 0.01f;
            if(GaugeLength<= Gauge.fillAmount)
                Gauge.fillAmount = GaugeLength;

        }else if(GaugeLength < Gauge.fillAmount)
        {
            Gauge.fillAmount -= 0.01f;
            if (GaugeLength >= Gauge.fillAmount)
                Gauge.fillAmount = GaugeLength;

        }

    }
}
