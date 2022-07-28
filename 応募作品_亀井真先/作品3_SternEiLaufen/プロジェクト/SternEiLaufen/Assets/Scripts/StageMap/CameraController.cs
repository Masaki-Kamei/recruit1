using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    Gamemanager GameManager;

    //�J�������ǂ������v���C���[���i�[
    [SerializeField]
    private GameObject Egg;
    //�J������X���W�̒���
    [SerializeField]
    private float CameraAdjustmentX=0;
    //�J�������v���C���[�ƈꏏ�ɓ����g���K�[
    private bool PlayerCamera = false;
    //�X�N���[�����̃v���C���[�̈ʒu
    private Vector3 ScreenPlayerPos;
    //�X�^�[�g���ɌŒ肷�邷��J�����̈ʒu
    private Vector3 StartCameraPos;
    //���݌Œ肷��J�����̈ʒu
    private Vector3 FixedCameraPos;
    //�ړ����x
    private float AddPosX = 0;
    //����
    private float DownTime = 0;
    // Start is called before the first frame update
    void Start()
    {
        GameManager = GameObject.Find("Gamemanager").GetComponent<Gamemanager>();

    }

    // Update is called once per frame
    void Update()
    {
        if (GameManager.GetGamePhase() != GameManager.GetDEAD())
        {
            if (PlayerCamera == false) StartCamera();
            if (PlayerCamera == true) CameraMove();
        }
    }

    //�v���C���[������̈ʒu�ő҂���
    void StartCamera()
    {
        //�v���C���[�̃I�u�W�F�N�g���Ɠ������̂��擾
        GameObject Player = GameObject.Find(Egg.name);
        //�i�[�������̂̈ʒu���擾
        Vector3 PlayerPos = Player.transform.position;
        ScreenPlayerPos = Camera.main.WorldToScreenPoint(PlayerPos);
        if (ScreenPlayerPos.x >= CameraAdjustmentX)
        {
            StartCameraPos = PlayerPos;
            PlayerCamera = true;
            CountStart countstartscript; //�ĂԃX�N���v�g�ɂ����Ȃ���
            countstartscript = GameObject.Find("CountCanvas").GetComponent<CountStart>(); //�t���Ă���X�N���v�g���擾
            countstartscript.OnStartTrigger();
        }
    }
    
    //�v���C���[�ƈꏏ�ɓ�������
    void CameraMove()
    {
        //�v���C���[�̃I�u�W�F�N�g���Ɠ������̂��擾
        GameObject Player = GameObject.Find(Egg.name);
        //�i�[�������̂̈ʒu���擾
        Vector3 PlayerPos = Player.transform.position;
        //�J�����̈ʒu��X���W�����i�[�����ʒu�ɍ��킹��
        /*transform.position = new Vector3(
            PlayerPos.x- (StartCameraPos.x), transform.position.y, transform.position.z);
        */
       float PosX = transform.position.x;
        if (Egg.GetComponent<DefaultPlayer>().GetIntervalDistance() > (Egg.GetComponent<DefaultPlayer>().GetAccelSpeed()-1)) {
            AddPosX = Egg.GetComponent<DefaultPlayer>().GetIntervalDistance();
        }
        //AddPosX = Egg.GetComponent<DefaultPlayer>().GetIntervalDistance();
        //�v���C���[�̉�ʓ��̈ʒu���W
        ScreenPlayerPos = Camera.main.WorldToScreenPoint(PlayerPos);
        //��ʂ̈ʒu�ɂ���ď���
        if ((ScreenPlayerPos.x < CameraAdjustmentX))
        {

            //�����X�s�[�h���P�ȏ�
            if (Egg.GetComponent<DefaultPlayer>().GetSpeed().x > 1)
            {
                //�Œ�ʒu�ɖ߂�ׂ̎���
                if (DownTime > 10)
                {
                    //�J����������������
                    AddPosX -= 1f;
                }
                else
                {
                    DownTime += Time.deltaTime; ;

                }
            }
        }
        else
        {
            DownTime = 0;
        }

        //�J�����ړ�
        transform.position = new Vector3(
            PosX + ( AddPosX * Time.deltaTime), transform.position.y, transform.position.z);
        //Debug.Log(Egg.GetComponent<DefaultPlayer>().GetIntervalDistance());
    }
}
