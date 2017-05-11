using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Facebook.Unity;
using System;

public class FBManager : MonoBehaviour
{
    public Text userIdText;
    
    // Use this for initialization
    public void Awake()
    {
        if (!FB.IsInitialized)
        {
            FB.Init();
        }
        else
        {
            FB.ActivateApp();
        }
    }
    public void Login()
    {
        FB.LogInWithReadPermissions(callback: OnLogIn);
    }

    private void OnLogIn(ILoginResult result)
    {
        if (FB.IsLoggedIn)
        {
            AccessToken token = AccessToken.CurrentAccessToken;
            userIdText.text = token.UserId;
        }
        else
            Debug.Log("Cacelled Login");
    }

    

    public void Share()
    {
        FB.ShareLink(contentTitle: "hello world",
            contentDescription: "write something",
            contentURL: new System.Uri("https://play.google.com/store"),
            //photoURL: new System.Uri("link image"),
            callback: ShareCallback
            );
    }

    private void ShareCallback(IShareResult result)
    {
        if(result.Cancelled || !string.IsNullOrEmpty(result.Error))
        {
            Debug.Log("share link error: " + result.Error);
        }
        else if (!String.IsNullOrEmpty(result.PostId))
        {
            Debug.Log(result.PostId);
        }
        else
        {
            Debug.Log("ShareLink success!");
        }
    }

    public void Invite()
    {

    }

}
