/*
 * Author: Kevin Trejos
 *
 */

#ifndef AVL
#define AVL

#include <iostream>
#include <string>
#include <stdint.h>
#include "avltree_ObtainData.hpp"

class avltree{
	public:
		avltree();
		int AVL_Insert(struct st_node *ActualNode, struct st_node *InsertedNode);    // Inserts checking balance
		struct st_node *l_pcmRootNode = NULL;                              // It will point to the root of the AVL
		struct st_node *AVL_Search(struct st_node *ActualNode, uint64_t u64SearchedNode);
		int AVL_NodesAmount();
		int32_t iNodesAmount = 0;

	private:
		// AUX nodes
		struct st_node *l_pcmNewNode = NULL;                               // Temporary saver of parent node
		struct st_node *l_pcmAuxNode1 = NULL;
		struct st_node *l_pcmAuxNode2 = NULL;

		// Rotation functions
		int AVL_RotateLL(struct st_node *BreakerNode);                     // Rotates if case is LL
		int AVL_RotateRR(struct st_node *BreakerNode);                     // Rotates if case is RR
		int AVL_RotateLR(struct st_node *BreakerNode);                     // Rotates if case is LR
		int AVL_RotateRL(struct st_node *BreakerNode);                     // Rotates if case is RL

		// Auxiliary functions
		int32_t AVL_DetRotType(struct st_node *BreakerNode);               // Determines the kind of rotation needed
		int32_t AVL_CalcHeight(struct st_node *NodeChecked);
		int32_t l_u32cmK_Rupture(struct st_node *LastNodeInserted);        // This variable will check the first K rupture (K>=2)
};



/*AVL::AVL(void){
	// Do nothing, just declare it, the magic comes later
}*/

#endif
