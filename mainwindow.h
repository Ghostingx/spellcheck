#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QString>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool loadFile(const QString &fileName); // 加载文件
    void newFile();   // 新建操作
    bool maybeSave(); // 判断是否需要保存
    bool save();      // 保存操作
    bool saveAs();    // 另存为操作
    bool saveFile(const QString &fileName); // 保存文件
    QString spellCheck();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionnew_N_triggered();

    void on_actionsave_triggered();

    void on_actionquit_Q_triggered();

    void on_actionfile_F_triggered();

    void on_actionclose_triggered();

    void on_actionexit_triggered();

    void on_actionundo_triggered();

    void on_actioncut_triggered();

    void on_actioncopy_triggered();

    void on_actionpaste_triggered();

    void on_actionspellcheck_triggered();

private:
    Ui::MainWindow *ui;
    // 为真表示文件没有保存过，为假表示文件已经被保存过了
    bool isUntitled;
    // 保存当前文件的路径
    QString curFile;
};

#endif // MAINWINDOW_H
