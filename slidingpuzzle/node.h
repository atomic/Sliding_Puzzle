 /* 
  * 
  * Copyright (C) 2015 Yekun Yang <dylanyang1003@gmail.com>
  *
  * Distributed under terms of the MIT license.
  */

#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

class Node
{
public:
    Node() {}
    Node(string initial){data=initial; order=""; step=0; pos=initial_zero_pos();}
    string data;        //puzzle status
    string order;       //play order for completing the puzzle
    int pos;            //position of 0 (space)
    int step;           //total steps to complete the puzzle

    int initial_zero_pos();

    void up();
    void down();
    void left();
    void right();
private:
    void swap(char& i, char& j);
};

int Node::initial_zero_pos(){
    int i=0;
    while (data[i]!='0'){
        i++;
    }
    return i;
}

void Node::up(){
    if (pos==0 || pos==1 || pos==2 || order[step-1]=='D'){
        //when 0 is at 1st row of puzzle
        //when the previous move is down
        //up move is invalid
        return;
    }else{
        swap(data[pos], data[pos-3]);   //move 0
        pos=pos-3;                      //new 0 position
        order=order+"U";                //record the order
        step++;                         //record the total step
    }
}

void Node::down(){
    if (pos==6 || pos==7 || pos==8 || order[step-1]=='U'){
        //when 0 is at 3rd row of puzzle
        //when the previous move is up
        //down move is invalid
        return;
    }else{
        swap(data[pos], data[pos+3]);   //move 0
        pos=pos+3;                      //new 0 position
        order=order+"D";                //record the order
        step++;                         //record the total step
    }
}

void Node::left(){
    if (pos==0 || pos==3 || pos==6 || order[step-1]=='R'){
        //when 0 is at 1st column of puzzle
        //when the previous move is right
        //left move is invalid
        return;
    }else{
        swap(data[pos], data[pos-1]);   //move 0
        pos=pos-1;                      //new 0 position
        order=order+"L";                //record the order
        step++;                         //record the total step
    }
}

void Node::right(){
    if (pos==2 || pos==5 || pos==8 || order[step-1]=='L'){
        //when 0 is at 3rd column of puzzle
        //when the previous move is left
        //right move is invalid
        return;
    }else{
        swap(data[pos], data[pos+1]);   //move 0
        pos=pos+1;                      //new 0 position
        order=order+"R";                //record the order
        step++;                         //record the total step
    }
}

void Node::swap(char& i, char& j){
    char temp=i;
    i=j;
    j=temp;
}

#endif // NODE_H
