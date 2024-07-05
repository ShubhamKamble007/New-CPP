#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentPlayer = 'X';
    resetBoard();

    connect(ui->b1, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui->b2, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui->b3, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui->b4, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui->b5, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui->b6, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui->b7, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui->b8, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui->b9, &QPushButton::clicked, this, &MainWindow::handleButtonClick);

    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetBoard()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            board[i][j] = ' ';
        }
    }
}

void MainWindow::handleButtonClick()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        int row = -1;
        int col = -1;

        if (button == ui->b1) { row = 0; col = 0; }
        else if (button == ui->b2) { row = 0; col = 1; }
        else if (button == ui->b3) { row = 0; col = 2; }
        else if (button == ui->b4) { row = 1; col = 0; }
        else if (button == ui->b5) { row = 1; col = 1; }
        else if (button == ui->b6) { row = 1; col = 2; }
        else if (button == ui->b7) { row = 2; col = 0; }
        else if (button == ui->b8) { row = 2; col = 1; }
        else if (button == ui->b9) { row = 2; col = 2; }

        if (row != -1 && col != -1 && board[row][col] == ' ')
        {
            board[row][col] = currentPlayer;
            updateUI();
            checkWin();
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

void MainWindow::checkWin()
{
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            QMessageBox::information(this, "Game Over", QString("Player %1 wins!").arg(board[i][0]));
            resetBoard();
            updateUI();
            return;
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            QMessageBox::information(this, "Game Over", QString("Player %1 wins!").arg(board[0][i]));
            resetBoard();
            updateUI();
            return;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        QMessageBox::information(this, "Game Over", QString("Player %1 wins!").arg(board[0][0]));
        resetBoard();
        updateUI();
        return;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        QMessageBox::information(this, "Game Over", QString("Player %1 wins!").arg(board[0][2]));
        resetBoard();
        updateUI();
        return;
    }

    bool draw = true;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                draw = false;
                break;
            }
        }
        if (!draw) break;
    }

    if (draw)
    {
        QMessageBox::information(this, "Game Over", "It's a draw!");
        resetBoard();
        updateUI();
    }
}

void MainWindow::updateUI()
{
    ui->b1->setText(QString(board[0][0]));
    ui->b2->setText(QString(board[0][1]));
    ui->b3->setText(QString(board[0][2]));
    ui->b4->setText(QString(board[1][0]));
    ui->b5->setText(QString(board[1][1]));
    ui->b6->setText(QString(board[1][2]));
    ui->b7->setText(QString(board[2][0]));
    ui->b8->setText(QString(board[2][1]));
    ui->b9->setText(QString(board[2][2]));
}
