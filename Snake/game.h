#ifndef GAME_H
#define GAME_H

#include <QTimerEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QVector>
#include <QPoint>


// Класс для описания логики игры
/*
 * Имеем массив, который хранит информацию о всех частях змейки
 * Координаты x,y
 * Поле условно разбито на квадраты
*/


class Game : public QWidget
{
public:
    Game(QWidget* parent = nullptr);

protected:
    void timerEvent(QTimerEvent* e) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    static const int DOT_WIDTH = 20;   // Размеры точек
    static const int DOT_HIGTH = 20;
    static const int FIELD_WIDTH = 20; // Количество точек
    static const int FIELD_HIGHT = 20;
    static const int DELAY = 150;      // Миллисекунды

    int m_timerId;

    enum Directions
    {
        left, right, up, down
    };
    Directions m_dir;

    bool m_inGame;          // переменная для хранения состояния
    QVector<QPoint> m_dots; // переменная для хранения всех частей змейки
    QPoint m_apple;         // положение яблока

private:
    void initGame();
    void doDrawing();
    void locateApple();
    void move();
    void check_field();
    void check_apple();
    void gameOver();
};

#endif // GAME_H
