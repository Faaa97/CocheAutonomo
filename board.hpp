#ifndef BOARD_HPP
#define BOARD_HPP


class Board : public QFrame{
    Q_OBJECT
public:
    Board(QWidget *parent = 0);

public slots:
    void start();
    void pause();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BOARD_HPP
