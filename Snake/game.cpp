#include <QDebug>
#include <QPainter>
#include <QTime>
#include <QMessageBox>

#include "game.h"


Game::Game(QWidget* parent)
{
    this->resize(DOT_WIDTH * FIELD_WIDTH, DOT_HIGTH * FIELD_HIGHT);
    this->setWindowTitle("Snake game");

    this->initGame();
}

void Game::timerEvent(QTimerEvent * event)
{
    Q_UNUSED(event);

    if (m_inGame)
    {
        this->check_apple();
        this->move();
        this->check_field();
    }

    this->repaint();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key == Qt::Key_Left  && m_dir != Directions::right) { m_dir = Directions::left; }
    if (key == Qt::Key_Right && m_dir != Directions::left)  { m_dir = Directions::right; }
    if (key == Qt::Key_Up    && m_dir != Directions::down)  { m_dir = Directions::up; }
    if (key == Qt::Key_Down  && m_dir != Directions::up)    { m_dir = Directions::down; }
}

void Game::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    doDrawing();
}

void Game::initGame()
{
    m_inGame = true;
    m_dir = right;

    /* Инициализация игры происходит в 2-х точках
       В начале игры и при завершении  */

    m_dots.resize(3); // начальный размер змейки - 3 части, голова в нулевом элементе

    for(int i = 0; i < m_dots.size(); i++)
    {
        m_dots[i].rx() = m_dots.size() - i - 1;
        m_dots[i].ry() = 0;
    }

    locateApple(); // произвольно расположить яблоко на поле

    this->m_timerId = startTimer(this->DELAY);
}

void Game::doDrawing()
{
    QPainter qp(this);

    if (m_inGame)
    {
        qp.setBrush(Qt::red);
        qp.drawEllipse(m_apple.x() * this->DOT_WIDTH, m_apple.y() * this->DOT_HIGTH, this->DOT_WIDTH, this->DOT_HIGTH);

        for(int i = 0; i < m_dots.size(); i++)
        {
            if(i == 0)
            {
                qp.setBrush(Qt::white);
                qp.drawRect(m_dots[i].x() * this->DOT_WIDTH, m_dots[i].y() * this->DOT_HIGTH, this->DOT_WIDTH, this->DOT_HIGTH);
            }
            else
            {
                qp.setBrush(Qt::green);
                qp.drawRect(m_dots[i].x() * this->DOT_WIDTH, m_dots[i].y() * this->DOT_HIGTH, this->DOT_WIDTH, this->DOT_HIGTH);
            }
        }
    }
    else
    {
        this->gameOver();
    }
}

void Game::locateApple()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    m_apple.rx() = qrand() % this->DOT_WIDTH;
    m_apple.ry() = qrand() % this->DOT_HIGTH;
}

void Game::move()
{
    for(int i = m_dots.size() - 1; i > 0; --i)
        m_dots[i] = m_dots[i-1];

    switch(m_dir)
    {
    case left:  m_dots[0].rx() -= 1; break;
    case right: m_dots[0].rx() += 1; break;
    case up:    m_dots[0].ry() -= 1; break;
    case down:  m_dots[0].ry() += 1; break;
    }
}

void Game::check_field()
{
    if(m_dots.size() > 4)
    {
        for(int i  = 1; i < m_dots.size(); i++)
        {
            if (m_dots[0] == m_dots[i])
            {
                m_inGame = false;
            }
        }
    }

    if(m_dots[0].x() >= this->FIELD_WIDTH) { m_inGame = false; }
    if(m_dots[0].x() < 0)                  { m_inGame = false; }
    if(m_dots[0].y() >= this->FIELD_HIGHT) { m_inGame = false; }
    if(m_dots[0].y() < 0)                  { m_inGame = false; }

    if(!m_inGame)
    {
        killTimer(m_timerId);
    }
}

void Game::check_apple()
{
    if (m_apple == m_dots[0])
    {
        m_dots.push_back(QPoint(0,0));
        locateApple();
    }
}

void Game::gameOver()
{
    QMessageBox msgb;
    msgb.setText("Game Over");
    msgb.exec();

    initGame();
}
