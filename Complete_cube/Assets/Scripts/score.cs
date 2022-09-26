using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class score : MonoBehaviour {

    public Transform player;
    public Text ScoreText;
	// Update is called once per frame
	void Update ()
    {
        int a;
        a = (int)player.position.z/3;
        ScoreText.text = a.ToString("0");

	}

}
