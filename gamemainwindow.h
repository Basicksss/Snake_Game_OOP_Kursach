#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <QDockWidget>
#include <QLabel>

namespace Ui {
class GameMainWindow;
}

class GameMainWindow : public QDockWidget
{
    Q_OBJECT

public:
    explicit GameMainWindow(QDockWidget *parent = nullptr);
    ~GameMainWindow();

private:
    Ui::GameMainWindow *ui;
    int score;
    int fruitCount;

    QLabel *scoreLabel;
    QLabel *fruitCountLabel;
};

#endif // GAMEMAINWINDOW_H
