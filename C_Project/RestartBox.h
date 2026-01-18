#ifndef C_PROJECT_RESTARTBOX_H
#define C_PROJECT_RESTARTBOX_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QProcess>

class RestartBox : public QDialog {
    Q_OBJECT
public:
    RestartBox(QWidget *parent = nullptr, const bool win = false) : QDialog(parent) {
        if (win) {
            setWindowTitle("You win !");
        } else {
            setWindowTitle("You lose !");
        }

        auto *layout = new QVBoxLayout(this);
        auto *button = new QPushButton("Restart", this);

        layout->addWidget(button);

        connect(button, &QPushButton::clicked, this, []() {
            QProcess::startDetached(QApplication::applicationFilePath());
            QApplication::quit();
        });
    }
};


#endif //C_PROJECT_RESTARTBOX_H