#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
#include <QMouseEvent>
#include <QMenu>
#include <QMenuBar>
#include "Flights.h"
#include "Airlines.h"

using namespace std;


void ButtonPressed(const string &airline, QTableWidget *table, vector<Airlines::Airline> &airlines) {
    table->clearContents();
    table->setRowCount(0);
    for (const Flights::Flight &f: Flights::GetFlights(airline, airlines)) {
        cout << f.aircraft << " " << f.registration << " " << f.departure << " " << f.arrival << " " << f.fn << " "
             << f.callsign << " " << f.airline << " " << f.fd << endl;
        table->insertRow(table->rowCount());
        table->setItem(table->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(f.aircraft)));
        table->setItem(table->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(f.departure)));
        table->setItem(table->rowCount() - 1, 2, new QTableWidgetItem(QString::fromStdString(f.arrival)));
        table->setItem(table->rowCount() - 1, 3, new QTableWidgetItem(QString::fromStdString(f.fn)));
        table->setItem(table->rowCount() - 1, 4, new QTableWidgetItem(QString::fromStdString(f.callsign)));
        table->setItem(table->rowCount() - 1, 5, new QTableWidgetItem(QString::fromStdString(f.airline)));
        table->setItem(table->rowCount() - 1, 6, new QTableWidgetItem(QString::fromStdString(f.fd)));
        table->setItem(table->rowCount() - 1, 7, new QTableWidgetItem(QString::fromStdString(f.registration)));
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWidget w;
    w.resize(890, 300);
    w.setWindowTitle("Flightsearcher");
    w.show();
    auto layout1 = new QVBoxLayout(&w);
    auto table = new QTableWidget();
    table->setColumnCount(8);
    table->setHorizontalHeaderLabels(
            {"Aircraft", "Departure", "Arrival", "Flightnumber", "Callsign", "Airline", "Flight duration",
             "Registration"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    QTableWidget::connect(table, &QTableWidget::customContextMenuRequested, [=](const QPoint &pos) {
        // check if there is a selected row
        if (!table->selectedItems().empty()) {
            // create a menu
            QMenu menu(table);
            // create a menu item
            QAction *action = menu.addAction("Show Livery");
            // connect the menu item to a slot
            QObject::connect(action, &QAction::triggered, [=]() {
                QPixmap pixmap = QPixmap::fromImage(
                        Flights::GetPhoto(table->item(table->currentRow(), 7)->text().toStdString()));
                auto *widget = new QWidget();
                auto *layout = new QHBoxLayout(widget);
                auto *label = new QLabel();
                label->setPixmap(pixmap);
                layout->addWidget(label);
                widget->setWindowTitle("Livery");
                widget->show();
            });
            // show the menu
            menu.exec(table->mapToGlobal(pos));
        }
    });
    QComboBox comboBox;
    vector<Airlines::Airline> airlines = Airlines::GetAirlines();
    for (const Airlines::Airline &air: airlines) {
        comboBox.addItem(QString::fromStdString(air.Name), QString::fromStdString(air.ICAO));
    }
    QPushButton button("Suchen");
    QPushButton::connect(&button, &QPushButton::clicked, [&comboBox, &table, &airlines]() {
        ButtonPressed(comboBox.currentData().toString().toStdString(), table, airlines);
    });
    layout1->addWidget(&comboBox);
    layout1->addWidget(&button);
    layout1->addWidget(table);
    return QApplication::exec();
}


