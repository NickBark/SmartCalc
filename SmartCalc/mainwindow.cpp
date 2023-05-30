#include "mainwindow.hpp"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setFixedSize(400, 400);
    graph = new Graph();

    Designer();
    Properties();
    Layouts();
    Connector();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::Designer() {
    cwCalc = new QFrame(this);

    vblCalc = new QVBoxLayout(this);
    leResultText = new QLabel(this);
    leText = new QLineEdit(this);

    glCalc = new QGridLayout(this);
    // layout
    pb0 = new QPushButton("0", this);
    pb1 = new QPushButton("1", this);
    pb2 = new QPushButton("2", this);
    pb3 = new QPushButton("3", this);
    pb4 = new QPushButton("4", this);
    pb5 = new QPushButton("5", this);
    pb6 = new QPushButton("6", this);
    pb7 = new QPushButton("7", this);
    pb8 = new QPushButton("8", this);
    pb9 = new QPushButton("9", this);
    pbAdd = new QPushButton("+", this);
    pbSub = new QPushButton("-", this);
    pbMul = new QPushButton("*", this);
    pbDiv = new QPushButton("/", this);
    pbMod = new QPushButton("%", this);
    pbPow = new QPushButton("^", this);

    pbSin = new QPushButton("sin", this);
    pbCos = new QPushButton("cos", this);
    pbAsin = new QPushButton("asin", this);
    pbAcos = new QPushButton("acos", this);
    pbTan = new QPushButton("tan", this);
    pbAtan = new QPushButton("atan", this);
    pbLn = new QPushButton("ln", this);
    pbLog10 = new QPushButton("log", this);

    pbResult = new QPushButton("=", this);

    // layout
}

void MainWindow::Properties() {
    this->setWindowTitle("SmartCalc");
    graph->setWindowTitle("Graph");

    cwCalc->setFixedSize(400, 400);

    //    leResultText->setReadOnly(true);

    pb0->setFixedSize(60, 25);
    pb1->setFixedSize(60, 25);
    pb2->setFixedSize(60, 25);
    pb3->setFixedSize(60, 25);
    pb4->setFixedSize(60, 25);
    pb5->setFixedSize(60, 25);
    pb6->setFixedSize(60, 25);
    pb7->setFixedSize(60, 25);
    pb8->setFixedSize(60, 25);
    pb9->setFixedSize(60, 25);
    pbAdd->setFixedSize(60, 25);
    pbSub->setFixedSize(60, 25);
    pbMul->setFixedSize(60, 25);
    pbDiv->setFixedSize(60, 25);
    pbMod->setFixedSize(60, 25);
    pbPow->setFixedSize(60, 25);
    pbResult->setFixedSize(60, 25);

    pbSin->setFixedSize(60, 25);
    pbCos->setFixedSize(60, 25);
    pbAsin->setFixedSize(60, 25);
    pbAcos->setFixedSize(60, 25);
    pbTan->setFixedSize(60, 25);
    pbAtan->setFixedSize(60, 25);
    pbLn->setFixedSize(60, 25);
    pbLog10->setFixedSize(60, 25);
}

void MainWindow::Layouts() {
    int rowSpan = 1;
    int columnSpan = 1;

    setCentralWidget(cwCalc);

    cwCalc->setLayout(vblCalc);
    vblCalc->addWidget(leResultText);
    vblCalc->addWidget(leText);
    vblCalc->addLayout(glCalc);

    glCalc->addWidget(pb1, 0, 1, rowSpan, columnSpan);
    glCalc->addWidget(pb2, 0, 2, rowSpan, columnSpan);
    glCalc->addWidget(pb3, 0, 3, rowSpan, columnSpan);

    glCalc->addWidget(pb4, 1, 1, rowSpan, columnSpan);
    glCalc->addWidget(pb5, 1, 2, rowSpan, columnSpan);
    glCalc->addWidget(pb6, 1, 3, rowSpan, columnSpan);

    glCalc->addWidget(pb7, 2, 1, rowSpan, columnSpan);
    glCalc->addWidget(pb8, 2, 2, rowSpan, columnSpan);
    glCalc->addWidget(pb9, 2, 3, rowSpan, columnSpan);

    glCalc->addWidget(pb0, 3, 2, rowSpan, columnSpan);

    glCalc->addWidget(pbAdd, 4, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbSub, 4, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbMul, 4, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbDiv, 5, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbMod, 5, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbPow, 5, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbSin, 6, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbCos, 6, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbTan, 6, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbAsin, 7, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbAcos, 7, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbAtan, 7, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbLn, 8, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbLog10, 8, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbResult, 8, 3, rowSpan, columnSpan);
}

void MainWindow::Connector() {
    connect(pb0, SIGNAL(clicked()), this, SLOT(slotPb0()));
    connect(pb1, SIGNAL(clicked()), this, SLOT(slotPb1()));
    connect(pb2, SIGNAL(clicked()), this, SLOT(slotPb2()));
    connect(pb3, SIGNAL(clicked()), this, SLOT(slotPb3()));
    connect(pb4, SIGNAL(clicked()), this, SLOT(slotPb4()));
    connect(pb5, SIGNAL(clicked()), this, SLOT(slotPb5()));
    connect(pb6, SIGNAL(clicked()), this, SLOT(slotPb6()));
    connect(pb7, SIGNAL(clicked()), this, SLOT(slotPb7()));
    connect(pb8, SIGNAL(clicked()), this, SLOT(slotPb8()));
    connect(pb9, SIGNAL(clicked()), this, SLOT(slotPb9()));

    connect(pbAdd, SIGNAL(clicked()), this, SLOT(slotPbAdd()));
    connect(pbSub, SIGNAL(clicked()), this, SLOT(slotPbSub()));
    connect(pbMul, SIGNAL(clicked()), this, SLOT(slotPbMul()));
    connect(pbDiv, SIGNAL(clicked()), this, SLOT(slotPbDiv()));
    connect(pbMod, SIGNAL(clicked()), this, SLOT(slotPbMod()));
    connect(pbPow, SIGNAL(clicked()), this, SLOT(slotPbPow()));

    connect(pbSin, SIGNAL(clicked()), this, SLOT(slotPbSin()));
    connect(pbCos, SIGNAL(clicked()), this, SLOT(slotPbCos()));
    connect(pbAsin, SIGNAL(clicked()), this, SLOT(slotPbAsin()));
    connect(pbAcos, SIGNAL(clicked()), this, SLOT(slotPbAcos()));
    connect(pbTan, SIGNAL(clicked()), this, SLOT(slotPbTan()));
    connect(pbAtan, SIGNAL(clicked()), this, SLOT(slotPbAtan()));
    connect(pbLog10, SIGNAL(clicked()), this, SLOT(slotPbLog10()));
    connect(pbLn, SIGNAL(clicked()), this, SLOT(slotPbLn()));

    connect(pbResult, SIGNAL(clicked()), this, SLOT(slotPbResult()));
}

void MainWindow::slotPb0() {
    qStr = leText->text();
    qStr += "0";
    leText->setText(qStr);
}
void MainWindow::slotPb1() {
    qStr = leText->text();
    qStr += "1";
    leText->setText(qStr);
}
void MainWindow::slotPb2() {
    qStr = leText->text();
    qStr += "2";
    leText->setText(qStr);
}
void MainWindow::slotPb3() {
    qStr = leText->text();
    qStr += "3";
    leText->setText(qStr);
}
void MainWindow::slotPb4() {
    qStr = leText->text();
    qStr += "4";
    leText->setText(qStr);
}
void MainWindow::slotPb5() {
    qStr = leText->text();
    qStr += "5";
    leText->setText(qStr);
}
void MainWindow::slotPb6() {
    qStr = leText->text();
    qStr += "6";
    leText->setText(qStr);
}
void MainWindow::slotPb7() {
    qStr = leText->text();
    qStr += "7";
    leText->setText(qStr);
}
void MainWindow::slotPb8() {
    qStr = leText->text();
    qStr += "8";
    leText->setText(qStr);
}
void MainWindow::slotPb9() {
    qStr = leText->text();
    qStr += "9";
    leText->setText(qStr);
}

void MainWindow::slotPbAdd() {
    qStr = leText->text();
    qStr += "+";
    leText->setText(qStr);
}

void MainWindow::slotPbSub() {
    qStr = leText->text();
    qStr += "-";
    leText->setText(qStr);
}

void MainWindow::slotPbMul() {
    qStr = leText->text();
    qStr += "*";
    leText->setText(qStr);
}

void MainWindow::slotPbDiv() {
    qStr = leText->text();
    qStr += "/";
    leText->setText(qStr);
}

void MainWindow::slotPbMod() {
    qStr = leText->text();
    qStr += "%";
    leText->setText(qStr);
}

void MainWindow::slotPbPow() {
    qStr = leText->text();
    qStr += "^";
    leText->setText(qStr);
}

void MainWindow::slotPbSin() {
    qStr = leText->text();
    qStr += "sin(";
    leText->setText(qStr);
}

void MainWindow::slotPbCos() {
    qStr = leText->text();
    qStr += "cos(";
    leText->setText(qStr);
}

void MainWindow::slotPbAsin() {
    qStr = leText->text();
    qStr += "asin(";
    leText->setText(qStr);
}

void MainWindow::slotPbAcos() {
    qStr = leText->text();
    qStr += "acos(";
    leText->setText(qStr);
}

void MainWindow::slotPbTan() {
    qStr = leText->text();
    qStr += "tan(";
    leText->setText(qStr);
}

void MainWindow::slotPbAtan() {
    qStr = leText->text();
    qStr += "atan(";
    leText->setText(qStr);
}

void MainWindow::slotPbLn() {
    qStr = leText->text();
    qStr += "ln(";
    leText->setText(qStr);
}

void MainWindow::slotPbLog10() {
    qStr = leText->text();
    qStr += "log(";
    leText->setText(qStr);
}

void MainWindow::slotPbResult() {
    qStr = leText->text();
    if (qStr.size()) {
        double result = 0;
        char resStr[255] = {};
        QByteArray br = qStr.toLatin1();
        const char* inputStr = br.data();
        qDebug() << "input str: " << inputStr;
        if (shuntingYard(inputStr, resStr, &result)) {
            qDebug() << "ERROR";
            leText->setText("ERROR");
            QMessageBox::warning(this, "ВНИМАНИЕ", "Деление на нуль");
        } else {
            qDebug() << "res str: " << resStr;
            qDebug() << "res nub: " << result;
            qStr = QString::number(result, 'g', 10);
            leText->setText(qStr);
            graph->show();
        }

    } else {
        qDebug() << "empty str";
    }
}
