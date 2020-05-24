#include "../include/Game.h"

int Game::getRand(int pA, int pB)
{
    return rand() % (pB - pA + 1) + pA;
}

void Game::InitGame()
{
    srand((unsigned int) time(NULL));

    // first place
    mPiece = getRand(0,6);
    mRotation = getRand(0,3);
    mPosX = (BOARD_WIDTH/2) + mPieces->getInitXPos(mPiece, mRotation);
    mPosY = mPieces->getInitYPos(mPiece, mRotation);

    //Next Piece
    mNextPiece = getRand(0,6);
    mNextRotation = getRand(0,3);
    mNextPosX = BOARD_WIDTH + 5;
    mNextPosY = 5;
}

void Game::createNewPiece()
{
    mPiece = mNextPiece;
    mRotation = mNextRotation;
    mPosX = (BOARD_WIDTH/2) + mPieces->getInitXPos(mPiece, mRotation);
    mPosY = mPieces->getInitYPos(mPiece, mRotation);

    // Random next pirce
    mNextPiece = getRand(0,6);
    mNextRotation = getRand(0,3);
}

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation)
{
    color mColor;

    int pixelsX = mBoard->getXPosInPixels(pX);
    int pixelsY = mBoard->getYPosInPixels(pY);

    for(int i=0; i< PIECE_BLOCKS; i++)
    {
        for(int j=0; j< PIECE_BLOCKS; j++)
        {
            switch (mPieces->getBlockType(pPiece, pRotation, j, i))
            {
                case 1: mColor = GREEN; break;
                case 2: mColor = BLUE; break;
                default:
                    break;
            }
            if(mPieces->getBlockType(pPiece, pRotation, j, i) != 0)
                mIO->DrawRectangle(pixelsX + i * BLOCK_SIZE, 
                                    pixelsY + j * BLOCK_SIZE, 
                                    pixelsX + i * BLOCK_SIZE + BLOCK_SIZE -1,
                                    pixelsY + j * BLOCK_SIZE + BLOCK_SIZE - 1,
                                    mColor);
        }
    }
}

void Game::DrawBoard()
{
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH/2)) - 1;
    int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH/2));
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    mIO->DrawRectangle(mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight -1, BLUE);
    mIO->DrawRectangle(mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight -1, BLUE);

    mX1 +=1;
    for(int i=0; i< BOARD_WIDTH; i++)
    {
        for (int j=0; j < BOARD_HEIGHT ; j++)
        {
            if(!mBoard->isFreeBlock(i,j))
                mIO->DrawRectangle(mX1 + i * BLOCK_SIZE,
                                    mY+ j* BLOCK_SIZE,
                                    (mX1 + i * BLOCK_SIZE) + BLOCK_SIZE -1,
                                    (mY + j* BLOCK_SIZE) + BLOCK_SIZE -1,
                                    RED);
        }
    }
}

void Game::drawScene()
{
    DrawBoard();
    DrawPiece(mPosX, mPosY, mPiece, mRotation);
    DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);

}