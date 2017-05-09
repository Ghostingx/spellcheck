#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    // 判断用户名和密码是否正确，
    // 弹出警告对话框
//    if(ui->usrLineEdit->text() == tr("ghost") &&
 //          ui->pwdLineEdit->text() == tr("123456"))
  //      {
           accept();
 //       } else {
  //         QMessageBox::warning(this, tr("Waring"),
  //                               tr("user name or password error!"),
  //                               QMessageBox::Yes);
  //      }
}

void LoginDialog::on_exitBtn_clicked()
{

}
