#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include "prism.h"
#include "manager.h"

const float move_speed = 5;
const float rotate_speed = 0.1;
const float resize_speed = 1.1;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

		void visualize_carcass();

	private slots:
		void on_actionInfo_triggered();

		void on_btnAddPrism_clicked();

		void on_btnDelPrism_clicked();

		void on_btnAddLight_clicked();

		void on_btnDelLight_clicked();

		void addPrism(Prism& prism);

		void keyPressEvent(QKeyEvent*);

		void on_listWidget_currentRowChanged(int currentRow);

		void on_listWidget_2_currentRowChanged(int currentRow);

		void on_listWidget_pressed(const QModelIndex &);

		void on_listWidget_2_pressed(const QModelIndex &);

	private:
		Ui::MainWindow *ui;
		Manager manager;
		QGraphicsScene scene;

};

#endif // MAINWINDOW_H
