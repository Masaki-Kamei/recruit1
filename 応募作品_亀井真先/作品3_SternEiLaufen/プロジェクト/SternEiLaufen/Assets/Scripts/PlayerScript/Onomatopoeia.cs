using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Onomatopoeia : MonoBehaviour
{
    public GameObject Player;
    public GameObject Egg;
    public GameObject Fried_Egg;
    public GameObject Boild_Egg;
    public GameObject Bard;

    private GameObject Type;
    private bool isOnoomatopoeia = false;
    private float DeleteTime=0;
    // Start is called before the first frame update
    void Start()
    {
        isOnoomatopoeia = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (isOnoomatopoeia)
        {
            DeleteTime+= Time.deltaTime;
            if (DeleteTime > 2)
            {
                isOnoomatopoeia = false;
                DeleteTime = 0;
                Destroy(Type);
            }
        }
    }

    public void OnoEgg()
    {

        SetType(Egg);
    }
    public void OnoFried_Egg()
    {
        SetType(Fried_Egg);
    }
    public void OnoBoild_Egg()
    {
        SetType(Boild_Egg);
    }
    public void OnoBard()
    {
        SetType(Bard);
    }

    public void SetType(GameObject gameObject)
    {
        Vector3 GroudPos = new Vector3(Player.transform.position.x, Player.transform.position.y+3.0f,0);
        //����(�����������,�o���ʒu,�o���p�x�iQuaternion.identity=��]�̃��[���h�}�g���b�N�X�����̂܂܎擾�j)
        Type = Instantiate(gameObject, GroudPos, Quaternion.identity);
        //�o�����Ǘ�(�o�����Ƃɐe�q�֌W�ɂ��AHierarchy�𐮗�)
        Type.transform.SetParent(transform);
        isOnoomatopoeia = true;
    }
}
