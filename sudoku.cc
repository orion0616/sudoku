#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <set>
#include <sys/time.h>

using namespace std;

typedef vector<set<int> > Choicelist;

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
        int x = row/3*3;
        int y = column/3*3;
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        if(x+i == row || y+j == column)
                                continue;
                        if(values[x+i][y+j] == values[row][column])
                                return false;
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
}

void updateList(sudoku& prob,Choicelist& choices, int varchosen){
        int row = varchosen/9;
        int column = varchosen%9;
        int value = prob.values[row][column];
        //check vertical
        for(int i=0;i<9;i++){
                if(row == i)
                        continue;
                choices[i*9+column].erase(value);
        }
        //check horizontal
        for(int i=0;i<9;i++){
                if(column == i)
                        continue;
                choices[9*row+i].erase(value);
        }
        //check box
        int x = row/3*3;
        int y = column/3*3;
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        if(x+i == row || y+j == column)
                                continue;
                        choices[(x+i)*9+y+j].erase(value);
                }
        }
        return;
}

string btandfcandmrv(sudoku prob,Choicelist choices,int varchosen = -1){
        if(prob.isComplete())
                return prob.valuesToString();
        if(varchosen == -1){
                for(int i=0;i<81;i++){
                        if(prob.values[i/9][i%9]!=0)
                                updateList(prob,choices,i);
                }
        }
        else{
                updateList(prob,choices,varchosen);
        }
        string result;
        int min = 10;
        int minvar = 100;
        for(int i=0;i<81;i++){
                if(prob.values[i/9][i%9] == 0){
                        if(choices[i].size() < min){
                                min = choices[i].size();
                                minvar = i;
                        }
                }
        }
        int var = minvar;
        for(auto it = choices[var].begin();it!=choices[var].end();it++){
                prob.values[var/9][var%9] = (*it);
                if(prob.checkConstraint(var)){
                        result = btandfcandmrv(prob,choices,var);
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

void printTime(timeval t0, timeval t1){
        t1.tv_sec -= t0.tv_sec;
        if (t1.tv_usec < t0.tv_usec) {
                t1.tv_sec -= 1;
                t1.tv_usec += 1000000 - t0.tv_usec;
        } else {
                t1.tv_usec -= t0.tv_usec;
        }
        printf("%ld.%06d sec\n\n", t1.tv_sec, t1.tv_usec);
}

int main(){
        struct timeval t0, t1,start,goal;
        string exp,result;
        set<int> all;
        for(int i=1;i<=9;i++){
                all.insert(i);
        }
        gettimeofday(&start,NULL);
        while(cin >> exp){
                Choicelist choices;
                for(int i=0;i<81;i++){
                        choices.push_back(all);
                }
                sudoku problem;
                for(int i=0;i<81;i++){
                        if(exp[i] == '.')
                                problem.values[i/9][i%9] = 0;
                        else{
                                int var = (int)exp[i]-(int)'0';
                                problem.values[i/9][i%9] = var;
                                set<int> tmp;
                                tmp.insert(var);
                                choices[i] = tmp;
                        }
                }
                gettimeofday(&t0, NULL);
                result = btandfcandmrv(problem,choices);
                gettimeofday(&t1, NULL);
                printTime(t0,t1);
        }
        gettimeofday(&goal,NULL);
        printTime(start,goal);
}
