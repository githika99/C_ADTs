/*
Githika Annapureddy
CruzId: gannapur
pa5
*/
//-----------------------------------------------------------------------------
// Shuffle.cpp
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include <iomanip> 
#include "List.h"

using namespace std;


//Performs one shuffle opperation on D
void shuffle(List& D) {                      //This is a pass by reference, so L (not a copy of L) is passed (in C, this would be done with *D, and call it with &D)
    List A = List();
    List D1 = D;
    int final_length = D.length();
    int front = 1;                           //leave 0 when it should be 0, and 1 when it should not
    int pos = int(D.length()/2);
    //cout << "pos is: " << pos << endl;
    D1.moveFront();
    D.moveFront();
    while(D.position() < pos) {
        D.moveNext();
    }
    //cout << "cursor of D is in pos now: " << endl;

    //cout << "round: " << A.length() <<  "A is: " << A << endl;
    while(A.length() < final_length) {                     //change condition
        if (front == 1 && D.position() < D.length()) {
            ListElement n2 = D.peekNext();
            A.insertBefore(n2);                 //add to A
            //cout << n2 << " added to A" << endl;
            D.eraseAfter();
            front = 0;
        } else if (front == 0 && A.length() < final_length) {
            ListElement n1 = D1.peekNext();
            A.insertBefore(n1);                 //add to A
            //cout << n1 << " added to A" << endl;
            D1.eraseAfter();
            front = 1;
        }
    }
    D = A;
}


int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Error: Calling Shuffle.cpp without exactly 1 arguments for size of deck");
        exit(EXIT_FAILURE);
    }
    char* end;

    int deck_size = strtol(argv[1], &end, 10);
    int num_shuffles[deck_size];

    // List L = List();
    // for(int i = 1; i<=8;i++){
    //     L.insertBefore(i);
    // }     
    // List OG = L;

    // int count = 1;
    // shuffle(L);                             //call shuffle with L
    // cout << "OG is: " << OG << endl;
    // cout << "L is: " << L << endl;
    // while((! L.equals(OG))) {                 //while L != OG
    //     cout << "not yet equal" << endl;
    //     cout << "L is: " << L << endl;
    //     shuffle(L);
    //     count++;
    // }
    // cout << "count is: " << count << endl;

    List L = List();
    List OG = List();                   //original list 
    for(int i = 1; i<=deck_size;i++){
        //cout << endl << endl << endl;
        OG.insertBefore(i);
        L.insertBefore(i);
        int count = 1;
        shuffle(L);                             //call shuffle with L
        //cout << "OG is: " << OG << endl;
        //cout << "L is: " << L << endl;
        //cout << "L == OG: " << L.equals(OG) << endl;
        while((! L.equals(OG))) {                 //while L != OG
            //cout << "not yet equal" << endl;
            //cout << "L is: " << L << endl;
            shuffle(L);
            count++;
        }
        num_shuffles[i] = count;
        //cout << "i: " << i << " count: " << count << endl;
    }

    // print to stdout
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    for(int i = 1; i<=deck_size;i++){
        //17 spaces between first num and second
        cout <<  i << setw(17) << num_shuffles[i] << endl;
    }

    return(EXIT_SUCCESS);
}


/*
When tested individually:
3   2
8   6
9   6
10  10*/