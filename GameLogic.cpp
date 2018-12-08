#include "GameLogic.hpp"
#include "stdlib.h"
#include "string.h"

ColorMap colorMap = {{2, Red}, {4, Lime}, {8, Blue}, {16, Pink}, {32, Cyan}, {64, Red},
                     {128, Lime}, {256, Blue}, {512, Pink}, {1024, Cyan}, {2048, Green}};

Game::Game(DisplayApp *app)
{
    displayApp = app;
    score = 0;
    memset(grid, 0, sizeof(grid));
}

void Game::updateGrid()
{
    displayApp->paintGrid(grid, colorMap);
}

void Game::moveTiles(Directions direction)
{
    if(direction == Up) {
        moveUp();
    } else if(direction == Down) {
        moveDown();
    } else if(direction == Left) {
        moveLeft();
    } else if(direction == Right) {
        moveRight();
    }
}

void Game::rotate()
{
    int i,j;
    int temp[4][4]={0};
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            temp[j][i]=grid[i][j];
        }
    }
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            grid[i][j]=temp[i][j];
        }
    }
}

void Game::generate()
{
    int no,k,l;
     k = rand()%4;
     l=rand()%4;
     if(grid[k][l]==0)
      {
         no=2*((rand()%10)+1);
         if(no==3 || no==2)
         {
            grid[k][l]=4;
         }
         else
         {
             grid[k][l]=2;
         }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%d ",grid[i][j]);
        }
        printf("\n");
    }
}
void Game::moveUp()
{
    int i,j,k,tmp;
    //printf("in up function\n");
    for(k=0;k<4;k++)
    {
        tmp = -1, j=0;
        for(i=0; i<4; i++){
            if(grid[i][k] != 0){
                if(tmp == -1){
                    tmp = grid[i][k];
                } else if(grid[i][k] == tmp){
                    grid[j][k] = tmp + tmp;
                    score= score+grid[j][k];
                    tmp = -1;
                    j++;
                } else {
                    grid[j][k] = tmp;
                    tmp = grid[i][k];
                    j++;
                }
            }
        }
        if(tmp != -1){
            grid[j][k] = tmp;
            j++;
        }
        while(j < 4){
            grid[j][k] = 0;
            j++;
        }
    }
}
void Game::moveDown()
{
    //printf("in down function\n");
    int i,j,k,tmp;
    for(k=0;k<4;k++)//column
    {
        tmp = -1, j=3;
        for(i=3; i>=0; i--)//row
        {
            if(grid[i][k] != 0){
                if(tmp == -1){
                    tmp = grid[i][k];
                } else if(grid[i][k] == tmp){
                    grid[j][k] = tmp + tmp;
                    score= score+grid[j][k];
                    tmp = -1;
                    j--;
                } else {
                    grid[j][k] = tmp;
                    tmp = grid[i][k];
                    j--;
                }
            }
        }
        if(tmp != -1){
            grid[j][k] = tmp;
            j--;
        }
        while(j >= 0){
            grid[j][k] = 0;
            j--;
        }
    }

}
void Game::moveLeft()
{
    rotate();
    moveUp();
    rotate();
}
void Game::moveRight()
{
    rotate();
    moveDown();
    rotate();
}


