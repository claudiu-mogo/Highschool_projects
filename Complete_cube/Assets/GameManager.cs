using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    bool GameHasEnded = false;
    public float Delay = 1f;
    public GameObject CompleteLevelUI;
    public void CompleteLevel()
    {
        CompleteLevelUI.SetActive(true);
    }

    public void EndGame()
    {
        if (GameHasEnded == false)
        {
            GameHasEnded = true;

            Debug.Log("Game Over!");
            Invoke("Restart", Delay);
        }
    }
        void Restart()
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }

}
