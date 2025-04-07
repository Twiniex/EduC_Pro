using ModbusLib;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainController : MonoBehaviour
{
    public ConveyorController conveyor;
    public DetectController[] sensor = new DetectController[2];

    // Update is called once per frame
    void Update()
    {
        conveyor.bIsCw = PlcData.bFromPlc[0];
        conveyor.bIsCcw = PlcData.bFromPlc[1];
        PlcData.bToPlc[0] = sensor[0].bIsOn;
        PlcData.bToPlc[1] = sensor[1].bIsOn;
    }
}
