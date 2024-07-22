#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_b1_clicked();
    void on_web_clicked();
    void on_ww_clicked();
    void on_go_clicked();
    void on_ap_clicked();
    void showResponse();  // Slot to show the bot's response after a delay

private:
    Ui::MainWindow *ui;
    QString userName;  // Store user's name
    QTimer *responseTimer;  // Timer for delay

    QString botResponse;  // Store bot's response
    double eval(const QString &expression);  // Function declaration for evaluation
};

#endif // MAINWINDOW_H
