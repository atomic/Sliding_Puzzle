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
    void heuristic_play();
    Node getSolution();
    Node getHeuristicSolution();

private:
    void find_hpath(Node status);
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

/**
 * @brief Wrap the logic and generator for heuristicSolution
 */
Node Sliding_Puzzle::getHeuristicSolution()
{
    status_list.push_back(puzzle);
    while(!complete()){
        find_hpath(status_list.front());
        status_list.pop_front();
    }
    return status_list.back();
}


/**
 * @brief Function to find the metric distance 
    check if it's a valid move
    and add the valid moves to a vector for later heuristic value calculation

 * @param Node
 */
void Sliding_Puzzle::find_hpath(Node status)
{
    vector<Node> test_vector;
    Node status_up=status;
    status_up.up();
    if (status_up.data != status.data){
        test_vector.push_back(status_up);
    }

    Node status_down=status;
    status_down.down();
    if (status_down.data != status.data){
        test_vector.push_back(status_down);
    }

    Node status_left=status;
    status_left.left();
    if (status_left.data != status.data){
        test_vector.push_back(status_left);
    }

    Node status_right=status;
    status_right.right();
    if (status_right.data != status.data){
        test_vector.push_back(status_right);
    }

    //find minimum heuristic value
    Node test=test_vector[0];
    int min_hvalue=test.find_hvalue();
    for (unsigned int i=1; i<test_vector.size(); i++){
        test=test_vector[i];
        if (min_hvalue>test.find_hvalue()){
            min_hvalue=test.find_hvalue();
        }
    }

    //add the status node that has the minimum heuristic value to the status list
    //and check if it's complete status
    for (unsigned int i=0; i<test_vector.size(); i++){
        Node valid=test_vector[i];
        if (valid.find_hvalue()==min_hvalue){
            status_list.push_back(valid);
            complete();
        }
    }
}

/**
 * @brief Function to generate solution for a puzzle without heuristic
 *  use the std list to store the game tree
 *  invalid move will not be stored (that branch of subtree will not be continued)
 * @param what
 * @return none
 */
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
        }
        complete();

        Node next_down=status_list.front();
        string s2=next_down.data;
        next_down.down();
        //store the down move only if it's valid move
        if(s2!=next_down.data){
            status_list.push_back(next_down);
            //check if the puzzle is completed
        }
        complete();

        Node next_left=status_list.front();
        string s3=next_left.data;
        next_left.left();
        //store the left move only if it's valid move
        if(s3!=next_left.data){
            status_list.push_back(next_left);
            //check if the puzzle is completed
        }
        complete();

        Node next_right=status_list.front();
        string s4=next_right.data;
        next_right.right();
        //store the right move only if it's valid move
        if(s4!=next_right.data){
            status_list.push_back(next_right);
            //check if the puzzle is completed
        }
        complete();
        status_list.pop_front();
    }
    return status_list.back();
}

/* @bried Demonstrate normal play function */
void Sliding_Puzzle::play(){
    Node final = getSolution();
    //output the result
    cout << "The puzzle     is " << puzzle.data << " has been solved!" << endl;
    cout << "The play order is " << final.order << endl;
    cout << "The total step is " << final.step  << endl;
    status_list.clear();
}

/**
 * @brief Display function that demonstrate and test puzzle's logic
 */
void Sliding_Puzzle::heuristic_play(){
    Node final = getHeuristicSolution();
    //output the result
    cout<<"The puzzle "<<puzzle.data<<" has been solved in heuristic method!"<<endl;
    cout<<"The play order is "<<final.order<<endl;
    cout<<"The total step is "<<final.step<<endl;

    status_list.clear();
}
}
#endif // SLIDING_PUZZLE_H
