using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MouseCameraController : MonoBehaviour
{
    public float moveSpeed = 0.5f;   // 카메라 이동 속도
    public float scrollSpeed = 100f;  // 줌 속도
    public float rotateSpeed = 0.5f; // 회전 속도

    private Vector3 lastMousePosition;
    private bool isPanning = false;
    private bool isRotating = false;

    void Update()
    {
        HandleMouseInput();
    }

    void HandleMouseInput()
    {
        // 마우스 휠 클릭 후 이동 → 카메라 이동
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

        // 마우스 우클릭 후 이동 → 카메라 회전
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

        // 마우스 휠 스크롤 → 줌 인/아웃
        float scroll = Input.GetAxis("Mouse ScrollWheel");
        transform.Translate(0, 0, scroll * scrollSpeed * Time.deltaTime, Space.Self);
    }
}