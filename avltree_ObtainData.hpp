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
#ifndef avltree_ObtainData
#define avltree_ObtainData

#include  <iostream>
#include  <stdint.h> //dealing with uint
#include  <string>
#include  <fstream>
#include  <iostream>
#include  <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "AVL.hpp"
//for Standard Library usage
using namespace std;

//defining variables
//string  l_s_NumberData;

void ObtainData(void);


/*
*Node has:
*Key:data of interest
*leftchild:data lower or equal than key
*rightchild:data greater than key
*height: AVL trees en AVL shall comply with |heightlchild-heightlright|<=1,
*
*In AVL Trees O(logn)
*/


//Creating the structure for the node
struct st_node
{
  //string  l_u64_key;
  int64_t l_u64_key;
  string  l_ssm_Name;
  int32_t  l_ssm_height;
  st_node  *l_u32psm_leftchild;
  st_node  *l_u32psm_rightchild;
  st_node  *st_parent;
  bool  l_bsm_isroot; //flag to define if it is a root TRUE=is root

};

#endif
