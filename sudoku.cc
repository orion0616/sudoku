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
                string valuesToString();
};

bool sudoku::checkConstraint(int num){
        return checkVertical(num) && checkHorizontal(num) && checkBox(num);
}

bool sudoku::checkVertical(int num){
        int row = num/9;
        int column = num%9;
        for(int i=0;i<9;i++){
                if(row == i)
                        continue;
                if(values[i][column] == values[row][column])
                        return false;
        }
        return true;
}

bool sudoku::checkHorizontal(int num){
        int row = num/9;
        int column = num%9;
        for(int i=0;i<9;i++){
                if(column == i)
                        continue;
                if(values[row][i] == values[row][column])
                        return false;
        }
        return true;
}

bool sudoku::checkBox(int num){
        int row = num/9;
        int column = num%9;
        int boxx = row/3;
        int boxy = column/3;
        if(boxx == 0 && boxy == 0){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(boxx*3+i == row || boxy*3+j == column){
                                        continue;
                                }
                                if(values[0+i][0+j] == values[row][column])
                                        return false;
                        }
                }
        }
        else if(boxx == 0 && boxy == 1){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(boxx*3+i == row || boxy*3+j == column){
                                        continue;
                                }
                                if(values[0+i][3+j] == values[row][column])
                                        return false;
                        }
                }
        }
        else if(boxx == 0 && boxy == 2){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(boxx*3+i == row || boxy*3+j == column){
                                        continue;
                                }
                                if(values[0+i][6+j] == values[row][column])
                                        return false;
                        }
                }
        }
        else if(boxx == 1 && boxy == 0){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(boxx*3+i == row || boxy*3+j == column){
                                        continue;
                                }
                                if(values[3+i][0+j] == values[row][column])
                                        return false;
                        }
                }
        }
        else if(boxx == 1 && boxy == 1){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(boxx*3+i == row || boxy*3+j == column){
                                        continue;
                                }
                                if(values[3+i][3+j] == values[row][column])
                                        return false;
                        }
                }
        }
        else if(boxx == 1 && boxy == 2){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(boxx*3+i == row || boxy*3+j == column){
                                        continue;
                                }
                                if(values[3+i][6+j] == values[row][column])
                                        return false;
                        }
                }
        }
        else if (boxx == 2 && boxy == 0){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(boxx*3+i == row || boxy*3+j == column){
                                        continue;
                                }
                                if(values[6+i][0+j] == values[row][column])
                                        return false;
                        }
                }
        }
        else if (boxx == 2 && boxy == 1){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(boxx*3+i == row || boxy*3+j == column){
                                        continue;
                                }
                                if(values[6+i][3+j] == values[row][column])
                                        return false;
                        }
                }
        }
        else{
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(boxx*3+i == row || boxy*3+j == column){
                                        continue;
                                }
                                if(values[6+i][6+j] == values[row][column])
                                        return false;
                        }
                }
        }
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

string sudoku::valuesToString(){
        string s = "";
        for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                        s.append(to_string(values[i][j]));
                }
        }
        return s;
}

void stringToValues(string s){
        int count = 0;
        for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                        cout << s[count];
                        count++;
                }
                cout << endl;
        }
        cout << endl;
}

string backtrackingdfs(sudoku prob){
        string result;
        if (prob.isComplete())
                return prob.valuesToString();
        vector<int> unassignedVariable;
        for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                        if(prob.values[i][j]==0)
                                unassignedVariable.push_back(i*9+j);
                }
        }
        //there are something better choices
        int var = unassignedVariable[0];
        for(int i=1;i<=9;i++){
                prob.values[var/9][var%9] = i;
                if(prob.checkConstraint(var)){
                        result = backtrackingdfs(prob);
                        if(result == "failure"){
                                prob.values[var/9][var%9] = 0;
                        }
                        else{
                                return result;
                        }
                }
                else{
                        prob.values[var/9][var%9] = 0;
                }
        }
        return "failure";
}

int main(){
        string exp,result;
        while(cin >> exp){
                sudoku problem;
                for(int i=0;i<81;i++){
                        if(exp[i] == '.')
                                problem.values[i/9][i%9] = 0;
                        else
                                problem.values[i/9][i%9] = (int)exp[i]-(int)'0';
                }
                result = backtrackingdfs(problem);
                stringToValues(result);
        }
}
