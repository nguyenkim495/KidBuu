using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using com.shephertz.app42.paas.sdk.csharp;
using com.shephertz.app42.paas.sdk.csharp.user;
using com.shephertz.app42.paas.sdk.csharp.storage;
using System;


public class UserManager : MonoBehaviour {

    private string apiKey = "cd18e9405709ff97ddfd5fb59b8d035ee75362e747f98e2e155c04a7423f26a7";
    private string secretKey = "4523e8a6ed3604a6c2f508390e2929604d4ccdd1422f36053a783f5ad3b21a6b";
    
    ServiceAPI serviceAPI;
    UserService userService;
    List<string> listUserID;
    public Text createUser;

    //storage userProfile
    private string DataBaseName = "PANDATABASE";
    public String jonsTest = "";// "{\"userID\":\"1185743988204572NUMBER2\",\"rank\":\"chicken\",\"Highest Score\":\"19090\"}";
    public string collectionName = "UserProfile";

    StorageService storageService = null;


    // Use this for initialization
    void Start () {
       // fbManager = new FBManager();
        App42Log.SetDebug(true);
        serviceAPI = new ServiceAPI(apiKey, secretKey);
        storageService = new StorageService(apiKey, secretKey);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void CreateNewUserProfile()
    {
        jonsTest = "{\"userID\":\"1185743988204572NUMBER2\",\"rank\":\"chicken\",\"Highest Score\":\"19090\"}";
        storageService.InsertJSONDocument(DataBaseName, collectionName, jonsTest, callBack: new UpdateCallback());
    }

    public void UpdateUserProfile()
    {
        //test update rank
        String newUpdateJson = "{\"userID\":\"1185743988204572\",\"rank\":\"MasterChicken\",\"Highest Score\":\"19090\"}";
        storageService.UpdateDocumentByKeyValue(DataBaseName, collectionName, "userID", "1185743988204572", newUpdateJson, new UpdateCallback());
    }

    public void GetLeaderboard()
    {
        storageService.FindAllDocuments(DataBaseName, collectionName, new LeaderboardCallback());
    }
    public class LeaderboardCallback : App42CallBack
    {
        public void OnSuccess(object response)
        {
            Storage storage = (Storage)response;
            IList<Storage.JSONDocument> jsonDocList = storage.GetJsonDocList();
            for(int i = 0; i < jsonDocList.Count; i++)
            {
                Debug.Log("jon Doc: " + jsonDocList[i].GetJsonDoc());
            }
               

        }
        public void OnException(Exception e)
        {

        }
    }

    public class UpdateCallback : App42CallBack
    {
        public void OnSuccess(object response)
        {
           

        }
        public void OnException(Exception e)
        {
            
        }
    }

    public void CreatUser()
    {
        string userID = "1185743988204572"; //userID
        Debug.Log("server" + userID);
        userService = serviceAPI.BuildUserService();
        userService.CreateUser(uName: userID, pwd: "NULL", emailAddress: "hung.nguyenvan2@gmail.com", callBack: new CreateUserCallback());
    }
    public class CreateUserCallback : App42CallBack
    {
        public void OnSuccess(object response)
        {
            User user = (User)response;
            /* This will create user in App42 cloud and will return User object */
            App42Log.Console("userName is " + user.GetUserName());
            App42Log.Console("emailId is " + user.GetEmail());

            


        }
        public void OnException(Exception e)
        {
            App42Log.Console("Exception : " + e);
            App42Exception exception = (App42Exception)e;
            int appErrorCode = exception.GetAppErrorCode();
            if (appErrorCode == 2001)
                Debug.Log("have early profile");
        }
    }

    public void GetUserProfile(string userName)
    {
        userService = serviceAPI.BuildUserService();
        userService.GetUser(userName: userName, callBack: GetUserProfileCallback);
    }
    public App42CallBack GetUserProfileCallback { get; private set; }
    

    public List<string> GetAllUserID()
    {
        userService = serviceAPI.BuildUserService();
        userService.GetAllUsers(callBack: GetAllUsers);
        
        return listUserID;
    }
    public App42CallBack GetAllUsers { get; private set; }
}
