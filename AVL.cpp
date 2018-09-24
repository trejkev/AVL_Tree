/*
 * Date: sep 15, 2018
 * Created by: K.Trejos
 */

#include "AVL.hpp"
#include "avltree_ObtainData.hpp"
#include <stdio.h>

using namespace std;


int32_t k = 0; // Balance constant
struct st_node *LastNodeIns = NULL;
struct st_node *l_pcmAuxNode3 = NULL;

avltree::avltree(){
 std::cout<<"AVL created \n"<<std::endl;
 // Do nothing, just declare it, the magic comes later
}

int avltree::AVL_NodesAmount(){return iNodesAmount;}

int avltree::AVL_Insert(struct st_node *ActualNode, struct st_node *InsertedNode){
  /* 0 everything is ok
   * 1 Equal IDs
   * 2 ID out of range
   */
  //cout<<"\n Node inserted is "<<InsertedNode->l_u64_key<<endl;

  if(InsertedNode->l_u64_key < 100000000 || InsertedNode->l_u64_key > 999999999){
    cout<<"ERROR: The ID shall be between 1 0000 0000 and 9 9999 9999."<<endl;
    return 2; // Ced shall be between the defined range
  }

  //if(ActualNode != NULL){
    //cout<<"\nNode inserted is "<<InsertedNode->l_u64_key;
    //cout<<" and is being compared with "<<ActualNode->l_u64_key<<endl;
//  }

  LastNodeIns = InsertedNode;

	//Check if this is the first inserted node
	if(l_pcmRootNode == NULL){
		l_pcmRootNode = InsertedNode;                               // Assign InsertedNode as the root node
		InsertedNode->l_ssm_height = 1;
		InsertedNode->l_bsm_isroot = true;
		l_pcmRootNode->l_bsm_isroot = true;
    iNodesAmount++;
		return 0;
	}

  if(InsertedNode->l_u64_key == ActualNode->l_u64_key){
    if(l_pcmRootNode == ActualNode){
      l_pcmRootNode = NULL;
      InsertedNode->l_bsm_isroot = false;
      l_pcmRootNode->l_bsm_isroot = false;
      iNodesAmount--;
    }
    cout<<"ERROR: There cannot be 2 equal IDs."<<endl;
    return 1; // There cannot be any couple of ceds equal
  }

	InsertedNode->st_parent = ActualNode;  // The actual node will be the parent of Inserted node

	// Left branch case
	if(InsertedNode->l_u64_key < ActualNode->l_u64_key){
		if(ActualNode->l_u32psm_leftchild == NULL){                 // If left child is empty assign inserted node there
			ActualNode->l_u32psm_leftchild = InsertedNode;
			InsertedNode->l_ssm_height = 1; //last node of the tree
      iNodesAmount++;
      //cout<<"Insertion OK of "<<InsertedNode->l_u64_key<<endl;
      return 0;
		}else{
      AVL_Insert(ActualNode->l_u32psm_leftchild , InsertedNode);
    }
	}

	// Right branch case
	if(InsertedNode->l_u64_key > ActualNode->l_u64_key){
		if(ActualNode->l_u32psm_rightchild == NULL){                // If right child is empty assign inserted node there
			ActualNode->l_u32psm_rightchild = InsertedNode;
			InsertedNode->l_ssm_height = 1; //last node of the tree
      iNodesAmount++;
      //cout<<"Insertion OK of "<<InsertedNode->l_u64_key<<endl;
      return 0;
		}else{
      AVL_Insert(ActualNode->l_u32psm_rightchild , InsertedNode);
    }
	}



	// Calculate the height of its parental ancestry
	AVL_CalcHeight(LastNodeIns);


}



int32_t avltree::l_u32cmK_Rupture(struct st_node *LastNodeInserted){
	//if(LastNodeInserted->l_bsm_isroot == false){l_pcmNewNode = LastNodeInserted->st_parent;}

	//Case where there is lc and rc
	if(LastNodeInserted->l_u32psm_leftchild != NULL && LastNodeInserted->l_u32psm_rightchild != NULL){
		l_pcmAuxNode1 = LastNodeInserted->l_u32psm_leftchild;
		l_pcmAuxNode2 = LastNodeInserted->l_u32psm_rightchild;
		return ((l_pcmAuxNode1->l_ssm_height)-(l_pcmAuxNode2->l_ssm_height));
	}
	// if lc == null
	if(LastNodeInserted->l_u32psm_leftchild == NULL && LastNodeInserted->l_u32psm_rightchild != NULL){
		l_pcmAuxNode2 = LastNodeInserted->l_u32psm_rightchild;
		return (0-(l_pcmAuxNode2->l_ssm_height));
	}
	//if rc == null
	if(LastNodeInserted->l_u32psm_leftchild != NULL && LastNodeInserted->l_u32psm_rightchild == NULL){
		l_pcmAuxNode1 = LastNodeInserted->l_u32psm_leftchild;
		return ((l_pcmAuxNode1->l_ssm_height)-0);
	}
	//if rc == lc == null
	if(LastNodeInserted->l_u32psm_leftchild == NULL && LastNodeInserted->l_u32psm_rightchild == NULL){
		return 0;
	}
}

// RECALCULAR ALTURAS Y UTILIZAR FUNCIONES!!!

int avltree::AVL_RotateLL(struct st_node *BreakerNode){
	/* Breaker node is the upper node of the rotation nodes affected (BreakerNode = z)
	 * This section will be full of ifs to avoid segmentation fault problems

	T1, T2, T3 and T4 are subtrees.
	         z                                       y
	        / \                                    /   \
 	       y  T4      Right Rotate (z)            x     z
	      / \          - - - - - - - - ->        / \   / \
	     x  T3                                  T1 T2 T3 T4
	    / \
	   T1 T2
	 */

	// Assigning parent of z as parent of y
  //cout<<"Rotando LL por "<<BreakerNode->l_u64_key<<endl;
	if(BreakerNode->l_bsm_isroot != true){
		BreakerNode->l_u32psm_leftchild->st_parent = BreakerNode->st_parent;
    if(BreakerNode->st_parent->l_u64_key > BreakerNode->l_u64_key){
      //parent is greather than child, we are lc
      BreakerNode->st_parent->l_u32psm_leftchild = BreakerNode->l_u32psm_leftchild;
    }else{BreakerNode->st_parent->l_u32psm_rightchild = BreakerNode->l_u32psm_leftchild;}
	}else{ // z is the root node
		BreakerNode->l_u32psm_leftchild->st_parent = NULL;
		BreakerNode->l_bsm_isroot = false;
		BreakerNode->l_u32psm_leftchild->l_bsm_isroot = true;
    l_pcmRootNode = BreakerNode->l_u32psm_leftchild;
	}

	// Assigning y as the new parent of z
	BreakerNode->st_parent = BreakerNode->l_u32psm_leftchild;

	// Assigning T3 as the left child of z
	if(BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild != NULL){
    l_pcmAuxNode2 = BreakerNode->l_u32psm_leftchild;
		BreakerNode->l_u32psm_leftchild = BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild;
    // Assigning z as the right child of y
  	l_pcmAuxNode2->l_u32psm_rightchild = BreakerNode;
	}else{
    // Assigning z as the right child of y
  	BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild = BreakerNode;
    BreakerNode->l_u32psm_leftchild = NULL;
  }

  //if(BreakerNode->st_parent->l_u32psm_leftchild != NULL){
    //cout<<"en LL: lc de "<<BreakerNode->st_parent->l_u64_key<<" es "<<BreakerNode->st_parent->l_u32psm_leftchild->l_u64_key<<endl;
  //}
  //if(BreakerNode->st_parent->l_u32psm_rightchild != NULL){
    //cout<<"en LL: rc de "<<BreakerNode->st_parent->l_u64_key<<" es "<<BreakerNode->st_parent->l_u32psm_rightchild->l_u64_key<<endl;
  //}

	return 0;
}





int avltree::AVL_RotateRR(struct st_node *BreakerNode){
	/* Breaker node is the upper node of the rotation nodes affected (BreakerNode = z)
	 * This section will be full of ifs to avoid segmentation fault problems

	T1, T2, T3 and T4 are subtrees.
	  z                                y
	 / \                             /   \
	T1  y      Left Rotate(z)       z     x
	   / \     - - - - - - - ->    / \   / \
	  T2  x                       T1 T2 T3 T4
	     / \
	    T3 T4
	 */

	// Assigning parent of y the parent of z
  //cout<<"Rotando RR por "<<BreakerNode->l_u64_key<<endl;
	if(BreakerNode->st_parent != NULL){
		BreakerNode->l_u32psm_rightchild->st_parent = BreakerNode->st_parent;
    if(BreakerNode->st_parent->l_u64_key > BreakerNode->l_u64_key){
      //parent is greather than child, we are lc
      BreakerNode->st_parent->l_u32psm_leftchild = BreakerNode->l_u32psm_rightchild;
    }else{
      BreakerNode->st_parent->l_u32psm_rightchild = BreakerNode->l_u32psm_rightchild;
    }
	}else{ // BreakerNode is the root
		BreakerNode->l_u32psm_rightchild->st_parent = NULL;
		BreakerNode->l_bsm_isroot = false;
		BreakerNode->l_u32psm_rightchild->l_bsm_isroot = true;
    l_pcmRootNode = BreakerNode->l_u32psm_rightchild;
	}

	// Assigning y as the new parent of z
	BreakerNode->st_parent = BreakerNode->l_u32psm_rightchild;

	// Assigning T2 as the right child of z
	if(BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild != NULL){
    l_pcmAuxNode1 = BreakerNode->l_u32psm_rightchild;
		BreakerNode->l_u32psm_rightchild = BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild;
    // Assigning z as the left child of y
  	l_pcmAuxNode1->l_u32psm_leftchild = BreakerNode;
	}else{
    // Assigning z as the right child of y
  	BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild = BreakerNode;
    BreakerNode->l_u32psm_rightchild = NULL;
  }

  // Update height of the nodes (just breakernode and its parents)
  //AVL_CalcHeight(LastNodeIns);
  //if(BreakerNode->st_parent->l_u32psm_leftchild != NULL){
    //cout<<"en RR: lc de "<<BreakerNode->st_parent->l_u64_key<<" es "<<BreakerNode->st_parent->l_u32psm_leftchild->l_u64_key<<endl;
  //}
  //if(BreakerNode->st_parent->l_u32psm_rightchild != NULL){
    //cout<<"en RR: rc de "<<BreakerNode->st_parent->l_u64_key<<" es "<<BreakerNode->st_parent->l_u32psm_rightchild->l_u64_key<<endl;
  //}
	return 0;
}



int avltree::AVL_RotateLR(struct st_node *BreakerNode){
	/* Breaker node is the upper node of the rotation nodes affected (BreakerNode = z)
	 * This section will be full of ifs to avoid segmentation fault problems

	     z                              z                            x
	    / \                            / \                         /   \
	   y  T4   Left Rotate (y)        x  T4    Right Rotate(z)    y     z
	  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \   / \
	 T1  x                          y   T3                      T1 T2 T3 T4
	    / \                        / \
	   T2 T3                      T1 T2
	 */
  //cout<<"Rotando LR por "<<BreakerNode->l_u64_key<<endl;
  AVL_RotateRR(BreakerNode->l_u32psm_leftchild);      // Left rotate for y
	AVL_RotateLL(BreakerNode);                          // Right rotate for z
  // Update height of the nodes (just breakernode and its parents)
  //AVL_CalcHeight(LastNodeIns);
	return 0;
}




int avltree::AVL_RotateRL(struct st_node *BreakerNode){
	/* Breaker node is the upper node of the rotation nodes affected (BreakerNode = z)
	 * This section will be full of ifs to avoid segmentation fault problems

	   z                            z                             x
	  / \                          / \                          /   \
	 T1  y   Right Rotate (y)     T1  x      Left Rotate(z)    z     y
	    / \  - - - - - - - - ->      / \   - - - - - - - ->   / \   / \
	   x  T4                        T2  y                    T1 T2 T3 T4
	  / \                              / \
	 T2 T3                            T3 T4

	 */
//  cout<<"Rotando RL por "<<BreakerNode->l_u64_key<<endl;
  AVL_RotateLL(BreakerNode->l_u32psm_rightchild);
	AVL_RotateRR(BreakerNode);
  // Update height of the nodes (just breakernode and its parents)
  //AVL_CalcHeight(LastNodeIns);
	return 0;
}




int32_t avltree::AVL_DetRotType(struct st_node *BreakerNode){
  if( k >= 2 ){// left branch is taller than right branch
    if(BreakerNode->l_u32psm_leftchild->l_u32psm_leftchild != NULL && BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild != NULL){
        // Can be LL or LR
        if(BreakerNode->l_u32psm_leftchild->l_u32psm_leftchild->l_ssm_height > BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild->l_ssm_height){
          //LL case
          //cout<<"LL rotation needed due to "<<BreakerNode->l_u64_key<<endl;
          AVL_RotateLL(BreakerNode);
          return 1;
        }else{
          // LR case
          //cout<<"LR rotation needed due to "<<BreakerNode->l_u64_key<<endl;
          AVL_RotateLR(BreakerNode);
          return 2;
        }
    }

    if(BreakerNode->l_u32psm_leftchild->l_u32psm_leftchild == NULL && BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild != NULL){
        // Can be just LR
        //cout<<"LR rotation needed due to "<<BreakerNode->l_u64_key<<endl;
        AVL_RotateLR(BreakerNode);
        return 2;
    }

    if(BreakerNode->l_u32psm_leftchild->l_u32psm_leftchild != NULL && BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild == NULL){
        // Can be just LL
        //cout<<"LL rotation needed due to "<<BreakerNode->l_u64_key<<endl;
        AVL_RotateLL(BreakerNode);
        return 1;
    }

  }

  if( k <= -2 ){ // Right branch is taller than right branch
    if(BreakerNode->l_u32psm_rightchild->l_u32psm_rightchild != NULL && BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild != NULL){
        // Can be RR or RL
        if(BreakerNode->l_u32psm_rightchild->l_u32psm_rightchild->l_ssm_height > BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild->l_ssm_height){
          //RR case
          //cout<<"RR rotation needed due to "<<BreakerNode->l_u64_key<<endl;
          AVL_RotateRR(BreakerNode);
          return 3;
        }else{
          // RL case
          //cout<<"RL rotation needed due to "<<BreakerNode->l_u64_key<<endl;
          AVL_RotateRL(BreakerNode);
          return 4;
        }
    }

    if(BreakerNode->l_u32psm_rightchild->l_u32psm_rightchild == NULL && BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild != NULL){
      // Can be just RL cause rr child is null
      //cout<<"RL rotation needed due to "<<BreakerNode->l_u64_key<<endl;
      AVL_RotateRL(BreakerNode);
      return 4;
    }

    if(BreakerNode->l_u32psm_rightchild->l_u32psm_rightchild != NULL && BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild == NULL){
      // Can be just RR cause rl child is null
      //cout<<"RR rotation needed due to "<<BreakerNode->l_u64_key<<endl;
      AVL_RotateRR(BreakerNode);
      return 3;
    }

  }
  return 0;

}



// Function to calculate the height of the parental ancestry of the last node inserted
int32_t avltree::AVL_CalcHeight(struct st_node *NodeChecked){

	//This is the root, no more recursivity -> GO OUT
	if (NodeChecked->l_bsm_isroot == true){
		return 0;
	}else{

	l_pcmNewNode = NodeChecked->st_parent; // Assign to l_pcmNewNode the parent of the node checked

  // Calculate height of NodeChecked prior to l_pcmNewNode
  if(NodeChecked->l_u32psm_leftchild == NULL && NodeChecked->l_u32psm_rightchild == NULL){
    NodeChecked->l_ssm_height = 1;
	}
  if(NodeChecked->l_u32psm_leftchild != NULL && NodeChecked->l_u32psm_rightchild == NULL){
    NodeChecked->l_ssm_height = NodeChecked->l_u32psm_leftchild->l_ssm_height + 1;
	}
  if(NodeChecked->l_u32psm_leftchild == NULL && NodeChecked->l_u32psm_rightchild != NULL){
    NodeChecked->l_ssm_height = NodeChecked->l_u32psm_rightchild->l_ssm_height + 1;
	}
  if(NodeChecked->l_u32psm_leftchild != NULL && NodeChecked->l_u32psm_rightchild != NULL){
    l_pcmAuxNode1 = NodeChecked->l_u32psm_leftchild;
		l_pcmAuxNode2 = NodeChecked->l_u32psm_rightchild;
    if(l_pcmAuxNode1->l_ssm_height >= l_pcmAuxNode2->l_ssm_height){
			NodeChecked->l_ssm_height = l_pcmAuxNode1->l_ssm_height + 1;
		}else{NodeChecked->l_ssm_height = l_pcmAuxNode2->l_ssm_height + 1;}
	}

	// Updating the height of the parent of Node Checked

  // Easy cases where there is just one child
	if(l_pcmNewNode->l_u32psm_leftchild == NULL || l_pcmNewNode->l_u32psm_rightchild == NULL){
		l_pcmNewNode->l_ssm_height = NodeChecked->l_ssm_height + 1;
	}

	// Complex cases where there is left and right children
	if(l_pcmNewNode->l_u32psm_leftchild != NULL && l_pcmNewNode->l_u32psm_rightchild != NULL){
		l_pcmAuxNode1 = l_pcmNewNode->l_u32psm_leftchild;
		l_pcmAuxNode2 = l_pcmNewNode->l_u32psm_rightchild;

		/* Check if the height of the left child is higher or equal to the height of
		 * the right child, if so, replace the its height with the height of the lc+1
		 * otherwhise it will be replaced with rc+1
 		 */
		if(l_pcmAuxNode1->l_ssm_height >= l_pcmAuxNode2->l_ssm_height){
			l_pcmNewNode->l_ssm_height = l_pcmAuxNode1->l_ssm_height + 1;
		}else{l_pcmNewNode->l_ssm_height = l_pcmAuxNode2->l_ssm_height + 1;}
	}

	// Calculate the k = lc_height - rc_height
	k = l_u32cmK_Rupture(l_pcmNewNode);
  // Determines the kind of rotation to execute and executes it
  int32_t aux = AVL_DetRotType(l_pcmNewNode);
  //cout<<"root es "<<l_pcmRootNode->l_u64_key<<endl;
  //if(l_pcmRootNode->l_u32psm_leftchild != NULL){cout<<"lc del root es "<<l_pcmRootNode->l_u32psm_leftchild->l_u64_key<<endl;}
  //if(l_pcmRootNode->l_u32psm_rightchild != NULL){cout<<"rc del root es "<<l_pcmRootNode->l_u32psm_rightchild->l_u64_key<<endl;}
  if(aux == 2 || aux == 4){
    //cout<<"caso no LL ni RR"<<endl;
    //cout<<"l_pcmNewNode es "<<l_pcmNewNode->l_u64_key<<endl;
    /* rotation was LR or RL and the height calc is different cause
     * last node inserted is parent of its parents before rotation
     */

     // l_pcmNewNode could be the rc or lc of Last Node Inserted, but this doesn´t matter
     // cause anyway will be one of the childs of Last Node Inserted

     // Case where both childs are NULL
     if(l_pcmNewNode->l_u32psm_leftchild == NULL && l_pcmNewNode->l_u32psm_rightchild == NULL){
       l_pcmNewNode->l_ssm_height = 1;
     }

     // Easy cases where there is just one child
   	if(l_pcmNewNode->l_u32psm_leftchild != NULL && l_pcmNewNode->l_u32psm_rightchild == NULL){
   		l_pcmNewNode->l_ssm_height = l_pcmNewNode->l_u32psm_leftchild->l_ssm_height + 1;
   	}
    if(l_pcmNewNode->l_u32psm_leftchild == NULL && l_pcmNewNode->l_u32psm_rightchild != NULL){
   		l_pcmNewNode->l_ssm_height = l_pcmNewNode->l_u32psm_rightchild->l_ssm_height + 1;
   	}

   	// Complex cases where there is left and right children
   	if(l_pcmNewNode->l_u32psm_leftchild != NULL && l_pcmNewNode->l_u32psm_rightchild != NULL){
   		l_pcmAuxNode1 = l_pcmNewNode->l_u32psm_leftchild;
   		l_pcmAuxNode2 = l_pcmNewNode->l_u32psm_rightchild;

   		/* Check if the height of the left child is higher or equal to the height of
   		 * the right child, if so, replace the its height with the height of the lc+1
   		 * otherwhise it will be replaced with rc+1
    		 */
   		if(l_pcmAuxNode1->l_ssm_height >= l_pcmAuxNode2->l_ssm_height){
   			l_pcmNewNode->l_ssm_height = l_pcmAuxNode1->l_ssm_height + 1;
   		}else{l_pcmNewNode->l_ssm_height = l_pcmAuxNode2->l_ssm_height + 1;}
   	}


      if(l_pcmNewNode->st_parent->l_u32psm_leftchild == l_pcmNewNode){
      // We need to analyze the right child
      l_pcmAuxNode3 = l_pcmNewNode->st_parent->l_u32psm_rightchild;

      // Case where both childs are NULL
      if(l_pcmAuxNode3->l_u32psm_leftchild == NULL && l_pcmAuxNode3->l_u32psm_rightchild == NULL){
        l_pcmAuxNode3->l_ssm_height = 1;
      }

      if(l_pcmAuxNode3->l_u32psm_leftchild != NULL && l_pcmAuxNode3->l_u32psm_rightchild == NULL){
     		l_pcmAuxNode3->l_ssm_height = l_pcmAuxNode3->l_u32psm_leftchild->l_ssm_height + 1;
     	}
      if(l_pcmAuxNode3->l_u32psm_leftchild == NULL && l_pcmAuxNode3->l_u32psm_rightchild != NULL){
     		l_pcmAuxNode3->l_ssm_height = l_pcmAuxNode3->l_u32psm_rightchild->l_ssm_height + 1;
     	}

     	// Complex cases where there is left and right children
     	if(l_pcmAuxNode3->l_u32psm_leftchild != NULL && l_pcmAuxNode3->l_u32psm_rightchild != NULL){
        l_pcmAuxNode2 = l_pcmAuxNode3->l_u32psm_rightchild;
     		l_pcmAuxNode1 = l_pcmAuxNode3->l_u32psm_leftchild;

     		/* Check if the height of the left child is higher or equal to the height of
     		 * the right child, if so, replace the its height with the height of the lc+1
     		 * otherwhise it will be replaced with rc+1
      		 */
     		if(l_pcmAuxNode1->l_ssm_height >= l_pcmAuxNode2->l_ssm_height){
     			l_pcmAuxNode3->l_ssm_height = l_pcmAuxNode1->l_ssm_height + 1;
     		}else{l_pcmAuxNode3->l_ssm_height = l_pcmAuxNode2->l_ssm_height + 1;}
     	}
    }else{
      // We need to analyze the left child
      l_pcmAuxNode3 = l_pcmNewNode->st_parent->l_u32psm_leftchild;

      // Case where both childs are NULL
      if(l_pcmAuxNode3->l_u32psm_leftchild == NULL && l_pcmAuxNode3->l_u32psm_rightchild == NULL){
        l_pcmAuxNode3->l_ssm_height = 1;
      }

      if(l_pcmAuxNode3->l_u32psm_leftchild != NULL && l_pcmAuxNode3->l_u32psm_rightchild == NULL){
     		l_pcmAuxNode3->l_ssm_height = l_pcmAuxNode3->l_u32psm_leftchild->l_ssm_height + 1;
     	}
      if(l_pcmAuxNode3->l_u32psm_leftchild == NULL && l_pcmAuxNode3->l_u32psm_rightchild != NULL){
     		l_pcmAuxNode3->l_ssm_height = l_pcmAuxNode3->l_u32psm_rightchild->l_ssm_height + 1;
     	}

     	// Complex cases where there is left and right children
     	if(l_pcmAuxNode3->l_u32psm_leftchild != NULL && l_pcmAuxNode3->l_u32psm_rightchild != NULL){
        l_pcmAuxNode2 = l_pcmAuxNode3->l_u32psm_rightchild;
     		l_pcmAuxNode1 = l_pcmAuxNode3->l_u32psm_leftchild;

     		/* Check if the height of the left child is higher or equal to the height of
     		 * the right child, if so, replace the its height with the height of the lc+1
     		 * otherwhise it will be replaced with rc+1
      		 */
     		if(l_pcmAuxNode1->l_ssm_height >= l_pcmAuxNode2->l_ssm_height){
     			l_pcmAuxNode3->l_ssm_height = l_pcmAuxNode1->l_ssm_height + 1;
     		}else{l_pcmAuxNode3->l_ssm_height = l_pcmAuxNode2->l_ssm_height + 1;}
     	}
    }
  }
  //cout<<"altura de "<<l_pcmNewNode->l_u64_key<<" es "<<l_pcmNewNode->l_ssm_height<<endl;
  //if(l_pcmNewNode->l_u32psm_leftchild != NULL){
    //cout<<"lc de "<<l_pcmNewNode->l_u64_key<<" es "<<l_pcmNewNode->l_u32psm_leftchild->l_u64_key;
    //cout<<" y su h es "<<l_pcmNewNode->l_u32psm_leftchild->l_ssm_height<<endl;
  //}
  //if(l_pcmNewNode->l_u32psm_rightchild != NULL){
    ////cout<<"rc de "<<l_pcmNewNode->l_u64_key<<" es "<<l_pcmNewNode->l_u32psm_rightchild->l_u64_key;
    //cout<<" y su h es "<<l_pcmNewNode->l_u32psm_rightchild->l_ssm_height<<endl;
//  }
	// Here I have to evaluate if is necessary to rotate due to |k|>=2
	// Recursive function to re-calculate the heights of all its parental ancestry
  AVL_CalcHeight(l_pcmNewNode);
  }
}


struct st_node* avltree::AVL_Search(struct st_node *ActualNode, uint64_t u64SearchedNode){
  if(u64SearchedNode > ActualNode->l_u64_key){
    if(ActualNode->l_u32psm_rightchild != NULL){
      AVL_Search(ActualNode->l_u32psm_rightchild, u64SearchedNode);
    }else{
      cout<<"The person does not exist in our database."<<endl;
      return ActualNode;
    }
  }
  if(u64SearchedNode < ActualNode->l_u64_key){
    if(ActualNode->l_u32psm_leftchild != NULL){
      AVL_Search(ActualNode->l_u32psm_leftchild, u64SearchedNode);
    }else{
      cout<<"The person does not exist in our database.\n"<<endl;
      return ActualNode;
    }
  }
  if(u64SearchedNode == ActualNode->l_u64_key){
    cout<<"Your person is "<<ActualNode->l_ssm_Name<<", with ID "<<ActualNode->l_u64_key<<"\n"<<endl;
    return ActualNode;
  }
  if(u64SearchedNode < ActualNode->l_u64_key && ActualNode->l_u32psm_leftchild == NULL){
    cout<<"The person does not exist in our database.\n"<<endl;
    return ActualNode;
  }
  if(u64SearchedNode > ActualNode->l_u64_key && ActualNode->l_u32psm_rightchild == NULL){
    cout<<"The person does not exist in our database.\n"<<endl;
    return ActualNode;
  }
}
