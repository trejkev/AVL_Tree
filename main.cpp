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

#include  <iostream>
#include  <stdint.h> //dealing with uint
#include  <string>
#include  <fstream>
#include  <iostream>
#include  <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "avltree_ObtainData.hpp"
//#include "catch.hpp" // For testing
#include "AVL.hpp"

//for Standard Library usage
using namespace std;


int main(){
    int aux = ObtainData();

    /* Errors considered:
     * 1 -> Invalid input to select data file to use
     * 2 -> File to open is empty
     * 3 -> Action selection out of range or NAN
     * 4 -> ID to search witch decision is NAN
     * 5 -> List to read is NAN.
     * 6 -> ID inserted is out of range when inserting manually new node
     */

     return 0;
}
