using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Collector : MonoBehaviour
{


    //���������I�u�W�F�N�g���\���ɂ���
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Ground")|| collision.CompareTag("GroundBonus"))
        {
            //�I�u�W�F�N�g���폜
            Destroy(collision.gameObject);
            //�X�N���v�g���w�肵�ĕϐ����󂯓n��
            //���𐶐�����N���X��p��
            //BackImageGenerator backImageGenerator;
            //�w�肵�����ϐ��������Ă���I�u�W�F�N�g���ŎQ��
            // GameObject obj = GameObject.Find("BackImageGenerator");
            //�Q�Ƃ������̂�p�ӂ������̂ɑ��
            // backImageGenerator = obj.GetComponent<BackImageGenerator>();
            //���ݏo�����Ă���I�u�W�F�N�g�̐������炷
            //backImageGenerator.GroundNum--;
        }
    }
}
