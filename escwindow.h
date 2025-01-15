#ifndef ESCWINDOW_H
#define ESCWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>


namespace Ui {
class EscWindow;
}

class EscWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EscWindow(int score, int fruitCount, QWidget *parent = nullptr);
    ~EscWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EscWindow *ui;
    QLabel *scoreLabel;
    QLabel *fruitCountLabel;
};

#endif // ESCWINDOW_H
