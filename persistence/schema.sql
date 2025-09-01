DROP TABLE patient;
DROP TABLE doctor;
DROP TABLE attendance;
DROP TABLE appointment;
DROP TABLE cases;
DROP TABLE leaveRecord;
DROP TABLE topic;
DROP TABLE topicParticipant;
DROP TABLE message;


CREATE TABLE patient(
    id TEXT PRIMARY KEY NOT NULL,
    name TEXT NOT NULL,
    idCard TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    gender TEXT NOT NULL,
    phone TEXT NOT NULL,
    birthday DATE,
    email TEXT,
    emergencyContact TEXT
);

CREATE TABLE doctor(
    id TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    idCard TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    employeeId TEXT,
    department TEXT,
    profile TEXT,
    photo TEXT,
    startTime DATETIME,
    endTime DATETIME,
    registrationFee REAL,
    dailyPatientLimit INTEGER
);

CREATE TABLE attendance(
    attendanceId TEXT PRIMARY KEY,
    doctorId TEXT NOT NULL,
    attendanceTime DATETIME NOT NULL
);

CREATE TABLE appointment(
    appointmentId TEXT PRIMARY KEY,
    doctorId TEXT NOT NULL,
    patientId TEXT NOT NULL,
    date DATE NOT NULL,
    startTime DATETIME NOT NULL,
    endTime DATETIME NOT NULL,
    status TEXT NOT NULL
);

CREATE TABLE cases(
    caseId TEXT PRIMARY KEY,
    appointmentId TEXT NOT NULL,
    diagnosis TEXT NOT NULL,
    prescription TEXT NOT NULL,
    advice TEXT NOT NULL,
    visitDate DATE NOT NULL
);

CREATE TABLE leaveRecord(
    leaveId TEXT PRIMARY KEY,
    doctorId TEXT NOT NULL,
    startTime DATETIME NOT NULL,
    endTime DATETIME NOT NULL,
    status TEXT NOT NULL
);

CREATE TABLE topic(
    topicId TEXT PRIMARY KEY,
    lastMessageTime DATETIME NOT NULL
);

CREATE TABLE topicParticipant(
    topicId TEXT NOT NULL,
    participantId TEXT NOT NULL,
    PRIMARY KEY (topicId, participantId)
);

CREATE TABLE message(
    messageId TEXT PRIMARY KEY,
    topicId TEXT NOT NULL,
    senderId TEXT NOT NULL,
    senderName TEXT NOT NULL,
    content TEXT NOT NULL,
    sendTime DATETIME NOT NULL
);

