#include <iostream>
#include <vector>
#include <string>

using namespace std;

class sudoku{
        public:
                sudoku(){}
                ~sudoku(){}
                int values[9][9];
                bool checkConstraint(int num);
                bool checkVertical(int num);
                bool checkHorizontal(int num);
                bool checkBox(int num);
                bool isComplete();
                void printState();
};

bool sudoku::checkConstraint(int num){
        return true;
}

bool sudoku::checkVertical(int num){
        return true;
}

bool sudoku::checkBox(int num){
        return true;
}

bool sudoku::isComplete(){
        for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                        if(values[i][j] == 0)
                                return false;
                }
        }
        return true;
}

void sudoku::printState(){
        for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                        cout << values[i][j];
                }
                cout << endl;
        }
        cout << endl;
}

int main(){
        string exp;
        while(cin >> exp){
                sudoku problem;
                for(int i=0;i<81;i++){
                        if(exp[i] == '.')
                                problem.values[i/9][i%9] = 0;
                        else
                                problem.values[i/9][i%9] = (int)exp[i]-(int)'0';
                }
                problem.printState();
        }
        return 0;
}
