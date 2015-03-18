#ifndef SLIDING_PUZZLE_H
#define SLIDING_PUZZLE_H
#include <vector>
#include <list>
#include "node.h"

namespace Yekun {

class Sliding_Puzzle
{
public:

    Sliding_Puzzle(string initial)  : puzzle(initial)
    { 
    }
    
    void play(); 
    Node getSolution();

private:
    bool complete();
    Node puzzle;   
    list<Node> status_list;
};

//check if the puzzle is completed
bool Sliding_Puzzle::complete(){
    Node next_status=status_list.back();
    if (next_status.data=="123456780"){
        return true;
    }else{
        return false;
    }
}

Node Sliding_Puzzle::getSolution()
{
    status_list.push_back(puzzle);
    while(!complete()){
        Node next_up=status_list.front();
        string s1=next_up.data;
        next_up.up();
        //store the up move only if it's valid move
        if(s1!=next_up.data){
            status_list.push_back(next_up);
            //check if the puzzle is completed
            complete();
        }
        Node next_down=status_list.front();
        string s2=next_down.data;
        next_down.down();
        //store the down move only if it's valid move
        if(s2!=next_down.data){
            status_list.push_back(next_down);
            //check if the puzzle is completed
            complete();
        }
        Node next_left=status_list.front();
        string s3=next_left.data;
        next_left.left();
        //store the left move only if it's valid move
        if(s3!=next_left.data){
            status_list.push_back(next_left);
            //check if the puzzle is completed
            complete();
        }
        Node next_right=status_list.front();
        string s4=next_right.data;
        next_right.right();
        //store the right move only if it's valid move
        if(s4!=next_right.data){
            status_list.push_back(next_right);
            //check if the puzzle is completed
            complete();
        }
        status_list.pop_front();
    }
    return status_list.back();
}

//use the std list to store the game tree
//invalid move will not be stored (that branch of subtree will not be continued)
void Sliding_Puzzle::play(){

    Node final = getSolution();

    //output the result
    cout << "The puzzle     is " << puzzle.data << " has been solved!" << endl;
    cout << "The play order is " << final.order << endl;
    cout << "The total step is " << final.step  << endl;
}

}
#endif // SLIDING_PUZZLE_H
