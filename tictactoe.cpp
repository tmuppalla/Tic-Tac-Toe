#include <iostream>
#include<string>
#include<stdlib.h>

using namespace std;
struct toe
{
    char arr[3][3];
    char human;
    char master;
};
int i,j,k;
void board_print(char grid[3][3]);
int recur_fun(char arr[3][3],char human,char master);
int minmax_value(char arr[3][3],char master,char human);
char predict_mov(char arr[3][3])
{
/* this function checks all the 8 winning possibilities and returns the respective position of grid */
    if (arr[0][0] != '_' && (arr[0][0] == arr[0][1] && arr[0][0] == arr[0][2] ||
                             arr[0][0] == arr[1][0] && arr[0][0] == arr[2][0] ||
                             arr[0][0] == arr[1][1] && arr[0][0] == arr[2][2]))
        return arr[0][0];
    if (arr[1][1] != '_' && (arr[1][1] == arr[1][0] && arr[1][1] == arr[1][2] ||
                             arr[1][1] == arr[0][1] && arr[1][1] == arr[2][1] ||
                             arr[1][1] == arr[2][0] && arr[1][1] == arr[0][2]))
        return arr[1][1];
    if (arr[2][2] != '_' && (arr[2][2] == arr[0][2] && arr[2][2] == arr[1][2] ||
                             arr[2][2] == arr[2][0] && arr[2][2] == arr[2][1]))
        return arr[2][2];
    return 0;
}
int recur_fun(char arr[3][3],char human,char master)
{
    /* this function recursively places the human value in grid, based on that it calculates the best move and returns it*/
    int best_move = -10;
    int score_move = 0,r,c;
    if (predict_mov(arr) == human)
        return 10;
    else if (predict_mov(arr) == master)
        return -10;
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 3; c++)
        {
            if (arr[r][c] == '_')
            {
                arr[r][c] = human;
                score_move = -(recur_fun(arr, master, human)); // the negative sign is to minimize the human play
                arr[r][c] = '_';
                if (score_move >= best_move)
                {
                    best_move = score_move;
                }
            }
        }
    }
    if (best_move == -10 || best_move == 0)
        return 0;
    else if (best_move < 0)
        return best_move + 1;
    else if (best_move > 0)
        return best_move - 1;
}
int minmax_value(char arr[3][3],char master,char human)
{
    /* this returns the cpu position based on the best move value*/
    int best_move = -10;
    int x,y;
    int score_move;
    int s,t;


    for (s = 0; s < 3; s++)
    {
        for (t = 0; t < 3; t++)
        {
            if (arr[s][t] == '_')
            {
                arr[s][t] = master;
                score_move = -(recur_fun(arr, human, master));
                arr[s][t] = '_';
                if (score_move >= best_move)
                {
                    best_move = score_move;
                    x = s;
                    y = t;
                }
            }
        }
    }

    return (10*x + y);
}
void grid(char grid[3][3])
{
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            grid[i][j]='_';
        }
    }
}
void board_print(char grid[3][3])
{
    cout<<"-------------------";
    for(i=0; i<3; i++)
    {
        cout<<"\t\t"<<endl;
        for(j=0; j<3; j++)
        {
            cout<<"|";
            cout<< grid[i][j]<<"|";
        }
    }
    cout<<endl<<"-------------------"<<endl;
}
int main()
{
    toe xo;
    int x=0,x_y;
    cout<<endl<<"*****************UNBETABLE TIC TAC TOE********************"<< endl;
    cout<<endl<<"choose ONE of the letters x OR O and try to beat the computer.. ";
    grid(xo.arr);
    cout<<endl<<endl<<"Before starting the game please select your character"<<endl;
    cout<<"choose any of 'X' or 'O'"<<endl<<"***you can only play with single character"<<endl;
    cout<<endl<<endl<<"please enter your choice"<<endl;
    cin>> xo.human;
    cout<<"your choice is "<<xo.human<<endl<<endl;
    if(xo.human=='X'|| xo.human=='x')
        xo.master='O';
    else
        xo.master='x';
    cout<<"Get ready to play with me and I am going to play with '"<<xo.master<<"'    "<<endl;
    board_print(xo.arr);

    for(x=1; x<10;)
    {
        for(;;)
        {
            int a,b;
            for(;;)
            {
                cout<<endl<<"Enter the row and coloumn position where would you like to play"<<endl;
                cout<<"row- ";
                cin>>a;
                cout<<"column- ";
                cin>>b;
                if(a>=1 && a<=3 && b>=1 && b<=3)
                    break;
                cout<<"invalid input";
            }
            cout<<a<<" "<<b<<" "<<endl;
            if(xo.arr[a-1][b-1]=='_') //this initializes the board with a default value
            {
                xo.arr[a-1][b-1]=xo.human;
                break;
            }
            else
            {
                cout<<"this block is filled, please enter the row and coloumn again";
            }
        }
        x++;
        board_print(xo.arr);
        if(predict_mov(xo.arr))
        {
            cout<<endl<<xo.human<<"won"<<endl;
            exit(1);
        }
        if(x==10)
        {
            break;
        }
        x_y = minmax_value(xo.arr, xo.master, xo.human);
        int xy= x_y / 10;
        int xy1= x_y % 10;
        xo.arr[xy][xy1] = xo.master; // places the computer move in grid
        x++;
        cout<<endl<<endl;
        board_print(xo.arr);
        if (predict_mov(xo.arr))
        {
            cout <<endl<< xo.master << " won!" <<endl;
            break;
        }
    }
    if(x==9)
        cout << "Draw game!" << endl;
    board_print(xo.arr);
    return 0;

}
