#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QAbstractListModel>
#include <vector>


class GameBoard: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
    Q_PROPERTY(int hiddenElementValue READ boardSize CONSTANT)
public:
    static constexpr size_t defaultPuzzleDimension = {4};

    GameBoard(const size_t boardDimention = defaultPuzzleDimension, QObject *parent = nullptr);

    struct Tile {
        size_t value {};
        Tile& operator = (const size_t newValue) {
                value = newValue;
                return *this;
        }
        bool operator == (const size_t other) {
                return value == other;
        }
    };


private:
    const size_t m_dimension;
    const size_t m_boardSize;
    std::vector<Tile> m_rawBoard;

    void  shufflle();
    bool isBoardValid() const;

    // QAbstractItemModel interface
public:
  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  size_t dimension() const;
  size_t boardSize() const;
  Q_INVOKABLE bool move(int index);

  using Position = std::pair<size_t, size_t>;

  Position getRowCol(size_t index) const;
};

#endif // GAMEBOARD_H
