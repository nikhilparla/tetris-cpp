#ifndef _PIECES_
#define _PIECES_

class Pieces
{
    public:
        int getBlockType(int pPiece, int pRotation, int pX, int pY);
        int getInitXPos (int pPiece, int pRotation);
        int getInitYPos (int pPiece, int pRotation); 
}


#endif