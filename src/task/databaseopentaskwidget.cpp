#include "databaseopentaskwidget.h"
#include "databaseopentask.h"
#include "atsdb.h"
#include "dbinterface.h"
#include "dbconnection.h"
#include "logger.h"
#include "stringconv.h"
#include "global.h"

#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QStackedWidget>



#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

DatabaseOpenTaskWidget::DatabaseOpenTaskWidget(DatabaseOpenTask& task, DBInterface& db_interface, QWidget* parent)
    : TaskWidget(parent), task_(task), db_interface_(db_interface)
{
    QFont font_bold;
    font_bold.setBold(true);

    QVBoxLayout* main_layout_ = new QVBoxLayout ();

    QGroupBox *group_box = new QGroupBox(tr("Database System"));
    group_box->setFont(font_bold);
    QVBoxLayout *grplayout = new QVBoxLayout ();

    connection_stack_ = new QStackedWidget ();

    const std::map<std::string, DBConnection*> &types = db_interface_.connections();

    for (auto& con_it : types)
    {
        QRadioButton *radio = new QRadioButton(con_it.first.c_str(), this);
        connect(radio, SIGNAL(pressed()), this, SLOT(databaseTypeSelectSlot()));

        if (db_interface_.usedConnection() == con_it.first)
            radio->setChecked (true);

        grplayout->addWidget (radio);

        connection_stack_->addWidget(con_it.second->widget());
        connect(con_it.second->widget(), SIGNAL(databaseOpenedSignal()),
                this, SLOT(databaseOpenedSlot()), Qt::UniqueConnection);
    }
    group_box->setLayout(grplayout);
    main_layout_->addWidget(group_box);

    main_layout_->addStretch();

    main_layout_->addWidget(connection_stack_);

    expertModeChangedSlot();

    setLayout (main_layout_);

    if (db_interface_.usedConnection().size() > 0)
    {
        useConnection (db_interface_.usedConnection());
    }
}

DatabaseOpenTaskWidget::~DatabaseOpenTaskWidget()
{
    logdbg << "DatabaseOpenTaskWidget: destructor";

    // remove all connection widgets, are deleted by connections
    //db_interface_.deleteConnectionWidgets();

    //connection_stack_->remo

//    const std::map<std::string, DBConnection*> &types = db_interface_.connections();
//    for (auto& con_it : types)
//        connection_stack_->removeWidget(con_it.second->widget());

    while (connection_stack_->count())
        connection_stack_->removeWidget(connection_stack_->widget(0));
}

void DatabaseOpenTaskWidget::databaseTypeSelectSlot ()
{
    QRadioButton *radio = dynamic_cast <QRadioButton *> (QObject::sender());
    useConnection(radio->text().toStdString());
}

void DatabaseOpenTaskWidget::useConnection (const std::string& connection_type)
{
    db_interface_.useConnection(connection_type);

    assert (connection_stack_);

    connection_stack_->setCurrentWidget(db_interface_.connectionWidget());
}

void DatabaseOpenTaskWidget::databaseOpenedSlot ()
{
    logdbg << "DatabaseOpenTaskWidget: databaseOpenedSlot";
    emit databaseOpenedSignal();
}

void DatabaseOpenTaskWidget::expertModeChangedSlot ()
{

}
