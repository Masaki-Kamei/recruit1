using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackImageGenerator : MonoBehaviour
{
    //�ϐ�
    //�I�u�W�F�N�g
    [SerializeField]
    private GameObject[] GroundPrefab;
    [SerializeField]
    private GameObject[] GroundBonusPrefab;

    //�o����
    [SerializeField]
    private float GroundSpawn = 0;
    //���X�g�Ǘ�
    private List<GameObject> GroundPool = new List<GameObject>();
    //���X�g�Ǘ�
    private List<GameObject> GroundBonusPool = new List<GameObject>();

    //�ʒu����
    [SerializeField]
    private float GroundAdjustmentPosY = 0.0f;
    //�������镝
    [SerializeField]
    private float GroundDistanceX = 17.82f;
    //�ʒu����
    [SerializeField]
    private float GroundBonusAdjustmentPosY = 0.0f;
    //�������镝
    [SerializeField]
    private float GroundBonusDistanceX = 17.82f;

    //�\������ʒu
    private float NextGroundPosX;
    //��ނ��Ƃɐ������鐔
    //private int GenerationKindsNum = 3;
    //�X�^�[�g���̃}�b�v�\����
    private int StartNewGroundNum = 1;

    //��������Ă��錻�݂̐�
    private int GroundNum = 0;
    //��������Ă���I�u�W�F�N�g
    GameObject[] GroundNumObjects;

    // Start is called before the first frame update
    void Start()
    {
        GroundGeneration();
        StartNewGround();
    }

    // Update is called once per frame
    void Update()
    {
        NumCheck("Ground");
        GroundSetNum();

    }

    //���̐�������
    void GroundGeneration()
    {
        for (int i = 0; i < GroundPrefab.Length; i++)
        {
            Vector3 GroudPos = Vector3.zero;
            GameObject NewGround;
            //�o���ʒu�̊i�[
            GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
            //����(�����������,�o���ʒu,�o���p�x�iQuaternion.identity=��]�̃��[���h�}�g���b�N�X�����̂܂܎擾�j)
            NewGround = Instantiate(GroundPrefab[i], GroudPos, Quaternion.identity);
            //�o�����Ǘ�(�o�����Ƃɐe�q�֌W�ɂ��AHierarchy�𐮗�)
            NewGround.transform.SetParent(transform);
            //���X�g�ɒǉ�(��ނ��Ƃ̐�)
            GroundPool.Add(NewGround);
            //�I�u�W�F�N�g���\��
            GroundPool[i].SetActive(false);


        }
        //�{�[�i�X�X�e�[�W
        for(int i=0;i< GroundBonusPrefab.Length;i++)
        {
            Vector3 GroudPos = Vector3.zero;
            GameObject NewGround;
            //�o���ʒu�̊i�[
            GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
            //����(�����������,�o���ʒu,�o���p�x�iQuaternion.identity=��]�̃��[���h�}�g���b�N�X�����̂܂܎擾�j)
            NewGround = Instantiate(GroundPrefab[i], GroudPos, Quaternion.identity);
            //�o�����Ǘ�(�o�����Ƃɐe�q�֌W�ɂ��AHierarchy�𐮗�)
            NewGround.transform.SetParent(transform);
            //���X�g�ɒǉ�(��ނ��Ƃ̐�)
            GroundBonusPool.Add(NewGround);
            //�I�u�W�F�N�g���\��
            GroundBonusPool[i].SetActive(false);

        }
    }

    void StartNewGround()
    {
        Vector3 GroudPos = Vector3.zero;

        for (int i = 0; i < StartNewGroundNum; i++)
        {
            //��ނ��Ƃ̃}�b�v�̕\�������鐔
            GameObject NewGround;
            GameObject NewGroundBonus;

            if (i == 0)
            {
                //�o���ʒu�̊i�[
                GroudPos = new Vector3(0, GroundAdjustmentPosY, 0f);
                //����(�����������,�o���ʒu,�o���p�x�iQuaternion.identity=��]�̃��[���h�}�g���b�N�X�����̂܂܎擾�j)
                NewGround = Instantiate(GroundPrefab[0], GroudPos, Quaternion.identity);
                //�o�����Ǘ�(�o�����Ƃɐe�q�֌W�ɂ��AHierarchy�𐮗�)
                NewGround.transform.SetParent(transform);
                NextGroundPosX += GroundDistanceX;

                //�o���ʒu�̊i�[
                GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
                //����(�����������,�o���ʒu,�o���p�x�iQuaternion.identity=��]�̃��[���h�}�g���b�N�X�����̂܂܎擾�j)
                NewGroundBonus = Instantiate(GroundBonusPrefab[0], GroudPos, Quaternion.identity);
                //�o�����Ǘ�(�o�����Ƃɐe�q�֌W�ɂ��AHierarchy�𐮗�)
                NewGroundBonus.transform.SetParent(transform);
                NextGroundPosX += GroundBonusDistanceX;

            }
            //�o���ʒu�̊i�[
            //GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
            //����(�����������,�o���ʒu,�o���p�x�iQuaternion.identity=��]�̃��[���h�}�g���b�N�X�����̂܂܎擾�j)
            //NewGround = Instantiate(GroundPrefab[0], GroudPos, Quaternion.identity);
            //�o�����Ǘ�(�o�����Ƃɐe�q�֌W�ɂ��AHierarchy�𐮗�)
            //NewGround.transform.SetParent(transform);
            //���̏��̏o���ʒu
            //NextGroundPosX += GroundDistanceX;
            //GroundNum++;

        }

    }

    //�o��������
    void SetNewGround()
    {
        Vector3 GroudPos = Vector3.zero;
        //  �����_���Ŏ�ނ����߂�
        int RandomKinds = Random.Range(0, GroundPool.Count);
        //��ނ��Ƃ̃}�b�v�̕\�������鐔
        GameObject NewGround;
        //�o���ʒu�̊i�[
        GroudPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
        //����(�����������,�o���ʒu,�o���p�x�iQuaternion.identity=��]�̃��[���h�}�g���b�N�X�����̂܂܎擾�j)
        NewGround = Instantiate(GroundPrefab[RandomKinds], GroudPos, Quaternion.identity);
        //�o�����Ǘ�(�o�����Ƃɐe�q�֌W�ɂ��AHierarchy�𐮗�)
        NewGround.transform.SetParent(transform);
        //���̏��̏o���ʒu
        NextGroundPosX += GroundDistanceX;

        //�{�[�i�X�X�e�[�W
        Vector3 GroudBonusPos = Vector3.zero;
        RandomKinds = Random.Range(0, GroundBonusPool.Count);
        GameObject NewGroundBounus;
        //�o���ʒu�̊i�[
        GroudBonusPos = new Vector3(NextGroundPosX, GroundAdjustmentPosY, 0f);
        //����(�����������,�o���ʒu,�o���p�x�iQuaternion.identity=��]�̃��[���h�}�g���b�N�X�����̂܂܎擾�j)
        NewGroundBounus = Instantiate(GroundBonusPrefab[RandomKinds], GroudBonusPos, Quaternion.identity);
        //�o�����Ǘ�(�o�����Ƃɐe�q�֌W�ɂ��AHierarchy�𐮗�)
        NewGroundBounus.transform.SetParent(transform);
        //���̏��̏o���ʒu
        NextGroundPosX += GroundBonusDistanceX;

        //GroundNum++;

    }


    //���ݕ\������Ă��鐔���擾
    void GroundSetNum()
    {


        if (GroundNum < GroundSpawn)
        {
            //�}�b�v�\��
            SetNewGround();
            NumCheck("Ground");

        }

    }

    //���݂̃I�u�W�F�N�g�̐�������Ă��鐔���擾
    //  string TagName  �w�肵���I�u�W�F�N�g�̃^�O��
    void NumCheck(string TagName)
    {
        //��������Ă���I�u�W�F�N�g���i�[
        GroundNumObjects = GameObject.FindGameObjectsWithTag(TagName);
        //���݂̃I�u�W�F�N�g�̐�
        GroundNum = GroundNumObjects.Length;
    }

}

