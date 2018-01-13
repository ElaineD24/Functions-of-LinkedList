
/*
File name is linked_list.c
 Purpose: file contains functions for manipulating singly linked list

 Created By
 Doron Nussbaum 2016

 Modifications:
 November 2017 - minor modifications


 Copyright 2017

 */

/******************************************************************/
// INCLUDE

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list.h"


/************************************************************************/
// Define



/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
id - id of person
firstName - first name of person
familyName - family name of person

input/output
head - head of linked list

return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/

PersonalInfo *insertToList(PersonalInfo **head, unsigned int id,
        char *firstName, char *familyName)
{

    PersonalInfo *p = NULL;
    // allocate memory
    p = (PersonalInfo*) malloc(sizeof(PersonalInfo));
    // set the data
    p->id = id;
    strcpy(p->firstName, firstName);
    strcpy(p->familyName, familyName);
    // make new node point to first node of list
    p->next = *head;
    // update the head
    *head = p;
    return p;

}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node

Input
node - the node after which the new node must be added to the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/


PersonalInfo *insertAfter(PersonalInfo *node, unsigned int id, char *firstName, char *familyName)
{
  PersonalInfo *p = NULL;
  // allocate memory
  p = (PersonalInfo*) malloc(sizeof(PersonalInfo));
  // set the data
  p->id = id;
  strcpy(p->firstName, firstName);
  strcpy(p->familyName,familyName);
  // make new node p point to node after "node"
  p->next = node->next;
  node->next = p;
  return p;


}

/************************************************************************/
/*
Purpose: create a new node and insert it into the end of the list
Input
head - the head of the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/


PersonalInfo *insertLast(PersonalInfo **head, unsigned int id, char *firstName, char *familyName)
{

  if(*head == NULL){
    return insertToList(head, id, firstName, familyName);
  }else{
    PersonalInfo *current = *head;
    // points to the next one in the list until we reach the last one
    while (current->next !=NULL) {
      current = current->next;
    }
    // add a new variable
    PersonalInfo *newLastNode = NULL;
    // allocate memory
    newLastNode = (PersonalInfo*) malloc(sizeof(PersonalInfo));
	// make the newLastNode point to node after the original last one
    current->next = newLastNode;
	// set the data
    newLastNode->id = id;
    strcpy(newLastNode->firstName, firstName);
    strcpy(newLastNode->familyName, familyName);
    newLastNode->next = NULL;
    return newLastNode;
  }
}


/************************************************************************/
/*
Purpose: search for the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


PersonalInfo *searchByName(PersonalInfo *head, char *firstName)
{
  PersonalInfo *current = head;
  // do the while-loop to compare with every firstName in the list until the person has been found
  while (current != NULL){
    if(strcmp(current->firstName, firstName)==0){
      return current;
    }else{
      // if the firstName is not the same, points to the next one
      current = current->next;
    }
  }
  return NULL;
}

/************************************************************************/
/*
Purpose: search for the first node with the matching id
Input
head - the head of the list
id - id of person person

return
a pointer to the node that was allocated.

NULL - if no node was found or list empty

*/


PersonalInfo *searchById(PersonalInfo *head, unsigned int id)
{
  PersonalInfo *current = head;
  // do the while-loop to compare with every id in the list until the person has been found
  while (current != NULL){
    if(current->id == id){
      return current;
    }else{
      // if the id is not the same, points to the next one
      current = current->next;
    }
  }
  return NULL;
}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteFromList(PersonalInfo **head, unsigned int *id,
	char *firstName, char *familyName)

{
    // check if the list is empty
    if (*head == NULL){
        return 1;
    }
    // keep a handle to the node to be deleted (the first one)
    PersonalInfo *handleDeleteNode = *head;
    PersonalInfo *nextNode = (*head)->next;
    // set the data
    *id = handleDeleteNode->id;
    strcpy(firstName, handleDeleteNode->firstName);
    strcpy(familyName, handleDeleteNode->familyName);  
    // update the head: set the head to the node after handleDeleteNode
    *head = nextNode;
    // free the memory of the original head
    free(handleDeleteNode);
	handleDeleteNode = NULL;
    return 0;

}


/***************************************************************/

/*
Purpose: delete the last node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteLast(PersonalInfo **head, unsigned int *id,
                char *firstName, char *familyName)

{
    if((*head) == NULL){
      return 1;
    }else if((*head)->next == NULL){ // if there is only one item in the list
      // call deleteFromList function to remove it
        deleteFromList(head, id,firstName, familyName);
        return 0;
    }
    PersonalInfo *current = *head;
    PersonalInfo *back = NULL;
    // points to the next item until current points to the last item of the list
    while (current->next != NULL){
        back = current;
      current = current->next;
    }
    // set the data
    *id = current->id;
    strcpy(firstName, current ->firstName);
    strcpy(familyName, current->familyName);
    back->next = current->next;
    // free the memory of current->next
    free(current);
	current = NULL;
    return 0;

}



/************************************************************************/

/*
Purpose: delete the record after the given node
Input
node - a node in the list

output
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0 if node was deleted
1 if node was not deleted (either input node is NULL or input node was the lastnode in the list)

*/



int deleteAfter(PersonalInfo *node, unsigned int *id,
                char *firstName, char *familyName)

{
    if (node == NULL){
      return 1;
    }
    if (node->next == NULL){
        return 1;
    }
      //  keep a handle to the node to be deleted (node->next)
      PersonalInfo *handleDeleteNode = node->next;
    // set the data
      *id = handleDeleteNode->id;
      strcpy(firstName, handleDeleteNode ->firstName);
      strcpy(familyName, handleDeleteNode->familyName);
    // update node
        node->next = handleDeleteNode->next;
    // free the memory of the node after "node"
      free(handleDeleteNode);
	handleDeleteNode = NULL;

      return 0;



}

/************************************************************************/

/*
Purpose: delete the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0  if node was deleted
1 if node was not found (e.g., list is empty, no such node exists)

*/


int deleteNodeByName(PersonalInfo **head, char *firstName,
	char *familyName, unsigned int *id)
{
	// check if there is no node in the list
  if((*head)==NULL){
    return 1;
  }
  PersonalInfo *temp = NULL;
  temp = searchByName((*head), firstName);
  if(temp==NULL){
    return 1;
  }else{
    PersonalInfo *deleteTemp = *head;
    while(1){
      if(temp==deleteTemp){
        return deleteFromList(head, id, firstName, familyName);
      }else if(temp==deleteTemp->next){
  			return deleteAfter(deleteTemp,id,firstName,familyName);
  		}
	// move to the next node until it has been found
      deleteTemp = deleteTemp->next;
      }
    }	
  }

/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/


void deleteList(PersonalInfo **head)
{
  while((*head)!=NULL){
    deleteFromList(head, &((*head)->id), (*head)->firstName, (*head)->familyName);
  }
}



/************************************************************************/
/*
Purpose: prints the fields of a node
input:
node - a pointer to a given node

*/


void printNode(PersonalInfo *node)
{
	printf("%-20s %-20s %7d \n",node->firstName, node->familyName, node->id);

}


/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
*/


void printList(PersonalInfo *head)
{
	// go through every person in the list and print them
  while (head != NULL){
    printNode(head);
    head = head->next;
  }



}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list
input
head - the head of the list

return
the number of nodes in the list

*/


int listSize(PersonalInfo *head)
{

	// check if there is no node in the list
    if (head==NULL){
    return 0;
  }
	// check if there is only one node in the list
  if(head->next == NULL){
    return 1;
  }
  if(head->next != NULL){
    return 1+listSize(head->next);
  }

}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list with a matching firstName
input
head - the head of the list

return
the number of nodes in the list that match the firstName


*/


int countRecords(PersonalInfo *head, char *firstName)
{
  int count = 0;
  if (head == NULL){
    return 0;
  }
  PersonalInfo *current = head;
  // do the while-loop to compare with every firstName in the list until the person has been found
  while (current != NULL){
    if(strcmp(current->firstName, firstName)==0){
      count++;
    }
    // points to the next one until it reaches the end of the list
    current = current->next;
  }
  return count;

}




/************************************************************************/
/*

Purpose: removes all duplicates records from the list.  Duplicate records are determined by their first name.
You can assume that the listed is sorted by first name.

input
head - the head of the  list



*/




void removeDuplicates(PersonalInfo *head)
{
	// check if there is no node in the list
  if (head == NULL){
    return;
  }
	// check if there is only one node in the list
  if(head->next == NULL){
    return;
  }
	// check if the first name of the next node of head is the same as the first name of the head
  if(strcmp(head->firstName, head->next->firstName)==0){
	// delete the next node
    deleteAfter(head, &(head->id), head->firstName, head->familyName);
    return removeDuplicates(head);
  }
  if(strcmp(head->firstName, head->next->firstName)!=0){
    return removeDuplicates(head->next);
  }

}
