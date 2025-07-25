#include <vector>
#include "TextDisplay.h"
#include "Observer.h"
#include "AttackState.h"
#include "Info.h"
#include "Subject.h"

//potentially check this, not sure if this constructor is properly made
TextDisplay::TextDisplay(std::string setupString, int n, bool enableBonus) : boardSize{n}, enableBonus{enableBonus} {
    if (enableBonus) {
        stringDisplay.resize(n);
        for (int i = 0; i < n; i++) {
            stringDisplay[i].resize(n);
            for (int j = 0; j < n; j++)
                stringDisplay[i][j] = std::string(1, setupString[i * n + j]);
        }
    } 
    else {
        charDisplay.resize(n);
        for (int i = 0; i < n; i++) {
            charDisplay[i].resize(n);
            for (int j = 0; j < n; j++)
                charDisplay[i][j] = setupString[i * n + j];
        }
    }
}

void TextDisplay::notify(Subject &sender) {
    Piece temp = sender.getInfo().curPiece;
    int row = sender.getInfo().row;
    int col = sender.getInfo().col;
    bool isDarkSquare = ((row + col) % 2 == 1);
    
    if (enableBonus) {
        switch(temp.type) {
            case PieceType::Pawn: 
                if (temp.colour == Colour::Nothing)
                    stringDisplay[row][col] = isDarkSquare ? " " : "_";
                else if (temp.colour == Colour::Black)
                    stringDisplay[row][col] = "♟";
                else if (temp.colour == Colour::White)
                    stringDisplay[row][col] = "♙"; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::Knight: 
                if (temp.colour == Colour::Nothing)
                    stringDisplay[row][col] = isDarkSquare ? " " : "_";
                else if (temp.colour == Colour::Black)
                    stringDisplay[row][col] = "♞";
                else if (temp.colour == Colour::White)
                    stringDisplay[row][col] = "♘"; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::Bishop: 
                if (temp.colour == Colour::Nothing)
                    stringDisplay[row][col] = isDarkSquare ? " " : "_";
                else if (temp.colour == Colour::Black)
                    stringDisplay[row][col] = "♝";
                else if (temp.colour == Colour::White)
                    stringDisplay[row][col] = "♗"; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::Rook: 
                if (temp.colour == Colour::Nothing)
                    stringDisplay[row][col] = isDarkSquare ? " " : "_";
                else if (temp.colour == Colour::Black)
                    stringDisplay[row][col] = "♜";
                else if (temp.colour == Colour::White)
                    stringDisplay[row][col] = "♖"; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::Queen: 
                if (temp.colour == Colour::Nothing)
                    stringDisplay[row][col] = isDarkSquare ? " " : "_";
                else if (temp.colour == Colour::Black)
                    stringDisplay[row][col] = "♛";
                else if (temp.colour == Colour::White)
                    stringDisplay[row][col] = "♕"; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::King: 
                if (temp.colour == Colour::Nothing)
                    stringDisplay[row][col] = isDarkSquare ? " " : "_";
                else if (temp.colour == Colour::Black)
                    stringDisplay[row][col] = "♚";
                else if (temp.colour == Colour::White)
                    stringDisplay[row][col] = "♔"; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
        }
    } else {
        switch(temp.type) {
            case PieceType::Pawn: 
                if (temp.colour == Colour::Nothing)
                    charDisplay[row][col] = isDarkSquare ? ' ' : '_';
                else if (temp.colour == Colour::Black)
                    charDisplay[row][col] = 'p';
                else if (temp.colour == Colour::White)
                    charDisplay[row][col] = 'P'; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::Knight: 
                if (temp.colour == Colour::Nothing)
                    charDisplay[row][col] = isDarkSquare ? ' ' : '_';
                else if (temp.colour == Colour::Black)
                    charDisplay[row][col] = 'n';
                else if (temp.colour == Colour::White)
                    charDisplay[row][col] = 'N'; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::Bishop: 
                if (temp.colour == Colour::Nothing)
                    charDisplay[row][col] = isDarkSquare ? ' ' : '_';
                else if (temp.colour == Colour::Black)
                    charDisplay[row][col] = 'b';
                else if (temp.colour == Colour::White)
                    charDisplay[row][col] = 'B'; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::Rook: 
                if (temp.colour == Colour::Nothing)
                    charDisplay[row][col] = isDarkSquare ? ' ' : '_';
                else if (temp.colour == Colour::Black)
                    charDisplay[row][col] = 'r';
                else if (temp.colour == Colour::White)
                    charDisplay[row][col] = 'R'; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::Queen: 
                if (temp.colour == Colour::Nothing)
                    charDisplay[row][col] = isDarkSquare ? ' ' : '_';
                else if (temp.colour == Colour::Black)
                    charDisplay[row][col] = 'q';
                else if (temp.colour == Colour::White)
                    charDisplay[row][col] = 'Q'; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
            
            case PieceType::King: 
                if (temp.colour == Colour::Nothing)
                    charDisplay[row][col] = isDarkSquare ? ' ' : '_';
                else if (temp.colour == Colour::Black)
                    charDisplay[row][col] = 'k';
                else if (temp.colour == Colour::White)
                    charDisplay[row][col] = 'K'; 
                else
                    std::cerr << "bad colour from textdisplay notify";
                break;
        }
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    out << "\n";
    for (int i = 0; i < td.boardSize; i++) {
        out << (td.boardSize - i) << " ";
        for (int j = 0; j < td.boardSize; j++) {
            if (td.enableBonus)
                out << td.stringDisplay[td.boardSize - i - 1][j];
            else out << td.charDisplay[td.boardSize - i - 1][j];
        }
        out << "\n";
    }
    out << "\n  ";
    for (int j = 0; j < td.boardSize; ++j)
        out << (char)('a' + j);
    out << "\n";
    return out;
}
