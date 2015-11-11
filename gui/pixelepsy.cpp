#include "gui/pixelepsy.h"
#include "ui_pixelepsy.h"

#include "sprite/buffer.h"
#include "sprite/sprite.h"
#include "gui/viewer.h"

#include <functional>

#include <QGraphicsPixmapItem>
#include <QMdiArea>
#include <QMenuBar>
#include <QHBoxLayout>


Pixelepsy::Pixelepsy(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pixelepsy)
    , mdiArea(new QMdiArea)
    , bar(new QMenuBar)
{
    this->setMenuBar(bar);
    this->createFileActions();
    //essential, do not remove
    //this->ui->setupUi(this);
    //QMdiaArea for subwindows
    this->setCentralWidget(mdiArea);

    //example of adding a widget and layouts.
    //QWidget* tools = new QWidget;
    //tools->setGeometry(QRect(100, 100, 100, 100));
    //tools->setWindowTitle("OMG");
    //mdiArea->addSubWindow(tools);
    //mdiArea->setLayout(new QHBoxLayout(mdiArea));
    //mdiArea->layout()->addWidget(tools);
    //mdiArea won't allow adding widgets. only subwindows.
    //tools->show();
}

Pixelepsy::~Pixelepsy()
{
    delete ui;
}

void Pixelepsy::createFileActions() {
    this->File = new QMenu(tr("&File"));
    this->menuBar()->addMenu(this->File);
    createAction(this->File, this->actionNew, "New", std::bind(&Pixelepsy::on_actionNew_triggered, this));
    createAction(this->File, this->actionOpen, "Open", std::bind(&Pixelepsy::on_actionOpen_triggered, this));
    createAction(this->File, this->actionSave, "Save", std::bind(&Pixelepsy::on_actionSave_triggered, this));
    createAction(this->File, this->actionSaveAs, "Save As", std::bind(&Pixelepsy::on_actionSave_As_triggered, this));
}

void Pixelepsy::createAction(QMenu* menu, QAction* action, const QString& text, std::function<void()> func) {
    action = new QAction(text, menu);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, func);
}

/*
 * Menu Bar - Open Button
 */
void Pixelepsy::on_actionOpen_triggered()
{
    // Opens new file - Set to automatically go to root
    QString fileName = QFileDialog::getOpenFileName(this, tr("Test"), "/", tr(" files (*.file)"));

}

/*
 * Menu Bar - Save Button
 */
void Pixelepsy::on_actionSave_triggered()
{
    // If file isn't saved yet/
    if (!fileSaved){
        // do file saving process.
    }
}

/*
 * Menu Bar - Save As Button
 */
void Pixelepsy::on_actionSave_As_triggered()
{

}

/*
 * Menu Bar - New Button
 */
void Pixelepsy::on_actionNew_triggered()
{
    get_user_dimension();
//    QMessageBox invalidInputPrompt;
//    QString tmp = QString::number(userDimension.first);
//    tmp.append(" and ");
//    tmp.append(QString::number(userDimension.second));
//    invalidInputPrompt.setText(tmp);
//    invalidInputPrompt.exec();

}

/*
 * Populate input dialog to get dimension from the user.
 */
//QPair<int, int> Pixelepsy::get_user_dimension()
void Pixelepsy::get_user_dimension()
{
    // Will store the state whether user pressed Ok button or cancel.
    bool userChoice1;
    bool userChoice2;
    bool convertState;
    int width;
    int height;
//    QPair<int, int> returnValue;

    while (true) {
        // Ask user for the input.
        QString horizontalInput = QInputDialog::getText(this,
                                                           tr("Horizontal Dimension test"),
                                                           tr("Your dimension here"),
                                                           QLineEdit::Normal,
                                                           "",
                                                           &userChoice1);
        // If user chooses to cancel, get out of the loop.
        if (!userChoice1){
            break;
        }

        width = horizontalInput.toInt(&convertState, 10);

        // If user input cannot be converted into an integer.
        if (width <= 0 || !convertState){

            //TODO Change message box text.
            QMessageBox invalidInputPrompt;
            invalidInputPrompt.setText("wrong input @ horizontal");
            invalidInputPrompt.exec();

            continue;
        } else {
//            returnValue.first = horizontalDimension;

            // Obtain vertical dimension from user
            while (true) {
                QString verticalInput = QInputDialog::getText(this,
                                                               tr("Vertical Dimension test"),
                                                               tr("Your dimension here"),
                                                               QLineEdit::Normal,
                                                               "",
                                                               &userChoice2);
                // If user chooses to cancel, get out of the loop.
                if(!userChoice2){
                    break;
                }

                height = verticalInput.toInt(&convertState, 10);

                // If user input cannot be converted into an integer.
                if (height <= 0 || !convertState){

                    //TODO: Change message box text.
                    QMessageBox invalidInputPrompt;
                    invalidInputPrompt.setText("wrong input @ vertical");
                    invalidInputPrompt.exec();

                    continue;
                } else {
//                    returnValue.second = verticalDimension;
                    break;
                }
            }
        }
    break;
    }
    QMessageBox bla;
    bla.setText("I got here");
    bla.exec();
    add_viewer(width, height);
//    return returnValue;
}

void Pixelepsy::add_viewer(int width, int height){
    Viewer* newView = new Viewer(std::make_shared<Buffer>(width, height));
    this->mdiArea->addSubWindow(newView);
    newView->show();
}

