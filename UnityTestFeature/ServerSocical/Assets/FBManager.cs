using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Facebook.Unity;
using System;

public class FBManager : MonoBehaviour
{
    public Text userIdText;
    public string userID;
    private static FBManager instance = null;
    private static readonly object padlock = new object();

    public static FBManager Instance
    {
        get
        {
            if (instance == null)
            {
                lock(padlock)
                {
                    if(instance == null)
                        instance = new FBManager();
                }
            }
                
            return instance;
        }
    }

    // Use this for initialization
    public void Awake()
    {
        instance = new FBManager();
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
            userID = token.UserId;
            Debug.Log("userID:" + userID);
        }
        else
            Debug.Log("Cacelled Login");
    }

    

    public void Share()
    {
        //FB.ShareLink(contentTitle: "hello world",
        //    contentDescription: "write something",
        //    contentURL: new System.Uri("https://play.google.com/store"),
        //    //photoURL: new System.Uri("link image"),
        //    callback: ShareCallback
        //    );
        FB.FeedShare(linkCaption: "hello world",
            picture: new System.Uri("https://scontent-hkg3-1.xx.fbcdn.net/hphotos-xta1/v/t1.0-9/11002495_681185385326261_5595920565377356380_n.jpg?oh=709c1ebbeb3d74bec276d54ae611f222&oe=560E242F"),
            linkName: "check out this game",
            link: new System.Uri("https://www.facebook.com/"));
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
        FB.Mobile.AppInvite(appLinkUrl: new System.Uri(""),
            previewImageUrl: new System.Uri(""));
    }



}
