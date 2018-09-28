/*
*File created by: Kevin Trejos
*
*Nomenclature  for this document is:
*l=local
*g=global
*sm=structure member
*cm=class member
*uX=unsigned int of X bits
*b=boolean
*s=string
*p=pointer
*st=structure
*
*Obtain data from a file and generates an AVL Tree node
*/

#include "avltree_ObtainData.hpp"
#include "AVL.hpp"
#include "catch.hpp" // For testing

uint8_t l_u8_TestInsert = 0;

//for Standard Library usage
using namespace std;
string  l_s_Name;
string  l_su64_ID;
string l_s_line;
int64_t l_i64_ID;
int l_iDecision = 0;
int l_iDecisionList = 0;
string l_sFileOpen = "Data.txt";
//uint64_t g_u64_InitTime = 0 , g_u64_FinalTime = 0 ,
//float g_u64_Time = 0;

int ObtainData()
{
   /* Define name of file where data is located
    * the file defined is used to obtain data */
  l_iDecision = 0;
  l_iDecisionList = 0;
  ChangeTXT:
    avltree AVLTree = avltree();
    ifstream  FileIn;
    FileIn.open(l_sFileOpen);
    if(!FileIn.is_open()){
     cout<<"Error: File is empty. File shall include name and IDs as follows: \nJuan Perez Lopez, 123456789"<<endl;
     return 2;
   }

   //data is obtained from file and saved
    std::chrono::high_resolution_clock::time_point g_u64_InitTime = std::chrono::high_resolution_clock::now();
    while(getline(FileIn,l_s_line)){
     stringstream ss(l_s_line);
     getline(ss,l_s_Name,',');
     getline(ss,l_su64_ID,',');

     stringstream iss(l_su64_ID);
     iss>>l_i64_ID;
     int  l_i64_ID = stoi(l_su64_ID);
     //initializing new node struc
     st_node* l_st_node= new st_node{
     l_i64_ID,l_s_Name,0, NULL,NULL, NULL, false};
     l_u8_TestInsert = AVLTree.AVL_Insert(AVLTree.l_pcmRootNode,l_st_node);
    }
    std::chrono::high_resolution_clock::time_point g_u64_FinalTime = std::chrono::high_resolution_clock::now();
    auto g_u64_Time = std::chrono::duration_cast<std::chrono::microseconds>(g_u64_FinalTime - g_u64_InitTime).count();
    cout<<"Time creating the tree was "<<g_u64_Time<<" us"<<endl;
    cout<<"\nWelcome to our AVL Tree. What do you want to do?"<<endl;
Decision:
    cout<<"1. Insert new person to our database. \n2. Search a person with the ID. \n3. Get the tree height."<<endl;
    cout<<"4. Get the root of the tree. \n5. Get the size of the tree. \n6. Create new tree. \n7. Exit."<<endl;
    cin>>l_iDecision;
    if(l_iDecision == 1){
      cout<<"Write the name of the person. \n";
      //getline(cin, l_s_Name);
      cin>>l_s_Name;
      cout<<"Write the ID of the person"<<endl;
      cin>>l_i64_ID;
      st_node* l_st_node= new st_node{
      l_i64_ID,l_s_Name,0, NULL,NULL, NULL, false};
      l_u8_TestInsert = AVLTree.AVL_Insert(AVLTree.l_pcmRootNode,l_st_node);
      cout<<"Person inserted in our database"<<endl;
      goto Decision;
    }
    else if(l_iDecision == 2){
      cout<<"Insert the ID of the person to search."<<endl;
      cin>>l_i64_ID;
      if(cin.fail()){
        cout<<"Invalid ID (not a number). Bye!"<<endl;
        return 4;
      }
      if(l_i64_ID > 999999999 || l_i64_ID < 100000000){
        cout<<"ID inserted out of range"<<endl;
        return 6;
      }
      struct st_node *Found = AVLTree.AVL_Search(AVLTree.l_pcmRootNode, l_i64_ID);
      goto Decision;
    }
    else if(l_iDecision == 3){
      cout<<"The height of the tree is "<<AVLTree.l_pcmRootNode->l_ssm_height<<"\n"<<endl;
      goto Decision;
    }
    else if(l_iDecision == 4){
      cout<<"The root of the tree is "<<AVLTree.l_pcmRootNode->l_u64_key<<endl;
      if(AVLTree.l_pcmRootNode->l_u32psm_leftchild != NULL){
        cout<<"its left child is "<<AVLTree.l_pcmRootNode->l_u32psm_leftchild->l_u64_key<<endl;
      }
      if(AVLTree.l_pcmRootNode->l_u32psm_rightchild != NULL){
        cout<<"its right child is "<<AVLTree.l_pcmRootNode->l_u32psm_rightchild->l_u64_key<<endl;
      }
      cout<<"its height is "<<AVLTree.l_pcmRootNode->l_ssm_height<<"\n"<<endl;
      goto Decision;
    }
    else if(l_iDecision == 5){
      cout<<"The tree has "<<AVLTree.AVL_NodesAmount()<<" valid nodes."<<"\n"<<endl;
      goto Decision;
    }
    else if(l_iDecision == 6){
      cout<<"You want to test the: \n1. 10 nodes. \n2. 100 nodes. \n3. 1000 nodes. \n4. 5000 nodes. \n5. 10000 nodes. \n"<<endl;
      cin>>l_iDecisionList;
      if(cin.fail()){
        cout<<"Option is NAN. Bye!"<<endl;
        return 5;
      }
      switch(l_iDecisionList){
        case 1:
          l_sFileOpen = "lista_10.txt";
          AVLTree.iNodesAmount = 0;
          goto ChangeTXT;
          break; // not needed
        case 2:
          l_sFileOpen = "lista_100.txt";
          AVLTree.iNodesAmount = 0;
          goto ChangeTXT;
          break; // not needed
        case 3:
          l_sFileOpen = "lista_1000.txt";
          AVLTree.iNodesAmount = 0;
          goto ChangeTXT;
          break; // not needed
        case 4:
          l_sFileOpen = "lista_5000.txt";
          AVLTree.iNodesAmount = 0;
          goto ChangeTXT;
          break; // not needed
        case 5:
          l_sFileOpen = "lista_10000.txt";
          AVLTree.iNodesAmount = 0;
          goto ChangeTXT;
          break; // not needed
        default:
          cout<<"Input out of range. Bye!"<<endl;
          return 1;
      }
      //goto Decision;
    }
    else if(l_iDecision == 7){
      cout<<"Bye!"<<endl;
      goto Exit;
    }
    else{
      cout<<"Invalid input, you shall write an integer number between 1 and 7."<<endl;
      return 3;
    }
  //  delete st_node;

  FileIn.close();
  Exit:
    return 0;
}

TEST_CASE("Verify the input to select data file to use (.txt)"){
  SECTION("Exit completed."){
    // l_iDecision = 7
    REQUIRE(ObtainData() == 0);
  }
  SECTION("Invalid choice of .txt to open with option 6 (number out of range when creating new tree)"){
    //l_iDecision = 6 then  0 > l_iDecisionList || l_iDecisionList >= 6;
    REQUIRE(ObtainData() == 1);
  }
  SECTION("The data input to create the tree is empty."){
    // Take one of the TXTs and clean up it all
    REQUIRE(ObtainData() == 2);
  }
  SECTION("Option selected out of range (number shall be between 1 and 7)."){
    // In main menu, write something out of range between 1 and 7
    REQUIRE(ObtainData() == 3);
  }
  SECTION("ID inserted is out of range when inserting manually new node."){
    // l_iDecision = 2 then write something out of range between 100000000 and 999999999
    REQUIRE(ObtainData() == 6);
  }
}
