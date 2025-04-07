using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LampController : MonoBehaviour
{
    MeshRenderer mesh;
    public Material matOn, matOff;
    public bool bIsOn;

    // Start is called before the first frame update
    void Start() => mesh = GetComponent<MeshRenderer>();
    void Update() => mesh.material = bIsOn ? matOn : matOff;
}
