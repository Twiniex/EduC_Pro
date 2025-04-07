using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ModbusLib;

public class ModbusController : MonoBehaviour
{
    ModbusClient client;

    // 연결 여부 확인용 프로퍼티
    public bool IsConnected => client != null && client.bIsConnected;

    void Start() => client = new ModbusClient();
    public void Connect() => client.Connect();
    public void Disconnect() => client.Disconnect();
}
