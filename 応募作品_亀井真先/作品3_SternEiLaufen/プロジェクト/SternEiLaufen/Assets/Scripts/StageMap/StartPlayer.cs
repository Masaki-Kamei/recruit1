using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartPlayer : MonoBehaviour
{
    //�I�u�W�F�N�g
    [SerializeField]
    private GameObject Player;
    [SerializeField]
    private float PosX = 0;
    [SerializeField]
    private float PosY = 0;

    // Start is called before the first frame update
    void Start()
    {
        StartNewPlayer();
    }

    // Update is called once per frame
    void Update()
    {

    }


    //�v���C���[�̐�������
    void StartNewPlayer()
    {
        /*Vector3 PlayerPos = Vector3.zero;
        GameObject NewPlayer;
        //�o���ʒu�̊i�[
        PlayerPos = new Vector3(PosX, PosY, 0f);
        //����(�����������,�o���ʒu,�o���p�x�iQuaternion.identity=��]�̃��[���h�}�g���b�N�X�����̂܂܎擾�j)
        NewPlayer = Instantiate(Player, PlayerPos, Quaternion.identity);
        //��������閼�O�����̖��O�ɂ���
        NewPlayer.name = Player.name;
        //�o�����Ǘ�(�o�����Ƃɐe�q�֌W�ɂ��AHierarchy�𐮗�)
        NewPlayer.transform.SetParent(transform);
        */
        Player.SetActive(true);
        Player.transform.position = new Vector2(PosX, PosY);

    }

}
