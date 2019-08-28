#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int inputStringFromUser( char prompt[], char s[], int arraySize );//
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;//
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;//
void printMusicLibraryTitle( void ) ;//

typedef struct node {
    char *artist ;
    char *songName ;
    char *genre ;
    struct node *nextNode ;
} Node; //can also use type def. 


Node *newNode(char *songName, char *artist, char *genre, Node *nextNode, int length1, int length2, int length3) 
{
    Node *np = (Node *)malloc(sizeof(Node));
    //Need for dynamic allocation - pointer needs some memory space to point to. Array is a collection of memory.
    np -> songName = (char *)malloc((length1 + 1)*sizeof(char));
    np -> artist = (char *)malloc((length2 + 1)*sizeof(char));
    np -> genre = (char *)malloc((length3 + 1)*sizeof(char));
    
    if(np == NULL);
    //Need for copy - as its empty
    strcpy(np -> artist, artist);
    strcpy(np -> songName, songName);
    strcpy(np -> genre, genre);
    np -> nextNode = nextNode;
    return np; 
}


void printList(Node*head)
{
    Node *np = head;
    if(np == NULL)
    {
        printMusicLibraryEmpty();
    }
    else
    {
       while(np != NULL)
       {
          printf("%s\n", np -> songName);
          printf("%s\n", np -> artist);
          printf("%s\n", np -> genre);
          np = np -> nextNode;
       }
    }
}


Node *search(char *searchSong, Node *head)
{
    Node *temp = head;
    while(temp != NULL && strcmp(searchSong, temp -> songName) != 0) 
    {  //song is greater than what head stores. 
       temp = temp -> nextNode;
    }
    return temp; //return NULL if they are not same or else returns the node containing that particular song.
}

Node *deleteSong(char *songToDelete, Node *head)
{
    Node *nodeToDelete = search(songToDelete, head);
    if(nodeToDelete == NULL)
    {
        return head;
    }
    
    if(head != NULL && (strcmp(songToDelete, head -> songName)) == 0) //they are the same
    {
        head = head -> nextNode; //moves to node 2.
    }
    else 
    {
        Node* temp = head;
        while(temp != NULL && (strcmp(songToDelete, temp -> nextNode -> songName) != 0)) 
        {  
           temp = temp -> nextNode;
        }
        temp -> nextNode = temp -> nextNode -> nextNode; 
    }
       free(nodeToDelete -> songName);
       free(nodeToDelete -> artist);
       free(nodeToDelete -> genre);
       free(nodeToDelete);
       return head; //why head??
}

Node *deleteList(Node *head)
{
   while(head != NULL){
      Node *np = head;
      head = np -> nextNode;
      songNameDeleted(np -> songName);
      free(np);
   } 
   return NULL;
}

const int MAX_LENGTH = 1024;

int main( void ) {
    printf( "Personal Music Library.\n\n" ) ;
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n" );
         
    Node *head = NULL;
    char response ;
    char input[MAX_LENGTH + 1] ;
    do {
        inputStringFromUser( "\nCommand", input, MAX_LENGTH ) ;
        response = toupper( input[0] ) ; //converts lower case to upper case.
       
        if(response == 'I'){
           char *promptName = "Song name";
           char *promptArtist = "Artist";
           char *promptGenre = "Genre";
           int length1 = 0, length2 = 0, length3 = 0;
           
           //Why do we need to copy??? -> 
           length1 = inputStringFromUser(promptName, input, MAX_LENGTH);//why not &promptName
           char songName[length1 + 1];
           strcpy(songName, input); //copy input into original string. 
           
           length2 = inputStringFromUser(promptArtist, input, MAX_LENGTH);
           char artist[length2 + 1];
           strcpy(artist, input);
           
           length3 = inputStringFromUser(promptGenre, input, MAX_LENGTH);
           char genre[length3 + 1];
           strcpy(genre, input);
           
           Node *sameSong = search(songName, head);
           if(sameSong != NULL)
           {
              songNameDuplicate(songName);
           }
           else
           {
              Node *nodeToinsert  = newNode(songName, artist, genre, head, length1, length2, length3);
           
              if(head == NULL || (strcmp(songName, head -> songName) < 0)) //if (songName) < (head -> songName).
              {
                 nodeToinsert -> nextNode = head; 
                 head = nodeToinsert;
                 //Imagine A being inserted before node 1. 
                 //A's link points to node 1.
              }
              else
              {               
                 Node *temp;
                 temp = head;
                 while(temp -> nextNode != NULL && (strcmp(songName, temp -> nextNode -> songName) > 0)) //Subtracts 2 from 1
                 {
                    temp = temp -> nextNode;
                 }
                 nodeToinsert -> nextNode = temp -> nextNode;
                 temp -> nextNode = nodeToinsert;
                 //Imagine A is between node 2 and 3. 
                 //A's link is pointing to whatever node 2's link points to; which is 3.
                 //node 2's link now points to A.
              }
           
            }
        }
        else if( response == 'D' ) { //Delete Song
            int length4;
            char *prompt = "\nEnter the name of the song to be deleted";
           
            length4 = inputStringFromUser(prompt, input, MAX_LENGTH);
            head = deleteSong(input, head);
            
            songNameDeleted(input);
        }
        else if( response == 'S' ) {
            int length5;
            char *prompt = "\nEnter the name of the song to search for";
            Node *nodeToPrint = NULL;
            
            length5 = inputStringFromUser(prompt, input, MAX_LENGTH);
            nodeToPrint = search(input, head);
            
            if(nodeToPrint == NULL){
              songNameNotFound(input); 
            }
            else{
              songNameFound(input);            
              printf("%s\n", nodeToPrint -> songName);
              printf("%s\n", nodeToPrint -> artist);
              printf("%s\n", nodeToPrint -> genre);
            }
         
        }
        else if(response == 'P') {
             printMusicLibraryTitle();
             printf("\n");
             printList(head);
        }
        else if( response == 'Q' ) {
             ; 
        }
        else{
             printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ;
  
    if( response == 'Q'){
        deleteList(head);
        printMusicLibraryEmpty();
    }
    return 0 ;
}

int inputStringFromUser(char prompt[], char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0' ;
    return i;
}

void songNameDuplicate(char songName[]){
    printf( "\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

void songNameFound( char songName[] ) {
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

void songNameNotFound( char songName[] ) {
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}

void songNameDeleted(char songName[]) {
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

void printMusicLibraryEmpty(void) {
    printf( "\nThe music library is empty.\n" ) ;
}

void printMusicLibraryTitle(void) {
    printf( "\nMy Personal Music Library: \n" ) ;
    
}

