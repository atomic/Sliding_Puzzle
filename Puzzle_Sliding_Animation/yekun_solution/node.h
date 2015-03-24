#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

namespace Yekun {

// Tony : trying to make a conflict here
//this is for testing
//this is 2nd test for GitHub push

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
    int find_hvalue();
private:
    void swap(char& i, char& j);
    int single_hvalue(int index, char letter);
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

int Node::find_hvalue(){
    int hvalue=0;
    for (unsigned int i=0; i<=data.length()-1; i++){
        hvalue=hvalue+single_hvalue(i, data[i]);
    }
    return hvalue;
}

int Node::single_hvalue(int index, char letter){
    int hvalue=0;
    if (letter=='1'){
        switch (index){
        case 0:
            hvalue=0;
            break;
        case 1:
            hvalue=1;
            break;
        case 2:
            hvalue=2;
            break;
        case 3:
            hvalue=1;
            break;
        case 4:
            hvalue=2;
            break;
        case 5:
            hvalue=3;
            break;
        case 6:
            hvalue=2;
            break;
        case 7:
            hvalue=3;
            break;
        case 8:
            hvalue=4;
            break;
        default:
            cout<<"Invalid index!"<<endl;
        }
    }else if (letter=='2'){
        switch (index){
        case 0:
            hvalue=1;
            break;
        case 1:
            hvalue=0;
            break;
        case 2:
            hvalue=1;
            break;
        case 3:
            hvalue=2;
            break;
        case 4:
            hvalue=1;
            break;
        case 5:
            hvalue=2;
            break;
        case 6:
            hvalue=3;
            break;
        case 7:
            hvalue=2;
            break;
        case 8:
            hvalue=3;
            break;
        default:
            cout<<"Invalid index!"<<endl;
        }
    }else if (letter=='3'){
        switch (index){
        case 0:
            hvalue=2;
            break;
        case 1:
            hvalue=1;
            break;
        case 2:
            hvalue=0;
            break;
        case 3:
            hvalue=3;
            break;
        case 4:
            hvalue=2;
            break;
        case 5:
            hvalue=1;
            break;
        case 6:
            hvalue=4;
            break;
        case 7:
            hvalue=3;
            break;
        case 8:
            hvalue=2;
            break;
        default:
            cout<<"Invalid index!"<<endl;
        }
    }else if (letter=='4'){
        switch (index){
        case 0:
            hvalue=1;
            break;
        case 1:
            hvalue=2;
            break;
        case 2:
            hvalue=3;
            break;
        case 3:
            hvalue=0;
            break;
        case 4:
            hvalue=1;
            break;
        case 5:
            hvalue=2;
            break;
        case 6:
            hvalue=1;
            break;
        case 7:
            hvalue=2;
            break;
        case 8:
            hvalue=3;
            break;
        default:
            cout<<"Invalid index!"<<endl;
        }
    }else if (letter=='5'){
        switch (index){
        case 0:
            hvalue=2;
            break;
        case 1:
            hvalue=1;
            break;
        case 2:
            hvalue=2;
            break;
        case 3:
            hvalue=1;
            break;
        case 4:
            hvalue=0;
            break;
        case 5:
            hvalue=1;
            break;
        case 6:
            hvalue=2;
            break;
        case 7:
            hvalue=1;
            break;
        case 8:
            hvalue=2;
            break;
        default:
            cout<<"Invalid index!"<<endl;
        }
    }else if (letter=='6'){
        switch (index){
        case 0:
            hvalue=3;
            break;
        case 1:
            hvalue=2;
            break;
        case 2:
            hvalue=1;
            break;
        case 3:
            hvalue=2;
            break;
        case 4:
            hvalue=1;
            break;
        case 5:
            hvalue=0;
            break;
        case 6:
            hvalue=3;
            break;
        case 7:
            hvalue=2;
            break;
        case 8:
            hvalue=1;
            break;
        default:
            cout<<"Invalid index!"<<endl;
        }
    }else if (letter=='7'){
        switch (index){
        case 0:
            hvalue=2;
            break;
        case 1:
            hvalue=3;
            break;
        case 2:
            hvalue=4;
            break;
        case 3:
            hvalue=1;
            break;
        case 4:
            hvalue=2;
            break;
        case 5:
            hvalue=3;
            break;
        case 6:
            hvalue=0;
            break;
        case 7:
            hvalue=1;
            break;
        case 8:
            hvalue=2;
            break;
        default:
            cout<<"Invalid index!"<<endl;
        }
    }else if (letter=='8'){
        switch (index){
        case 0:
            hvalue=3;
            break;
        case 1:
            hvalue=2;
            break;
        case 2:
            hvalue=3;
            break;
        case 3:
            hvalue=2;
            break;
        case 4:
            hvalue=1;
            break;
        case 5:
            hvalue=2;
            break;
        case 6:
            hvalue=1;
            break;
        case 7:
            hvalue=0;
            break;
        case 8:
            hvalue=1;
            break;
        default:
            cout<<"Invalid index!"<<endl;
        }
    }else{
        hvalue=0;
    }
    return hvalue;
}

}

#endif // NODE_H
