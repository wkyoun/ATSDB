#include "createartasassociationstask.h"
#include "createartasassociationstaskwidget.h"
#include "atsdb.h"
#include "dbinterface.h"
#include "taskmanager.h"
#include "jobmanager.h"

CreateARTASAssociationsTask::CreateARTASAssociationsTask(const std::string& class_id, const std::string& instance_id,
                                                         TaskManager* task_manager)
    : Configurable (class_id, instance_id, task_manager)
{

}

CreateARTASAssociationsTask::~CreateARTASAssociationsTask()
{
    if (widget_)
    {
        delete widget_;
        widget_ = nullptr;
    }

}

CreateARTASAssociationsTaskWidget* CreateARTASAssociationsTask::widget()
{
    if (!widget_)
    {
        widget_ = new CreateARTASAssociationsTaskWidget (*this);
    }

    assert (widget_);
    return widget_;
}

void CreateARTASAssociationsTask::run ()
{
    create_job_ = std::make_shared<CreateARTASAssociationsJob> (ATSDB::instance().interface());

    connect (create_job_.get(), &CreateARTASAssociationsJob::obsoleteSignal,
             this, &CreateARTASAssociationsTask::createDoneSlot, Qt::QueuedConnection);

    connect (create_job_.get(), &CreateARTASAssociationsJob::doneSignal,
             this, &CreateARTASAssociationsTask::createObsoleteSlot, Qt::QueuedConnection);

    JobManager::instance().addDBJob(create_job_);
}


void CreateARTASAssociationsTask::createDoneSlot ()
{
    loginf << "CreateARTASAssociationsTask: createDoneSlot";
}

void CreateARTASAssociationsTask::createObsoleteSlot ()
{

}
