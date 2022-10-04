#include<iostream>
#include<array>
#include<vector>
#include<bitset>

class Solution
{
public:
    void solve_board(std::vector<std::vector<char>>&board) const noexcept
    {
        std::array<std::bitset<9>,9>in_row={0,0,0,0,0,0,0,0,0};
        std::array<std::bitset<9>,9>in_col={0,0,0,0,0,0,0,0,0};
        std::array<std::bitset<9>,9>in_cell={0,0,0,0,0,0,0,0,0};

        for (std::size_t row=0;row<9;++row)
        {
            for (std::size_t col=0;col<9;++col)
            {
                char num_check;
                if((num_check=board[row][col])!='0')
                {
                    std::size_t num_check_idx=num_check - '1';
                    in_row[row].set(num_check_idx);
                    in_col[col].set(num_check_idx);
                    std::size_t cell=(row/3)*3+col/3;
                    in_cell[cell].set(num_check_idx);
                }
            }
        }
        solve(board,0,0,in_row,in_col,in_cell);
    }

private:

    static constexpr std::pair<std::size_t,std::size_t>
    next_box(std::vector<std::vector<char>>&board,std::size_t row,std::size_t col) noexcept
    {
        while (row!=9)
        {
            if (board[row][col]=='0')
            {
                return {row,col};
            }
            row=row+(1+col)/9;
            col=(1+col)%9;
        }
        return {9,0};
    }

    static bool
    solve(std::vector<std::vector<char>>&board,std::size_t const row_start,std::size_t const col_start,std::array<std::bitset<9>,9>&in_row,std::array<std::bitset<9>,9>&in_col,std::array<std::bitset<9>,9>&in_cell) noexcept
    {
        auto [row,col]=next_box(board,row_start,col_start);

        if (row==9)
        {
            return true;
        }
        std::size_t const cell=(row/3)*3+col/3;
        std::bitset<9>const contains=in_row[row] | in_col[col] | in_cell[cell];
        if (contains.all())
        {
            return false;
        }

        for (std::size_t num_check_idx=0;num_check_idx<9;++num_check_idx)
        {
            if (!contains[num_check_idx])
            {
                board[row][col]=static_cast<char>(num_check_idx+'1');
                in_row[row].set(num_check_idx);
                in_col[col].set(num_check_idx);
                in_cell[cell].set(num_check_idx);
                if (solve(board,row,col,in_row,in_col,in_cell))
                {
                    return true;
                }

                in_row[row].reset(num_check_idx);
                in_col[col].reset(num_check_idx);
                in_cell[cell].reset(num_check_idx);
            }
        }
        board[row][col]='0';
        return false;
    }
};

void print_board(std::vector<std::vector<char>>board)
{
    for (std::size_t row=0;row<9;++row)
    {
        for (std::size_t col=0;col<9;++col)
        {
            std::cout<<board[row][col]<<" ";
        }
        std::cout<<"\n";
    }
}

std::vector<std::vector<char>>array_to_vector(std::array<char,81>const input_board)
{
    std::vector<std::vector<char>>board;
    board.reserve(9);
    for (std::size_t row=0;row<9;++row)
    {
        std::vector<char>current_row;
        current_row.reserve(9);
        for (std::size_t col=0;col<9;++col)
        {
            current_row.push_back(input_board[row * 9 + col]);
        }
        board.push_back(current_row);
    }
    return board;
}

using namespace std;

int main()
{   
    array<char,81>input_board;

    for(int i=0;i<81;++i){
        cin>>input_board[i];
    }
    vector<vector<char>>initial_board=array_to_vector(input_board);
    vector<vector<char>>board=array_to_vector(input_board);

    Solution soln;

    soln.solve_board(board);

    if(initial_board!=board){
        print_board(board);
    }
    else{
        cout<<"No Solution"<<endl;
    }
    return 0;
}
