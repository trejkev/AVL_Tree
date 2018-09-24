/*
*File created by: Erick Obando
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

/*#include  <iostream>
#include  <stdint.h> //dealing with uint
#include  <string>
#include  <fstream>
#include  <iostream>
#include  <sstream>
#include <stdlib.h>
#include <stdio.h>

*/
#include "avltree_ObtainData.hpp"
#include "AVL.hpp"

uint8_t l_u8_TestInsert = 0;

//for Standard Library usage
using namespace std;
string  l_s_Name;
string  l_su64_ID;
string l_s_line;
int64_t l_i64_ID;
int l_iDecision;
string l_sFileOpen = "Data.txt";

void ObtainData()
{
   /*Define name of file where data is located
   *the file defined is used to obtain data*/
  ChangeTXT:
    avltree AVLTree = avltree();
   ifstream  FileIn;
   FileIn.open(l_sFileOpen);

   //conversion from string to int
   //uint64_t l_u64_NumPeople = stoi(l_s_NumberData);

   //data is obtained from file and saved
    while(getline(FileIn,l_s_line)){
     stringstream ss(l_s_line);
     getline(ss,l_s_Name,',');
     getline(ss,l_su64_ID,',');

     stringstream iss(l_su64_ID);
     iss>>l_i64_ID;
     //int64_t  l_u64_ID = atoi(l_su64_ID);
    int  l_i64_ID = stoi(l_su64_ID);
 //initializing new node struc
    st_node* l_st_node= new st_node{
    l_i64_ID,l_s_Name,0, NULL,NULL, NULL, false};
    l_u8_TestInsert = AVLTree.AVL_Insert(AVLTree.l_pcmRootNode,l_st_node);
    }

    cout<<"\nWelcome to our AVL Tree. What do you want to do?"<<endl;

Decision:
    cout<<"1. Insert new person to out database. \n2. Search a person with the ID. \n3. Get the tree height."<<endl;
    cout<<"4. Get the root of the tree. \n5. Get the size of the tree. \n6. Create new tree. \n7. Exit."<<endl;
    cin>>l_iDecision;
    if(l_iDecision == 1){
      cout<<"Function not implemented.\n"<<endl;
      goto Decision;
    }
    if(l_iDecision == 2){
      cout<<"Insert the ID of the person to search."<<endl;
      cin>>l_i64_ID;
      struct st_node *Found = AVLTree.AVL_Search(AVLTree.l_pcmRootNode, l_i64_ID);
      goto Decision;
    }
    if(l_iDecision == 3){
      cout<<"The height of the tree is "<<AVLTree.l_pcmRootNode->l_ssm_height<<"\n"<<endl;
      goto Decision;
    }
    if(l_iDecision == 4){
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
    if(l_iDecision == 5){
      cout<<"the tree has "<<AVLTree.AVL_NodesAmount()<<" valid nodes."<<"\n"<<endl;
      goto Decision;
    }
    if(l_iDecision == 6){
      cout<<"You want to test the: \n1. 10 nodes. \n2. 100 nodes. \n3. 1000 nodes. \n4. 5000 nodes. \n5. 10000 nodes. \n"<<endl;
      cin>>l_iDecision;
      switch(l_iDecision){
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
      }
      goto Decision;
    }
  //  delete st_node;

FileIn.close();


}
