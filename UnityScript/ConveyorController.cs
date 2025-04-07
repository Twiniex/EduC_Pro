using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConveyorController : MonoBehaviour
{
    public bool bIsCw, bIsCcw;
    List<Transform> boxes = new List<Transform>();

    void Update()
    {
        if (bIsCcw)
        {
            foreach (Transform box in boxes)
            {
                box.Translate(new Vector3(0.1f, 0f, 0f) * Time.deltaTime);
            }
        }
        if (bIsCw)
        {
            foreach (Transform box in boxes)
            {
                box.Translate(new Vector3(-0.1f, 0f, 0f) * Time.deltaTime);
            }
        }
    }

    private void OnCollisionEnter(Collision collision) => boxes.Add(collision.transform);
    private void OnCollisionExit(Collision collision) => boxes.Remove(collision.transform);
}
