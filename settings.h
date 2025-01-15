#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

class SettingsWindow : public QDialog {
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    QString getSnakeColor() const;
    QString getFruit() const;

signals:
    void settingsChanged(const QString &snakeColor, const QString &fruit);

private slots:
    void selectSnakeColor();
    void selectFruit();
    void acceptSettings();

private:
    QString snakeColor;
    QString fruit;

    QLabel *snakeColorLabel;
    QLabel *fruitLabel;
    QPushButton *snakeColorButton;
    QPushButton *fruitButton;
    QPushButton *okButton;
};

#endif // SETTINGSWINDOW_H
