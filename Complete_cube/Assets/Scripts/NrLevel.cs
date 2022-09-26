using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class NrLevel : MonoBehaviour {

    public Text Nivel;
    private void Start()
    {
        Nivel.text = "LEVEL " + SceneManager.GetActiveScene().buildIndex.ToString("0");
    }
}
