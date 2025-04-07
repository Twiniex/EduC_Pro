using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MouseCameraController : MonoBehaviour
{
    public float moveSpeed = 0.5f;   // ī�޶� �̵� �ӵ�
    public float scrollSpeed = 100f;  // �� �ӵ�
    public float rotateSpeed = 0.5f; // ȸ�� �ӵ�

    private Vector3 lastMousePosition;
    private bool isPanning = false;
    private bool isRotating = false;

    void Update()
    {
        HandleMouseInput();
    }

    void HandleMouseInput()
    {
        // ���콺 �� Ŭ�� �� �̵� �� ī�޶� �̵�
        if (Input.GetMouseButtonDown(2))
        {
            isPanning = true;
            lastMousePosition = Input.mousePosition;
        }
        else if (Input.GetMouseButtonUp(2))
        {
            isPanning = false;
        }

        if (isPanning)
        {
            Vector3 delta = Input.mousePosition - lastMousePosition;
            transform.Translate(-delta.x * moveSpeed * Time.deltaTime, -delta.y * moveSpeed * Time.deltaTime, 0);
            lastMousePosition = Input.mousePosition;
        }

        // ���콺 ��Ŭ�� �� �̵� �� ī�޶� ȸ��
        if (Input.GetMouseButtonDown(1))
        {
            isRotating = true;
            lastMousePosition = Input.mousePosition;
        }
        else if (Input.GetMouseButtonUp(1))
        {
            isRotating = false;
        }

        if (isRotating)
        {
            Vector3 delta = Input.mousePosition - lastMousePosition;
            transform.Rotate(Vector3.up, delta.x * rotateSpeed, Space.World);
            transform.Rotate(Vector3.right, -delta.y * rotateSpeed, Space.Self);
            lastMousePosition = Input.mousePosition;
        }

        // ���콺 �� ��ũ�� �� �� ��/�ƿ�
        float scroll = Input.GetAxis("Mouse ScrollWheel");
        transform.Translate(0, 0, scroll * scrollSpeed * Time.deltaTime, Space.Self);
    }
}