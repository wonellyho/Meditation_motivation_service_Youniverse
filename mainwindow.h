#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_generateButton_clicked(); // 이미지 생성
    void on_pushButton_clicked();  // 일기저장+명상스크립트 생성 버튼
    void on_generateTTSButton_clicked(); // 명상 TTS 생성버튼
    void on_playTTSButton_clicked(); // 명상 TTS 재생버튼
};



#endif // MAINWINDOW_H
