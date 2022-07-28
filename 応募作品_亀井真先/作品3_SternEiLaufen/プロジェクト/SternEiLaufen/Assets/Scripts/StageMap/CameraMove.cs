using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{

    [SerializeField]
    private float MoveSpeed = 0.04f;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        CameraMoveDebug();
    }

    private void CameraMoveDebug()
    {
        transform.Translate(MoveSpeed, 0f, 0.0f);
    }
}
