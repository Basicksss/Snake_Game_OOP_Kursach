#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QWidget>
#include <QLabel>


namespace Ui {
class GameOverWindow;
}

class GameOverWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameOverWindow(int score, int fruitCount, QWidget *parent = nullptr);
    ~GameOverWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GameOverWindow *ui;

    QLabel *scoreLabel;
    QLabel *fruitCountLabel;
};

#endif // GAMEOVERWINDOW_H
