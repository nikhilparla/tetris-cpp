#include "../include/Game.h"
#include "../include/Main.h"
#ifndef LINUX
#include <windows.h>
#endif

// int WINAPI WinMain(HINSTANCE hInstance, HININSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main()
{
    IO mIO;
    int mScreenHeight = mIO.GetScreenHeight();

    Pieces mPieces;
    Board mBoard(&mPieces, mScreenHeight);
    Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

    unsigned long mTime1 = SDL_GetTicks();

    while(!mIO.IsKeyDown (SDLK_ESCAPE))
    {
        mIO.ClearScreen();
        mGame.drawScene();
        mIO.UpdateScreen();

        int mKey = mIO.PollKey();

        switch (mKey)
        {
        case (SDLK_RIGHT):
        {
            if(mBoard.isPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX++;
            break;
        }
        case (SDLK_LEFT):
        {
            if(mBoard.isPossibleMovement(mGame.mPosX -1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX--;
            break;
        }
        case (SDLK_DOWN):
        {
            if(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
                mGame.mPosY++;
            break;
        }
        case (SDLK_z):
        {
            if(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation + 1))
                mGame.mRotation = (mGame.mRotation + 1) % 4;
            break;
        }
        default:
            break;
        }

        unsigned long mTime2 = SDL_GetTicks();
        if((mTime2 - mTime1) > WAIT_TIME)
        {
            if(mBoard.isPossibleMovement(mGame.mPosX,mGame.mPosY + 1, mGame.mPiece, mGame.mRotation ))
            {
                mGame.mPosY++;
            }
            else
            {
                mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
                mBoard.deletePossibleLines();
                if(mBoard.isGameOver())
                {
                    mIO.GetKey();
                    exit(0);
                }
                mGame.createNewPiece();
            }
            mTime1 = SDL_GetTicks();
            
        }
    }
    return 0;
}

