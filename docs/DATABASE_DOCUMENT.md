# 数据库文档

- [患者表](##患者表)
- [医生表](##医生表)
- [预约表](##预约表)
- [考勤表](##考勤表)
- [病例表](##病例表)
- [请假记录表](##请假记录表)
- [消息表](##消息表)
- [话题表](##话题表)

---

## 患者表

表名：`patient`

键：
- `id`: 患者ID，主键，非空。
- `name`: 患者姓名，非空。
- `idCard`: 患者身份证号，非空。
- `password`: 用户密码，非空。
- `gender`: 患者性别，非空。
- `phone`: 患者联系电话，非空。
- `birthday`: 患者生日。
- `email`: 患者邮箱。
- `emergencyContact`: 紧急联系人电话。

建表：
```sqlite
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
```

## 医生表

表名：`doctor`

键：
- `id`: 医生ID，主键，非空。
- `name`: 医生姓名，非空。
- `idCard`: 医生身份证号，非空。
- `password`: 用户密码，非空。
- `employeeId`: 医生工号。
- `department`: 医生科室。
- `profile`: 医生简介。
- `photo`: 医生照片URL。
- `workSchedule`: 医生工作日程。
- `registrationFee`: 医生挂号费用。
- `dailyPatientLimit`: 医生每日患者限制。

建表：
```sqlite
CREATE TABLE doctor(
    id TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    idCard TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    employeeId TEXT,
    department TEXT,
    profile TEXT,
    photo TEXT,
    workSchedule TEXT,
    registrationFee REAL,
    dailyPatientLimit INTEGER
);
```

## 预约表

表名：`appointment`

键：
- `appointmentId`: 预约ID，主键，非空。
- `doctorId`: 医生ID，外键关联医生表，非空。
- `patientId`: 患者ID，外键关联患者表，非空。
- `date`: 预约日期，非空。
- `timeSlot`: 预约时间段，非空。
- `status`: 预约状态（SCHEDULED/COMPLETED/CANCELLED）

建表：
```sqlite
CREATE TABLE appointment(
    appointmentId TEXT PRIMARY KEY,
    doctorId TEXT NOT NULL,
    patientId TEXT NOT NULL,
    date TEXT NOT NULL,
    timeSlot TEXT NOT NULL,
    status TEXT NOT NULL,
    FOREIGN KEY (doctorId) REFERENCES doctor(id),
    FOREIGN KEY (patientId) REFERENCES patient(id)
);
```

## 考勤表

表名：`attendance`

键：
- `attendanceId`: 考勤ID，主键
- `doctorId`: 医生ID，外键关联医生表
- `attendanceTime`: 考勤时间

建表：
```sqlite
CREATE TABLE attendance(
    attendanceId TEXT PRIMARY KEY,
    doctorId TEXT NOT NULL,
    attendanceTime TEXT NOT NULL,
    FOREIGN KEY (doctorId) REFERENCES doctor(id)
);
```

## 病例表

表名：`case`

键：
- `caseId`: 病例ID，主键
- `appointmentId`: 预约ID，外键关联预约表
- `diagnosis`: 诊断信息
- `prescription`: 处方信息
- `advice`: 医嘱信息
- `visitDate`: 就诊日期

建表：
```sqlite
CREATE TABLE case(
    caseId TEXT PRIMARY KEY,
    appointmentId TEXT NOT NULL,
    diagnosis TEXT NOT NULL,
    prescription TEXT NOT NULL,
    advice TEXT NOT NULL,
    visitDate TEXT NOT NULL,
    FOREIGN KEY (appointmentId) REFERENCES appointment(appointmentId)
);
```



## 请假记录表

表名：`leave_record`

键：
- `leaveId`: 请假ID，主键
- `doctorId`: 医生ID，外键关联医生表
- `startTime`: 请假开始时间
- `endTime`: 请假结束时间
- `status`: 请假状态（ACTIVE/CANCELED）

建表：
```sqlite
CREATE TABLE leave_record(
    leaveId TEXT PRIMARY KEY,
    doctorId TEXT NOT NULL,
    startTime TEXT NOT NULL,
    endTime TEXT NOT NULL,
    status TEXT NOT NULL,
    FOREIGN KEY (doctorId) REFERENCES doctor(id)
);
```

## 消息表

表名：`message`

键：
- `messageId`: 消息ID，主键
- `topicId`: 话题ID，外键关联话题表
- `senderId`: 发送者ID
- `senderName`: 发送者姓名
- `content`: 消息内容
- `time`: 发送时间

建表：
```sqlite
CREATE TABLE message(
    messageId TEXT PRIMARY KEY,
    topicId TEXT NOT NULL,
    senderId TEXT NOT NULL,
    senderName TEXT NOT NULL,
    content TEXT NOT NULL,
    time TEXT NOT NULL,
    FOREIGN KEY (topicId) REFERENCES topic(topicId)
);
```

## 话题表

表名：`topic`

键：
- `topicId`: 话题ID，主键
- `participants`: 参与者ID列表（存储为JSON数组）

建表：
```sqlite
CREATE TABLE topic(
    topicId TEXT PRIMARY KEY,
    participants TEXT NOT NULL
);
```
