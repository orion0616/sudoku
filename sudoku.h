#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>

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
                std::string valuesToString();
};


#endif
