#include "mainwindow.h"
#include "ui_mainwindow.h"

// 파일 입출력을 위한 클래스들
#include <QFile>
#include <QTextStream>

#include <QMessageBox> // 사용자 알림 창을 위한 클래스
#include <QPixmap> // 이미지 출력용 클래스
#include <QDebug> // 디버깅용 로그 출력
#include <cstdlib>  // c++에서 .py 돌리기 위한 system()함수가진 클래스
#include <QDir> // 디렉토리 생성 및 경로 작업
#include <QProcess> // 외부프로그램 파이썬 실행
#include <QPushButton>


// 생성자: UI 초기화
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // UI 연결
}

// 소멸자: 메모리 정리
MainWindow::~MainWindow()
{
    delete ui;
}

// 이미지 생성
void MainWindow::on_generateButton_clicked()
{
    // 1. 사용자 입력 가져오기
    QString prompt = ui->promptInput->toPlainText(); //QTextEdit에서 텍스트 추출
    qDebug() << "[입력 프롬프트]:" << prompt;

    // 2. 프롬프트 저장할 폴더 만들기 (없으면 생성)
    QDir dir("../image_prompt");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // 3. 텍스트 파일로 프롬프트 저장
    QFile file("../image_prompt/image_prompt.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);  // 파일 스트림 열기
        out << prompt; // 프롬프트 내용 쓰기
        file.close();
        QMessageBox::information(this, "성공", "프롬프트 저장 완료!");
    } else {
        QMessageBox::warning(this, "에러", "프롬프트 저장 실패");
    }

    // 4. 이미지 생성 파이썬 파일 실행
    int result = std::system("python C:\\Users\\WONHO\\Desktop\\mainwindow\\gpt_image_creator.py");
    if (result != 0) {
        QMessageBox::warning(this, "실패", "이미지 생성 실패!");
        return;
    }


    // 5. 이미지 출력
    QPixmap image("../output_image/image.png");
    if (!image.isNull()) {
        ui->imageLabel->setPixmap(image.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio));
    }else {
        QMessageBox::warning(this, "에러", "이미지 로딩 실패");
    }

}

// 일기 + 생성된 이미지로 명상 스크립트 만들기
void MainWindow::on_pushButton_clicked()
{
    // 1. 일기 입력 저장
    QString diary = ui->user_diary->toPlainText();
    qDebug() << "[입력된 일기]:" << diary;

    // 2. 일기 저장 폴더 생성 (없으면 만들기)
    QDir dir("../diary_input");
    if (!dir.exists()) {
        dir.mkpath(".");
    }


    // 3. diary.txt로 저장
    QFile file("../diary_input/diary.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << diary;
        file.close();
        QMessageBox::information(this, "성공", "일기 저장 완료!");
    }
    else
    {
        QMessageBox::warning(this, "에러", "일기 저장 실패");
        return;
    }

    // 4. 명상 스크립트 생성 Python 실행(외부실행의존)
    int result2 = std::system("python C:\\Users\\WONHO\\Desktop\\mainwindow\\gpt_script_creator.py");
    if (result2 != 0) {
        QMessageBox::warning(this, "실패", "명상 스크립트 생성 실패!");
    } else {
        QMessageBox::information(this, "성공", "명상 스크립트 생성 완료!");
    }

    // 4. 명상 스크립트 생성 파이썬 실행 (비동기 실행)_ 이미지 생성에 비해 비교적 짧아서, 비동기 실행가능
    QString scriptPath = "C:/Users/WONHO/Desktop/mainwindow/gpt_script_creator.py";
    bool scriptSuccess = QProcess::startDetached("python", QStringList() << scriptPath);

    if (!scriptSuccess) {
        QMessageBox::warning(this, "실패", "명상 스크립트 생성 실패!");
    } else {
        QMessageBox::information(this, "성공", "명상 스크립트 생성 시작됨!");
    }

}

// 명상TTS 생성
void MainWindow::on_generateTTSButton_clicked()
{
    // Python 스크립트 경로 (절대 경로로 설정)
    QString pythonScriptPath = "C:/Users/WONHO/Desktop/mainwindow/gpt_tts_creator.py";

    qDebug() << "TTS 생성 중...";
    bool success = QProcess::startDetached("python", QStringList() << pythonScriptPath);

    if (success) {
        qDebug() << "명상TTS 스크립트 실행 성공!";
    } else {
        qDebug() << "Python 실행 실패.";
    }
}

// 명상TTS 재생
void MainWindow::on_playTTSButton_clicked()
{
    QString audioPath = "C:/Users/WONHO/Desktop/mainwindow/build/output_script/speech.mp3";

    if (QFile::exists(audioPath)) {
        qDebug() << "TTS 재생 중...";
        QProcess::startDetached("cmd.exe", { "/C", audioPath });  // Windows 기본 음악 플레이어로 실행
    } else {
        qDebug() << "오디오 파일이 존재하지 않습니다!";
    }
}
