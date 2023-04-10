/********************************************************************************
** Form generated from reading UI file 'untitledMFqTfH.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UNTITLEDMFQTFH_H
#define UNTITLEDMFQTFH_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Weather
{
public:
    QPushButton *pushFront;
    QLabel *left_city;
    QLabel *right_city;
    QLabel *cur_city;
    QPushButton *pushBack;
    QFrame *frame;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QFrame *main_frame;
    QLabel *cur_info;
    QLabel *cur_header;
    QLabel *cur_image;

    void setupUi(QDialog *Weather)
    {
        if (Weather->objectName().isEmpty())
            Weather->setObjectName("Weather");
        Weather->resize(1200, 600);
        Weather->setMinimumSize(QSize(1200, 600));
        Weather->setMaximumSize(QSize(1200, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8("images/test.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Weather->setWindowIcon(icon);
        Weather->setStyleSheet(QString::fromUtf8(""));
        pushFront = new QPushButton(Weather);
        pushFront->setObjectName("pushFront");
        pushFront->setGeometry(QRect(1080, 0, 111, 91));
        QFont font;
        font.setPointSize(14);
        pushFront->setFont(font);
        pushFront->setCursor(QCursor(Qt::PointingHandCursor));
        pushFront->setMouseTracking(false);
        pushFront->setTabletTracking(false);
        pushFront->setAcceptDrops(false);
        pushFront->setAutoFillBackground(false);
        pushFront->setStyleSheet(QString::fromUtf8("background-color: transparent; border: none;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../resources/images/Front.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushFront->setIcon(icon1);
        pushFront->setIconSize(QSize(95, 105));
        pushFront->setAutoRepeat(false);
        left_city = new QLabel(Weather);
        left_city->setObjectName("left_city");
        left_city->setGeometry(QRect(-110, 0, 551, 41));
        QFont font1;
        font1.setPointSize(20);
        left_city->setFont(font1);
        left_city->setLayoutDirection(Qt::LeftToRight);
        left_city->setStyleSheet(QString::fromUtf8("color: white"));
        left_city->setAlignment(Qt::AlignCenter);
        right_city = new QLabel(Weather);
        right_city->setObjectName("right_city");
        right_city->setGeometry(QRect(760, 0, 551, 41));
        right_city->setFont(font1);
        right_city->setLayoutDirection(Qt::LeftToRight);
        right_city->setStyleSheet(QString::fromUtf8("color: white"));
        right_city->setAlignment(Qt::AlignCenter);
        cur_city = new QLabel(Weather);
        cur_city->setObjectName("cur_city");
        cur_city->setGeometry(QRect(310, 30, 560, 41));
        cur_city->setFont(font1);
        cur_city->setLayoutDirection(Qt::LeftToRight);
        cur_city->setStyleSheet(QString::fromUtf8("color: white"));
        cur_city->setAlignment(Qt::AlignCenter);
        pushBack = new QPushButton(Weather);
        pushBack->setObjectName("pushBack");
        pushBack->setGeometry(QRect(10, 0, 111, 91));
        pushBack->setFont(font);
        pushBack->setCursor(QCursor(Qt::PointingHandCursor));
        pushBack->setMouseTracking(false);
        pushBack->setTabletTracking(false);
        pushBack->setAcceptDrops(false);
        pushBack->setAutoFillBackground(false);
        pushBack->setStyleSheet(QString::fromUtf8("background-color: transparent; border: none;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../resources/images/Back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushBack->setIcon(icon2);
        pushBack->setIconSize(QSize(95, 105));
        pushBack->setAutoRepeat(false);
        frame = new QFrame(Weather);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 1201, 101));
        frame->setStyleSheet(QString::fromUtf8("/* background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #4E4E4E, stop:1 #000000);*/\n"
                                               "background-image: url(../resources/images/main-background.png);\n"
                                               "border-style: solid; \n"
                                               "border-bottom-width: 2px;\n"
                                               "border-color: #000;\n"
                                               ""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        scrollArea = new QScrollArea(Weather);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(10, 110, 1180, 480));
        scrollArea->setStyleSheet(QString::fromUtf8(" QScrollBar:vertical {\n"
                                                    "	border: none;\n"
                                                    "    background: rgb(45, 45, 68);\n"
                                                    "    width: 14px;\n"
                                                    "    margin: 15px 0 15px 0;\n"
                                                    "	border-radius: 0px;\n"
                                                    " }\n"
                                                    "\n"
                                                    "/*  HANDLE BAR VERTICAL */\n"
                                                    "QScrollBar::handle:vertical {	\n"
                                                    "	background-color: rgb(80, 80, 122);\n"
                                                    "	min-height: 30px;\n"
                                                    "	border-radius: 7px;\n"
                                                    "}\n"
                                                    "QScrollBar::handle:vertical:hover{	\n"
                                                    "	background-color: rgb(255, 0, 127);\n"
                                                    "}\n"
                                                    "QScrollBar::handle:vertical:pressed {	\n"
                                                    "	background-color: rgb(185, 0, 92);\n"
                                                    "}\n"
                                                    "\n"
                                                    "/* BTN TOP - SCROLLBAR */\n"
                                                    "QScrollBar::sub-line:vertical {\n"
                                                    "	border: none;\n"
                                                    "	background-color: rgb(59, 59, 90);\n"
                                                    "	height: 15px;\n"
                                                    "	border-top-left-radius: 7px;\n"
                                                    "	border-top-right-radius: 7px;\n"
                                                    "	subcontrol-position: top;\n"
                                                    "	subcontrol-origin: margin;\n"
                                                    "}\n"
                                                    "QScrollBar::sub-line:vertical:hover {	\n"
                                                    "	background-color: rgb(255, 0, 127);\n"
                                                    "}\n"
                                                    "QScrollBar::sub-line:vertical:pressed {	\n"
                                                    "	background-color: rgb(185, 0, 92);\n"
                                                    "}\n"
                                                    "\n"
                                                    "/* BTN BOTTOM - SCROLLBAR */\n"
                                                    "QScrollBar"
                                                    "::add-line:vertical {\n"
                                                    "	border: none;\n"
                                                    "	background-color: rgb(59, 59, 90);\n"
                                                    "	height: 15px;\n"
                                                    "	border-bottom-left-radius: 7px;\n"
                                                    "	border-bottom-right-radius: 7px;\n"
                                                    "	subcontrol-position: bottom;\n"
                                                    "	subcontrol-origin: margin;\n"
                                                    "}\n"
                                                    "QScrollBar::add-line:vertical:hover {	\n"
                                                    "	background-color: rgb(255, 0, 127);\n"
                                                    "}\n"
                                                    "QScrollBar::add-line:vertical:pressed {	\n"
                                                    "	background-color: rgb(185, 0, 92);\n"
                                                    "}\n"
                                                    "\n"
                                                    "/* RESET ARROW */\n"
                                                    "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\n"
                                                    "	background: none;\n"
                                                    "}\n"
                                                    "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
                                                    "	background: none;\n"
                                                    "}"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1180, 480));
        scrollAreaWidgetContents->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
                                                                  "    background-color: lightgray;\n"
                                                                  "}\n"
                                                                  "\n"
                                                                  "QTableWidget::item {\n"
                                                                  "    padding: 5px;\n"
                                                                  "}\n"
                                                                  "\n"
                                                                  "QTableWidget::item:selected {\n"
                                                                  "    background-color: darkblue;\n"
                                                                  "    color: white;\n"
                                                                  "}"));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        main_frame = new QFrame(scrollAreaWidgetContents);
        main_frame->setObjectName("main_frame");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(main_frame->sizePolicy().hasHeightForWidth());
        main_frame->setSizePolicy(sizePolicy);
        main_frame->setMinimumSize(QSize(0, 0));
        main_frame->setStyleSheet(QString::fromUtf8("background-color: none;\n"
                                                    "border: none"));
        main_frame->setFrameShape(QFrame::StyledPanel);
        main_frame->setFrameShadow(QFrame::Raised);
        cur_info = new QLabel(main_frame);
        cur_info->setObjectName("cur_info");
        cur_info->setGeometry(QRect(630, 60, 221, 111));
        QFont font2;
        font2.setPointSize(14);
        cur_info->setFont(font2);
        cur_info->setContextMenuPolicy(Qt::ActionsContextMenu);
        cur_info->setStyleSheet(QString::fromUtf8("line-height: 20px"));
        cur_info->setLineWidth(1);
        cur_info->setMidLineWidth(0);
        cur_info->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        cur_info->setWordWrap(false);
        cur_info->setOpenExternalLinks(false);
        cur_header = new QLabel(main_frame);
        cur_header->setObjectName("cur_header");
        cur_header->setGeometry(QRect(70, 0, 1001, 41));
        cur_header->setFont(font1);
        cur_header->setAlignment(Qt::AlignCenter);
        cur_image = new QLabel(main_frame);
        cur_image->setObjectName("cur_image");
        cur_image->setGeometry(QRect(340, 60, 201, 111));
        cur_image->setFrameShape(QFrame::NoFrame);
        cur_image->setFrameShadow(QFrame::Plain);
        cur_image->setPixmap(QPixmap(QString::fromUtf8("../resources/images/cloud.png")));
        cur_image->setScaledContents(true);

        verticalLayout->addWidget(main_frame);

        scrollArea->setWidget(scrollAreaWidgetContents);
        frame->raise();
        left_city->raise();
        right_city->raise();
        pushFront->raise();
        cur_city->raise();
        pushBack->raise();
        scrollArea->raise();

        retranslateUi(Weather);

        QMetaObject::connectSlotsByName(Weather);
    } // setupUi

    void retranslateUi(QDialog *Weather)
    {
        Weather->setWindowTitle(QCoreApplication::translate("Weather", "Dialog", nullptr));
        pushFront->setText(QString());
#if QT_CONFIG(shortcut)
        pushFront->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        left_city->setText(QCoreApplication::translate("Weather", "TextLabel", nullptr));
        right_city->setText(QCoreApplication::translate("Weather", "TextLabel", nullptr));
        cur_city->setText(QCoreApplication::translate("Weather", "TextLabel", nullptr));
        pushBack->setText(QString());
#if QT_CONFIG(shortcut)
        pushBack->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        cur_info->setText(QCoreApplication::translate("Weather", "<html><head/><body>\n"
                                                                 "<p style=\"line-height: 20px\">\320\247\320\270\321\201\321\202\320\276\320\265 \320\275\320\265\320\261\320\276<br/><span style=\" color:#00aa00;\">+9</span>(<span style=\" color:#0000ff;\">0</span>) \302\260C<br/>\342\206\222 <span style=\" color:#00aa00;\">3</span>-<span style=\" color:#00aa00;\">5</span> \320\274/\321\201<br/><span style=\" color:#ffff00;\">772</span> \320\274\320\274.\321\200\321\202.\321\201\321\202<br/>0.0 mm | 0% </p>\n"
                                                                 "</body></html>", nullptr));
        cur_header->setText(QCoreApplication::translate("Weather", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \320\277\320\276\320\263\320\276\320\264\320\260", nullptr));
        cur_image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Weather: public Ui_Weather {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UNTITLEDMFQTFH_H
