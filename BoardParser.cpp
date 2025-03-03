#include "BoardParser.h"
#include <sstream>

PieceColor BoardParser::ParseColor(char c)
{
    if (c == 'w' || c == 'W') {
        return PieceColor::white;
    }
    else if (c == 'b' || c == 'B') {
        return PieceColor::black;
    }
    else {
        return PieceColor::defult;
    }
}

PieceType BoardParser::ParseType(char c)
{
    switch (toupper(c)) {
    case 'P': return PieceType::pawn;
    case 'R': return PieceType::rook;
    case 'N': return PieceType::knight;
    case 'B': return PieceType::bishop;
    case 'Q': return PieceType::queen;
    case 'K': return PieceType::king;
    default: return PieceType::defult;
    }
}

bool BoardParser::ParseMoved(char c)
{
    return isupper(c);
}

BoardParser::BoardParser(Board& board,Rule& rule) : m_board(board),m_Rule(rule)
{
}

void BoardParser::ParseFile(map<Vector2i, shared_ptr<Piece>>& board, string path)
{
    std::cout << "Parsing board from " << path << std::endl;
    std::ifstream f(path);

    if (!f.is_open()) {
        std::cerr << "Error: Unable to open file for reading: " << path << std::endl;
        return;
    }

    board.clear();


    std::string line;
    while (std::getline(f, line))
    {
        std::stringstream ss(line);
        std::string typeStr, colorStr, xStr, yStr;

        std::getline(ss, typeStr, ',');
        std::getline(ss, colorStr, ',');
        std::getline(ss, xStr, ',');
        std::getline(ss, yStr, ',');

        int x = std::stoi(xStr);
        int y = std::stoi(yStr);
        Vector2i pos(x, y);

        PieceType type = ParseType(typeStr[0]);
        PieceColor color = ParseColor(colorStr[0]);

        char pieceChar = typeStr[0];

        board[pos] = std::make_shared<Piece>(pos, pieceChar, color);
    }

    f.close();
    std::cout << "Board parsed successfully from " << path << std::endl;
}

void BoardParser::SaveFile(const map<Vector2i, shared_ptr<Piece>>& board, int round,PieceColor m_currentTurn, string path)
{
    std::ofstream f(path);

    if (!f.is_open()) {
        std::cerr << "Error: Unable to open file for writing: " << path << std::endl;
        return;
    }

    //รับเทิร์นและรอบ
    f << "Round:" << round << std::endl;
    f << "Turn:" << (m_currentTurn == PieceColor::white ? 'w' : 'b') << std::endl;

    for (const auto& pair : board)
    {
        const Vector2i& position = pair.first;
        const std::shared_ptr<Piece>& piece = pair.second;

        if (piece)
        {
            char pieceChar = piece->getChar();
            if (piece->getHasMove()) {
                pieceChar = toupper(pieceChar);
            }
            else {
                pieceChar = tolower(pieceChar);
            }

            f << pieceChar << ","; // เขียนตัวอักษรพิมพ์ใหญ่หรือเล็ก
            f << (piece->getColor() == PieceColor::white ? 'w' : 'b') << ",";
            f << position.x << "," << position.y << std::endl;
        }
        else
        {
            // Skip nullptr
            continue;
        }
    }

    f.close();
    std::cout << "Board saved successfully to " << path << std::endl;
}

void BoardParser::LoadGame(map<Vector2i, shared_ptr<Piece>>& board, int& round, PieceColor& m_currentTurn, string path)
{
    std::cout << "Loading game from " << path << std::endl;
    std::ifstream f(path);

    if (!f.is_open()) {
        std::cerr << "Error: Unable to open file for reading: " << path << std::endl;
        return;
    }

    board.clear();

    std::string line;
    while (std::getline(f, line))
    {
        if (line.find("Round:") == 0)
        {
            round = std::stoi(line.substr(6));
        }
        else if (line.find("Turn:") == 0)
        {
            m_currentTurn = ParseColor(line[5]);
        }
        else
        {
            std::stringstream ss(line);
            std::string typeStr, colorStr, xStr, yStr;

            std::getline(ss, typeStr, ',');
            std::getline(ss, colorStr, ',');
            std::getline(ss, xStr, ',');
            std::getline(ss, yStr, ',');

            int x = std::stoi(xStr);
            int y = std::stoi(yStr);
            Vector2i pos(x, y);

            PieceType type = ParseType(typeStr[0]);
            PieceColor color = ParseColor(colorStr[0]);

            char pieceChar = typeStr[0];
            bool hasMoved = ParseMoved(pieceChar);

            board[pos] = std::make_shared<Piece>(pos, tolower(pieceChar), color); // load lower case.
            board[pos]->setHasMove(hasMoved);
        }
    }

    f.close();
    std::cout << "Game loaded successfully from " << path << std::endl;
}