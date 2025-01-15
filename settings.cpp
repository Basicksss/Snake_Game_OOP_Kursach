#include "settings.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QDialog(parent), snakeColor(""), fruit("") {
    // Создаем виджеты
    snakeColorLabel = new QLabel("Выберите цвет змейки:");
    fruitLabel = new QLabel("Выберите фрукт:");

    // Кнопки для выбора цвета змейки и фрукта
    snakeColorButton = new QPushButton();
    fruitButton = new QPushButton();

    // Устанавливаем начальные изображения
    snakeColorButton->setIcon(QIcon(":/images/default_snake.png")); // Путь к изображению по умолчанию
    fruitButton->setIcon(QIcon(":/images/default_fruit.png")); // Путь к изображению по умолчанию

    okButton = new QPushButton("ОК");

    // Устанавливаем компоновку
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(snakeColorLabel);
    layout->addWidget(snakeColorButton);
    layout->addWidget(fruitLabel);
    layout->addWidget(fruitButton);
    layout->addWidget(okButton);

    setLayout(layout);

    // Подключаем сигналы и слоты
    connect(snakeColorButton, &QPushButton::clicked, this, &SettingsWindow::selectSnakeColor);
    connect(fruitButton, &QPushButton::clicked, this, &SettingsWindow::selectFruit);
    connect(okButton, &QPushButton::clicked, this, &SettingsWindow::acceptSettings);
}

void SettingsWindow::selectSnakeColor() {
    // Здесь вы можете открыть диалог выбора цвета или просто установить цвет
    snakeColor = "yellow"; // Пример установки цвета
    snakeColorButton->setIcon(QIcon(":/images/yellow_snake.png")); // Изменяем изображение
}

void SettingsWindow::selectFruit() {
    // Здесь вы можете открыть диалог выбора фрукта
    fruit = "apple"; // Пример установки фрукта
    fruitButton->setIcon(QIcon(":/images/apple.png")); // Изменяем изображение
}

void SettingsWindow::acceptSettings() {
    emit settingsChanged(snakeColor, fruit);
    accept(); // Закрываем окно
}

QString SettingsWindow::getSnakeColor() const {
    return snakeColor;
}

QString SettingsWindow::getFruit() const {
    return fruit;
}
