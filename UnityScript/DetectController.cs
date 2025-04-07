using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DetectController : MonoBehaviour
{
    public LampController[] lamps = new LampController[2];
    public bool bIsOn;
    // Start is called before the first frame update
    void Start()
    {
        foreach (LampController lamp in lamps)
            lamp.bIsOn = false;
    }

    private void OnTriggerEnter(Collider other)
    {
        foreach(LampController lamp in lamps)
        {
            lamp.bIsOn = true;
        }
        bIsOn = true;
    }

    private void OnTriggerExit(Collider other)
    {
        foreach (LampController lamp in lamps)
        {
            lamp.bIsOn = false;
        }
        bIsOn = false;
    }
}
