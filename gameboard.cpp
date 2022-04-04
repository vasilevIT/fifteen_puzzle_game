#include "gameboard.h"
#include <random>

namespace {
    bool isAdjacent(const GameBoard::Position first, const GameBoard::Position second) {
        if (first == second) {
            return false;
        }

        const auto calcDistance = [](const size_t pos1, const size_t pos2) {
            int distance = static_cast<int>(pos1);
            distance -= static_cast<int>(pos2);

            distance = std::abs(distance);

            return distance;
        };

        bool result {false};

        // Two elements in one row
        if (first.first == second.first) {
            int distance = calcDistance(first.second, second.second);
            if (distance == 1) {
                result = true;
            }
        }
        if (first.second == second.second) {
            int distance = calcDistance(first.first, second.first);
            if (distance == 1) {
                result = true;
            }
        }

        return result;
    }
}

GameBoard::GameBoard(const size_t boardDimention, QObject *parent)
    : QAbstractListModel{parent},
    m_dimension(boardDimention),
    m_boardSize(m_dimension * m_dimension)
{
    m_rawBoard.resize(m_boardSize);
    std::iota(m_rawBoard.begin(), m_rawBoard.end(), 1);
    shufflle();
}

size_t GameBoard::boardSize() const
{
    return m_boardSize;
}

bool GameBoard::move(int index)
{
    if (index < 0 && index >= m_rawBoard.size()) {
        return false;
    }


    int indexElement = static_cast<size_t>(index);

    Position currentElementPosition = getRowCol(indexElement);

    auto  hiddenElementIterator = std::find(m_rawBoard.begin(), m_rawBoard.end(), m_rawBoard.size());


    Q_ASSERT(hiddenElementIterator != m_rawBoard.end());

    Position hiddenElementPosition {getRowCol(std::distance(m_rawBoard.begin(), hiddenElementIterator))};

    if (!isAdjacent(currentElementPosition, hiddenElementPosition)) {
        return false;
    }

    // swap
    std::swap(hiddenElementIterator->value, m_rawBoard[index].value);

    dataChanged(createIndex(0, 0), createIndex(m_rawBoard.size(), 0));
    return true;
}


GameBoard::Position GameBoard::getRowCol(size_t index) const
{
    Q_ASSERT(m_dimension > 0);

    size_t row = index / m_dimension;
    size_t column = index % m_dimension;

    return std::make_pair(row, column);
}

size_t GameBoard::dimension() const
{
    return m_dimension;
}

void GameBoard::shufflle()
{
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    do {
    std::shuffle(m_rawBoard.begin(), m_rawBoard.end(), generator);
    } while(!isBoardValid());

}

bool GameBoard::isBoardValid() const
{
    int inv {0};
    for (size_t i {0}; i < m_boardSize; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (m_rawBoard[j].value > m_rawBoard[i].value) {
                ++inv;
            }
        }
    }

    const size_t start_point = 1;

    for(size_t i = 0; i < m_boardSize; ++i) {
        if (m_rawBoard[i].value == m_boardSize) {
            inv += start_point + i / m_dimension;
        }
    }

    return (inv % 2) ==  0;
}

int GameBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_rawBoard.size();
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && index.isValid()) {
        const int row_index = {index.row()};
        return QVariant::fromValue((int)m_rawBoard.at(row_index).value);
    }
    return QVariant();
}

