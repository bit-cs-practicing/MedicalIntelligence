#include <memory>

#include <QCoreApplication>
#include <QDebug>
#include <QSettings>

// Application Layer
#include "app/appointment/appointmentappservice.h"
#include "app/appointment/appointmentappserviceimpl.h"
#include "app/attendance/attendanceappservice.h"
#include "app/attendance/attendanceappserviceimpl.h"
#include "app/case/caseappservice.h"
#include "app/case/caseappserviceimpl.h"
#include "app/chat/chatappservice.h"
#include "app/chat/chatappserviceimpl.h"
#include "app/doctor/doctorappservice.h"
#include "app/doctor/doctorappserviceimpl.h"
#include "app/patient/patientappservice.h"
#include "app/patient/patientappserviceimpl.h"
// Domain Layer
#include "domain/appointment/appointmentfactory.h"
#include "domain/appointment/appointmentrepository.h"
#include "domain/appointment/appointmentservice.h"
#include "domain/attendance/attendancefactory.h"
#include "domain/attendance/attendancerepository.h"
#include "domain/case/casefactory.h"
#include "domain/case/caserepository.h"
#include "domain/case/caseservice.h"
#include "domain/doctor/doctorfactory.h"
#include "domain/doctor/doctorrepository.h"
#include "domain/doctor/doctorservice.h"
#include "domain/leave/leaverecordfactory.h"
#include "domain/leave/leaverecordrepository.h"
#include "domain/leave/leaverecordservice.h"
#include "domain/message/messagefactory.h"
#include "domain/message/messagerepository.h"
#include "domain/message/messageservice.h"
#include "domain/patient/patientfactory.h"
#include "domain/patient/patientrepository.h"
#include "domain/patient/patientservice.h"
#include "domain/topic/topicfactory.h"
#include "domain/topic/topicrepository.h"
// Infrastructure Layer
#include "infra/data/appointment/appointmentsqliterepository.h"
#include "infra/data/attendance/attendancesqliterepository.h"
#include "infra/data/case/casesqliterepository.h"
#include "infra/data/doctor/doctorsqliterepository.h"
#include "infra/data/leave/leaverecordsqliterepository.h"
#include "infra/data/message/messagesqliterepository.h"
#include "infra/data/patient/patientsqliterepository.h"
#include "infra/data/topic/topicsqliterepository.h"
#include "infra/rpcserver/rpcdispatcher.h"
#include "infra/rpcserver/rpcserver.h"
// View Layer
#include "view/appointmenthandler.h"
#include "view/attendancehandler.h"
#include "view/casehandler.h"
#include "view/chathandler.h"
#include "view/consultationhandler.h"
#include "view/doctorhandler.h"
#include "view/patienthandler.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Settings
    QString srcPath = QCoreApplication::applicationDirPath() + "/setting.ini";
    QSettings settings(srcPath, QSettings::IniFormat);
    if (!settings.contains("database/path")) {
        settings.setValue("database/path", "main.db");
    }
    settings.beginGroup("server");
    if (!settings.contains("ip")) {
        settings.setValue("ip", "0.0.0.0");
    }
    if (!settings.contains("port")) {
        settings.setValue("port", 8080);
    }
    settings.endGroup();
    QString path = settings.value("database/path").toString();

    // Authentication
    auto credentialRegistry = std::make_shared<CredentialRegistry>();

    // Repositories
    auto appointmentRepository = std::make_shared<AppointmentSQLiteRepository>(path);
    auto attendanceRepository = std::make_shared<AttendanceSQLiteRepository>(path);
    auto caseRepository = std::make_shared<CaseSQLiteRepository>(path);
    auto doctorRepository = std::make_shared<DoctorSQLiteRepository>(path);
    auto leaveRecordRepository = std::make_shared<LeaveRecordSQLiteRepository>(path);
    auto messageRepository = std::make_shared<MessageSQLiteRepository>(path);
    auto patientRepository = std::make_shared<PatientSQLiteRepository>(path);
    auto topicRepository = std::make_shared<TopicSQLiteRepository>(path);

    // External Providers
    auto doctorAssistantProvider = nullptr;
    auto patientAssistantProvider = nullptr;

    // Domain Services
    auto appointmentFactory = std::make_shared<AppointmentFactory>(appointmentRepository, doctorRepository, leaveRecordRepository);
    auto appointmentService = std::make_shared<AppointmentService>();

    auto attendanceFactory = std::make_shared<AttendanceFactory>(attendanceRepository);

    auto caseFactory = std::make_shared<CaseFactory>();
    auto caseService = std::make_shared<CaseService>(appointmentRepository);

    auto doctorFactory = std::make_shared<DoctorFactory>(doctorRepository);
    auto doctorService = std::make_shared<DoctorService>();

    auto leaveRecordFactory = std::make_shared<LeaveRecordFactory>(leaveRecordRepository);
    auto leaveRecordService = std::make_shared<LeaveRecordService>();

    auto messageFactory = std::make_shared<MessageFactory>(topicRepository);
    auto messageService = std::make_shared<MessageService>(messageRepository);

    auto patientFactory = std::make_shared<PatientFactory>(patientRepository);
    auto patientService = std::make_shared<PatientService>();

    auto topicFactory = std::make_shared<TopicFactory>(patientRepository, doctorRepository);

    // Application Services
    auto appointmentAppService = std::make_shared<AppointmentAppServiceImpl>(
        appointmentRepository,
        appointmentFactory,
        appointmentService,
        patientRepository,
        doctorRepository,
        credentialRegistry
    );
    auto attendanceAppService = std::make_shared<AttendanceAppServiceImpl>(
        attendanceRepository,
        attendanceFactory,
        leaveRecordRepository,
        leaveRecordFactory,
        leaveRecordService,
        doctorRepository,
        credentialRegistry
    );
    auto caseAppService = std::make_shared<CaseAppServiceImpl>(
        caseRepository,
        caseFactory,
        caseService,
        appointmentRepository,
        doctorRepository,
        credentialRegistry
    );
    auto chatAppService = std::make_shared<ChatAppServiceImpl>(
        topicRepository,
        topicFactory,
        messageRepository,
        messageFactory,
        messageService,
        patientRepository,
        doctorRepository,
        credentialRegistry
    );
    auto doctorAppService = std::make_shared<DoctorAppServiceImpl>(
        doctorRepository,
        doctorFactory,
        doctorService,
        credentialRegistry
    );
    auto patientAppService = std::make_shared<PatientAppServiceImpl>(
        patientRepository,
        patientFactory,
        patientService,
        credentialRegistry
    );

    // Handlers
    auto dispatcher = std::make_unique<RpcDispatcher>();

    dispatcher->add("appointment.create", std::make_shared<AppointmentCreateHandler>(appointmentAppService));
    dispatcher->add("appointment.cancel", std::make_shared<AppointmentCancelHandler>(appointmentAppService));
    dispatcher->add("appointment.complete", std::make_shared<AppointmentCompleteHandler>(appointmentAppService));
    dispatcher->add("appointment.listByPatient", std::make_shared<AppointmentListByPatientHandler>(appointmentAppService));
    dispatcher->add("appointment.listByDoctor", std::make_shared<AppointmentListByDoctorHandler>(appointmentAppService));

    dispatcher->add("attendance.checkIn", std::make_shared<AttendanceCheckInHandler>(attendanceAppService));
    dispatcher->add("attendance.leaveRequest", std::make_shared<AttendanceLeaveRequestHandler>(attendanceAppService));
    dispatcher->add("attendance.leaveCancel", std::make_shared<AttendanceLeaveCancelHandler>(attendanceAppService));
    dispatcher->add("attendance.fetchLastRequest", std::make_shared<AttendanceFetchLastRequestHandler>(attendanceAppService));

    dispatcher->add("case.create", std::make_shared<CaseCreateHandler>(caseAppService));
    dispatcher->add("case.update", std::make_shared<CaseUpdateHandler>(caseAppService));
    dispatcher->add("case.listByPatient", std::make_shared<CaseListByPatientHandler>(caseAppService));
    dispatcher->add("case.listByDoctorAndPatient", std::make_shared<CaseListByDoctorAndPatientHandler>(caseAppService));

    dispatcher->add("chat.createTopic", std::make_shared<ChatCreateTopicHandler>(chatAppService));
    dispatcher->add("chat.listTopicsByUser", std::make_shared<ChatListTopicsByUserHandler>(chatAppService));
    dispatcher->add("chat.sendMessage", std::make_shared<ChatSendMessageHandler>(chatAppService));
    dispatcher->add("chat.fetchMessages", std::make_shared<ChatFetchMessagesHandler>(chatAppService));

    dispatcher->add("consultation.answerForDoctor", std::make_shared<ConsultationAnswerForDoctorHandler>(doctorAssistantProvider));
    dispatcher->add("consultation.answerForPatient", std::make_shared<ConsultationAnswerForPatientHandler>(patientAssistantProvider));

    dispatcher->add("doctor.signup", std::make_shared<DoctorSignupHandler>(doctorAppService));
    dispatcher->add("doctor.login", std::make_shared<DoctorLoginHandler>(doctorAppService));
    dispatcher->add("doctor.updateInfo", std::make_shared<DoctorUpdateInfoHandler>(doctorAppService));
    dispatcher->add("doctor.fetchInfo", std::make_shared<DoctorFetchInfoHandler>(doctorAppService));
    dispatcher->add("doctor.fetchAllInfo", std::make_shared<DoctorFetchAllInfoHandler>(doctorAppService));
    dispatcher->add("doctor.updatePassword", std::make_shared<DoctorUpdatePasswordHandler>(doctorAppService));

    dispatcher->add("patient.register", std::make_shared<PatientRegisterHandler>(patientAppService));
    dispatcher->add("patient.login", std::make_shared<PatientLoginHandler>(patientAppService));
    dispatcher->add("patient.updateInfo", std::make_shared<PatientUpdateInfoHandler>(patientAppService));
    dispatcher->add("patient.fetchInfo", std::make_shared<PatientFetchInfoHandler>(patientAppService));
    dispatcher->add("patient.fetchInfoByName", std::make_shared<PatientFetchInfoByNameHandler>(patientAppService));
    dispatcher->add("patient.fetchInfoByIdCard", std::make_shared<PatientFetchInfoByIdCardHandler>(patientAppService));
    dispatcher->add("patient.updatePassword", std::make_shared<PatientUpdatePasswordHandler>(patientAppService));

    // Bootstrap
    auto rpcServer = RpcServer(std::move(dispatcher));
    QString address = settings.value("ip").toString();
    int port = settings.value("port").toInt();
    if (rpcServer.listen(QHostAddress(address), port)) {
        qDebug() << "listening...";
    }

    return a.exec();
}
