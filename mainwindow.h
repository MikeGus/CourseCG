#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QTextStream>
#include <QPoint>
#include "prism.h"
#include "manager.h"
#include <mutex>

const double move_speed = 5;
const double rotate_speed = 0.1;
const double resize_speed = 1.1;

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
		void visualize_trass();

		void partial_render(unsigned first_line, int size);

		void draw_lights(bool check);
		void clear_all();


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

		void on_radioButton_toggled(bool checked);

		void on_radioButton_2_toggled(bool checked);

		void on_actionSave_triggered();

		void on_actionLoad_triggered();

	private:
		Ui::MainWindow *ui;
		Manager manager;
		QGraphicsScene scene;
		QPixmap* pixmap;
		std::mutex mutex;
		QPainter* painter;

		void read_point(QTextStream& stream, Point& point);
		void read_edge(QTextStream& stream, Edge& edge);
		void read_color(QTextStream& stream, QColor& color);

		void read_light(QTextStream& stream, Light& light);
		void read_prism(QTextStream& stream, Prism& prism);

		bool key_event_acceptable(QKeyEvent* e);


};

#endif // MAINWINDOW_H
