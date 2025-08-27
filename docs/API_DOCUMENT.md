# API 文档

- [患者用户管理模块](#患者用户管理模块)
  - [patient.register](#patientregister)
  - [patient.login](#patientlogin)
  - [patient.fetchInfo](#patientfetchinfo)
  - [patient.updateInfo](#patientupdateinfo)
  - [patient.updatePassword](#patientupdatepassword)
- [医生用户管理模块](#医生用户管理模块)
  - [doctor.register](#doctorregister)
  - [doctor.login](#doctorlogin)
  - [doctor.fetchInfo](#doctorfetchinfo)
  - [doctor.updateInfo](#doctorupdateinfo)
  - [doctor.updatePassword](#doctorupdatepassword)
- [预约管理模块](#预约管理模块)
  - [appointment.create](#appointmentcreate)
  - [appointment.cancel](#appointmentcancel)
  - [appointment.complete](#appointmentcomplete)
  - [appointment.listByPatient](#appointmentlistbypatient)
  - [appointment.listByDoctor](#appointmentlistbydoctor)
- [病例管理模块](#病例管理模块)
  - [case.create](#casecreate)
  - [case.update](#caseupdate)
  - [case.listByPatient](#caselistbypatient)
  - [case.listByDoctorAndPatient](#caselistbydoctorandpatient)
- [考勤管理模块](#考勤管理模块)
  - [attendance.checkIn](#attendancecheckin)
  - [attendance.leaveRequest](#attendanceleaverequest)
  - [attendance.leaveCancel](#attendanceleavecancel)
- [医患沟通模块](#医患沟通模块)
  - [chat.createTopic](#chatcreatetopic)
  - [chat.listTopicsByUser](#chatlisttopicsbyuser)
  - [chat.sendMessage](#chatsendmessage)
  - [chat.fetchMessages](#chatfetchmessages)

## 患者用户管理模块

### `patient.register`

#### 功能描述

患者注册。  
注册时必须进行以下检查：

- 姓名、密码、身份证、手机号字段不能为空，且格式必须正确  
- 注册时若身份证已被注册，则返回身份证重复失败  

#### 请求格式

```json
{
  "endpoint": "patient.register",
  "credential": "",
  "data": {
    "name": "张三",
    "password": "123456",
    "gender": "male",
    "idCard": "123456789012345678",
    "phone": "13800138000",
    "birthday": "1990-01-01",
    "email": "test@example.com",
    "emergencyContact": "13800138001"
  }
}
```

#### 请求字段

- `name (string)` 姓名
- `password (string)` 密码
- `gender (string)` 性别，可选项 `male | female`
- `idCard (string)` 身份证
- `phone (string)` 手机号
- `birthday (string, optional)` 出生日期，格式 `yyyy-MM-dd`
- `email (string, optional)` 邮箱
- `emergencyContact (string, optional)` 紧急联系人电话

#### 响应格式

```json
{
  "success": true,
  "message": "注册成功",
  "data": {
    "userId": "uuid"
  }
}
```

#### 响应字段

- `userId (string)` 用户唯一标识

---

### `patient.login`

#### 功能描述

患者登录。
登录时必须进行以下检查：

- 登录时若身份证未注册，则返回用户不存在失败
- 登录时若密码不正确，则返回密码错误失败

#### 请求格式

```json
{
  "endpoint": "patient.login",
  "credential": "",
  "data": {
    "idCard": "123456789012345678",
    "password": "123456"
  }
}
```

#### 请求字段

- `idCard (string)` 身份证
- `password (string)` 密码

#### 响应格式

```json
{
  "success": true,
  "message": "登录成功",
  "data": {
    "credential": "auth-token"
  }
}
```

#### 响应字段

- `credential (string)` 登录凭证

---

### `patient.updateInfo`

#### 功能描述

修改患者信息。
修改时必须进行以下检查：

- 姓名、手机号等字段必须符合格式要求

#### 请求格式

```json
{
  "endpoint": "patient.updateInfo",
  "credential": "auth-token",
  "data": {
    "name": "张三",
    "phone": "13900139000",
    "gender": "male",
    "birthday": "1991-01-01",
    "email": "new@example.com",
    "emergencyContact": "13900139001"
  }
}
```

#### 请求字段

- `name (string, optional)` 姓名
- `phone (string, optional)` 手机号
- `birthday (string, optional)` 出生日期，格式 `yyyy-MM-dd`
- `gender (string, optional)` 性别，可选项 `male | female`
- `email (string, optional)` 邮箱
- `emergencyContact (string, optional)` 紧急联系人电话

#### 响应格式

```json
{
  "success": true,
  "message": "修改成功",
  "data": {}
}
```

#### 响应字段

- 无额外字段

---

### `patient.fetchInfo`

#### 功能描述

获取患者的基本信息。

- 返回患者的姓名、性别、手机号、生日、邮箱和紧急联系人等信息。

#### 请求格式

```json
{
  "endpoint": "patient.fetchInfo",
  "credential": "auth-token",
  "data": {}
}
```

#### 请求字段

- 无额外字段

#### 响应格式

```json
{
  "success": true,
  "message": "获取成功",
  "data": {
    "name": "张三",
    "phone": "13900139000",
    "birthday": "1991-01-01",
    "gender": "male",
    "email": "example@example.com",
    "emergencyContact": "13900139001"
  }
}
```

#### 响应字段

- `name (string)` 姓名
- `phone (string)` 手机号
- `birthday (string)` 出生日期，格式 `yyyy-MM-dd`
- `gender (string)` 性别，格式 `male | female`
- `email (string)` 邮箱
- `emergencyContact (string)` 紧急联系人电话

---

### `patient.updatePassword`

#### 功能描述

修改患者密码。
修改时必须进行以下检查：

- 修改时若原密码不正确，则返回原密码错误失败

#### 请求格式

```json
{
  "endpoint": "patient.updatePassword",
  "credential": "auth-token",
  "data": {
    "oldPassword": "123456",
    "newPassword": "abcdef"
  }
}
```

#### 请求字段

- `oldPassword (string)` 原密码
- `newPassword (string)` 新密码

#### 响应格式

```json
{
  "success": true,
  "message": "修改密码成功",
  "data": {}
}
```

#### 响应字段

- 无额外字段

---

## 医生用户管理模块

### `doctor.register`

#### 功能描述

医生注册。注册时必须进行以下检查：  

- 姓名、密码、身份证字段不能为空，且格式必须正确  
- 注册时若身份证已被注册，则返回身份证重复失败  

#### 请求格式

```json
{
  "endpoint": "doctor.register",
  "credential": "",
  "data": {
    "name": "李四",
    "password": "123456",
    "idCard": "123456789012345678"
  }
}
```

#### 请求字段

- `name (string)` 姓名
- `password (string)` 密码
- `idCard (string)` 身份证

#### 响应格式

```json
{
  "success": true,
  "message": "注册成功",
  "data": {
    "userId": "uuid"
  }
}
```

#### 响应字段

- `userId (string)` 医生唯一标识

---

### `doctor.login`

#### 功能描述

医生登录。
登录时必须进行以下检查：

- 登录时若身份证未注册，则返回用户不存在失败
- 登录时若密码不正确，则返回密码错误失败

#### 请求格式

```json
{
  "endpoint": "doctor.login",
  "credential": "",
  "data": {
    "idCard": "123456789012345678",
    "password": "123456"
  }
}
```

#### 请求字段

- `idCard (string)` 身份证
- `password (string)` 密码

#### 响应格式

```json
{
  "success": true,
  "message": "登录成功",
  "data": {
    "credential": "auth-token"
  }
}
```

#### 响应字段

- `credential (string)` 登录凭证

---

### `doctor.updateInfo`

#### 功能描述

修改医生信息。
修改时必须进行以下检查：

- 工号、科室、个人资料、照片、上班时间、挂号费用、单日患者上限字段必须符合格式要求

#### 请求格式

```json
{
  "endpoint": "doctor.updateInfo",
  "credential": "auth-token",
  "data": {
    "employeeId": "D001",
    "department": "内科",
    "profile": "副主任医师，从业10年",
    "photo": "http://example.com/photo.jpg",
    "workSchedule": "Mon-Fri 9:00-17:00",
    "registrationFee": 50,
    "dailyPatientLimit": 30
  }
}
```

#### 请求字段

- `employeeId (string, optional)` 工号
- `department (string, optional)` 科室
- `profile (string, optional)` 个人资料
- `photo (string, optional)` 照片 URL
- `workSchedule (string, optional)` 上班时间，格式由系统定义
- `registrationFee (number, optional)` 挂号费用
- `dailyPatientLimit (number, optional)` 单日患者上限

#### 响应格式

```json
{
  "success": true,
  "message": "修改成功",
  "data": {}
}
```

#### 响应字段

- 无额外字段

---

### `doctor.fetchInfo`

#### 功能描述

获取医生的基本信息。

- 返回医生的工号、科室、个人资料、照片、上班时间、挂号费用、单日患者上限等信息。

#### 请求格式

```json
{
  "endpoint": "doctor.fetchInfo",
  "credential": "auth-token",
  "data": {}
}
```

#### 请求字段

- 无额外字段

#### 响应格式

```json
{
  "success": true,
  "message": "获取成功",
  "data": {
    "employeeId": "D001",
    "department": "内科",
    "profile": "副主任医师，从业10年",
    "photo": "http://example.com/photo.jpg",
    "workSchedule": "Mon-Fri 9:00-17:00",
    "registrationFee": 50,
    "dailyPatientLimit": 30
  }
}
```

#### 响应字段

- `employeeId (string)` 工号
- `department (string)` 科室
- `profile (string)` 个人资料
- `photo (string)` 照片 URL
- `workSchedule (string)` 上班时间，格式由系统定义
- `registrationFee (number)` 挂号费用
- `dailyPatientLimit (number)` 单日患者上限

---

### `doctor.updatePassword`

#### 功能描述

修改医生密码。修改时必须进行以下检查：

- 修改时若原密码不正确，则返回原密码错误失败

#### 请求格式

```json
{
  "endpoint": "doctor.updatePassword",
  "credential": "auth-token",
  "data": {
    "oldPassword": "123456",
    "newPassword": "abcdef"
  }
}
```

#### 请求字段

- `oldPassword (string)` 原密码
- `newPassword (string)` 新密码

#### 响应格式

```json
{
  "success": true,
  "message": "修改密码成功",
  "data": {}
}
```

#### 响应字段

- 无额外字段

---

## 预约管理模块

### `appointment.create`

#### 功能描述

患者发起预约。

预约时必须进行以下检查：

- 若预约医生正在请假，则返回医生不在岗失败  
- 若预约日期超出可预约时间范围，则返回超出预约范围失败  
- 若该时间段人数已达到上限，则返回人数已满失败  
- 若患者已有相同时间段的预约，则返回预约冲突失败  

#### 请求格式

```json
{
  "endpoint": "appointment.create",
  "credential": "patient-auth-token",
  "data": {
    "userId": "D001",
    "date": "2025-09-01",
    "timeSlot": "09:00-10:00"
  }
}
```

#### 请求字段

- `userId (string)` 医生唯一标识
- `date (string)` 预约日期，格式 `yyyy-MM-dd`
- `timeSlot (string)` 预约时间段，格式 `HH:mm-HH:mm`

#### 响应格式

```json
{
  "success": true,
  "message": "预约成功",
  "data": {
    "appointmentId": "A123456"
  }
}
```

#### 响应字段

- `appointmentId (string)` 预约唯一标识

---

### `appointment.cancel`

#### 功能描述

患者取消预约。取消时必须进行以下检查：

- 若预约 ID 不存在，则返回预约不存在失败
- 若预约与患者凭证不匹配，则返回无权限取消失败
- 若预约已过期或当天预约，则返回不可取消失败
- 若预约已完成，则返回不可取消失败

#### 请求格式

```json
{
  "endpoint": "appointment.cancel",
  "credential": "patient-auth-token",
  "data": {
    "appointmentId": "A123456"
  }
}
```

#### 请求字段

- `appointmentId (string)` 预约唯一标识

#### 响应格式

```json
{
  "success": true,
  "message": "取消成功",
  "data": {}
}
```

#### 响应字段

- 无额外字段

---

### `appointment.complete`

#### 功能描述

医生完成预约。完成时必须进行以下检查：

- 若预约 ID 不存在，则返回预约不存在失败
- 若预约与医生凭证不匹配，则返回无权限操作失败
- 若预约不属于当前时间段，则返回时间不符失败
- 若预约已完成，则返回重复完成失败

#### 请求格式

```json
{
  "endpoint": "appointment.complete",
  "credential": "doctor-auth-token",
  "data": {
    "appointmentId": "A123456"
  }
}
```

#### 请求字段

- `appointmentId (string)` 预约唯一标识

#### 响应格式

```json
{
  "success": true,
  "message": "预约已完成",
  "data": {}
}
```

#### 响应字段

- 无额外字段

---

### `appointment.listByPatient`

#### 功能描述

患者查询所有预约。查询时必须进行以下检查：

- 凭证必须为有效的患者凭证

#### 请求格式

```json
{
  "endpoint": "appointment.listByPatient",
  "credential": "patient-auth-token",
  "data": {}
}
```

#### 请求字段

- 无

#### 响应格式

```json
{
  "success": true,
  "message": "查询成功",
  "data": {
    "appointments": [
      {
        "appointmentId": "A123456",
        "doctorId": "D001",
        "date": "2025-09-01",
        "timeSlot": "09:00-10:00",
        "status": "scheduled"
      }
    ]
  }
}
```

#### 响应字段

- `appointments (array)` 患者的预约列表

  - `appointmentId (string)` 预约唯一标识
  - `doctorId (string)` 医生唯一标识
  - `date (string)` 预约日期
  - `timeSlot (string)` 预约时间段
  - `status (string)` 预约状态（`scheduled` | `completed` | `cancelled`）

---

### `appointment.listByDoctor`

#### 功能描述

医生查询所有分配给自己的预约。查询时必须进行以下检查：

- 凭证必须为有效的医生凭证

#### 请求格式

```json
{
  "endpoint": "appointment.listByDoctor",
  "credential": "doctor-auth-token",
  "data": {}
}
```

#### 请求字段

- 无

#### 响应格式

```json
{
  "success": true,
  "message": "查询成功",
  "data": {
    "appointments": [
      {
        "appointmentId": "A123456",
        "patientId": "P001",
        "date": "2025-09-01",
        "timeSlot": "09:00-10:00",
        "status": "scheduled"
      }
    ]
  }
}
```

#### 响应字段

- `appointments (array)` 医生的预约列表

  - `appointmentId (string)` 预约唯一标识
  - `patientId (string)` 患者唯一标识
  - `date (string)` 预约日期
  - `timeSlot (string)` 预约时间段
  - `status (string)` 预约状态（`scheduled` | `completed` | `cancelled`）

---

## 病例管理模块

### `case.create`

#### 功能描述

医生创建病例项。创建时必须进行以下检查：  

- 若预约 ID 不存在，则返回预约不存在失败  
- 若医生凭证与预约 ID 不匹配，则返回无权限创建失败  
- 若预约不属于当前时间段，则返回预约时间不符失败  
- 若预约已完成，则返回不可创建失败  
- 若输入的诊断结果、处方、医嘱不符合格式，则返回信息格式错误失败  
- 创建成功的病例记录当前日期为就诊日期 `visitDate`

#### 请求格式

```json
{
  "endpoint": "case.create",
  "credential": "doctor-auth-token",
  "data": {
    "appointmentId": "A123456",
    "diagnosis": "上呼吸道感染",
    "prescription": "阿莫西林胶囊 500mg 每日三次",
    "advice": "多饮水，注意休息"
  }
}
```

#### 请求字段

- `appointmentId (string)` 预约唯一标识
- `diagnosis (string)` 诊断结果
- `prescription (string)` 处方
- `advice (string)` 医嘱

#### 响应格式

```json
{
  "success": true,
  "message": "病例创建成功",
  "data": {
    "caseId": "C987654"
  }
}
```

#### 响应字段

- `caseId (string)` 病例项唯一标识

---

### `case.update`

#### 功能描述

医生修改病例项。修改时必须进行以下检查：

- 若病例项 ID 不存在，则返回病例不存在失败
- 若医生凭证与病例项 ID 不匹配，则返回无权限修改失败
- 若输入的诊断结果、处方、医嘱不符合格式，则返回信息格式错误失败

#### 请求格式

```json
{
  "endpoint": "case.update",
  "credential": "doctor-auth-token",
  "data": {
    "caseId": "C987654",
    "diagnosis": "慢性支气管炎",
    "prescription": "氨溴索片 30mg 每日两次",
    "advice": "避免受凉，按时复诊"
  }
}
```

#### 请求字段

- `caseId (string)` 病例项唯一标识
- `diagnosis (string)` 诊断结果
- `prescription (string)` 处方
- `advice (string)` 医嘱

#### 响应格式

```json
{
  "success": true,
  "message": "病例修改成功",
  "data": {}
}
```

#### 响应字段

- 无额外字段

---

### `case.listByPatient`

#### 功能描述

患者获取自己的病例列表。

- 患者身份通过 `credential` 验证，系统根据患者 ID 查询其所有病例。
- 返回的病例包括病例 ID、就诊日期、诊断结果、处方和医嘱等基本信息。

#### 请求格式

```json
{
  "endpoint": "case.listByPatient",
  "credential": "patient-auth-token",
  "data": {}
}
```

#### 请求字段

- 无额外字段

#### 响应格式

```json
{
  "success": true,
  "message": "获取成功",
  "data": [
    {
      "caseId": "C987654",
      "visitDate": "2023-08-15",
      "diagnosis": "慢性支气管炎",
      "prescription": "氨溴索片 30mg 每日两次",
      "advice": "避免受凉，按时复诊"
    },
    {
      "caseId": "C123456",
      "visitDate": "2023-05-20",
      "diagnosis": "上呼吸道感染",
      "prescription": "对乙酰氨基酚 500mg 每日三次",
      "advice": "多喝水，注意休息"
    }
  ]
}
```

#### 响应字段

- `caseId (string)` 病例项唯一标识
- `visitDate (string)` 就诊日期，格式 `yyyy-MM-dd`
- `diagnosis (string)` 诊断结果
- `prescription (string)` 处方
- `advice (string)` 医嘱

---

### `case.listByDoctorAndPatient`

#### 功能描述

医生获取自己诊断过的某个患者的所有病例。

- 医生身份通过 `credential` 验证，系统根据医生 ID 和指定患者 ID 查询该医生为该患者诊断的病例。
- 若患者 ID 不存在，则返回失败。
- 若医生未诊断过该患者，则返回空列表。
- 返回的病例包括病例 ID、就诊日期、诊断结果、处方和医嘱等基本信息。

#### 请求格式

```json
{
  "endpoint": "case.listByDoctorAndPatient",
  "credential": "doctor-auth-token",
  "data": {
    "patientId": "P123456"
  }
}
```

#### 请求字段

- `patientId (string)` 患者唯一标识

#### 响应格式

```json
{
  "success": true,
  "message": "获取成功",
  "data": [
    {
      "caseId": "C987654",
      "visitDate": "2023-08-15",
      "diagnosis": "慢性支气管炎",
      "prescription": "氨溴索片 30mg 每日两次",
      "advice": "避免受凉，按时复诊"
    },
    {
      "caseId": "C123456",
      "visitDate": "2023-05-20",
      "diagnosis": "上呼吸道感染",
      "prescription": "对乙酰氨基酚 500mg 每日三次",
      "advice": "多喝水，注意休息"
    }
  ]
}
```

#### 响应字段

- `caseId (string)` 病例项唯一标识
- `visitDate (string)` 就诊日期，格式 `yyyy-MM-dd`
- `diagnosis (string)` 诊断结果
- `prescription (string)` 处方
- `advice (string)` 医嘱

---

## 考勤管理模块

### `attendance.checkIn`

#### 功能描述

医生打卡创建上班记录。打卡时必须进行以下检查：  

- 若医生凭证不存在，则返回无效凭证失败  
- 若当前时间不在医生的上班时间范围内，则返回不在工作时间失败  
- 若当前时间段已存在打卡记录，则返回重复打卡失败  

#### 请求格式

```json
{
  "endpoint": "attendance.checkIn",
  "credential": "doctor-auth-token",
  "data": {}
}
```

#### 请求字段

- 无

#### 响应格式

```json
{
  "success": true,
  "message": "打卡成功",
  "data": {
    "attendanceId": "AT123456",
    "time": "2025-09-01T09:00:00"
  }
}
```

#### 响应字段

- `attendanceId (string)` 打卡记录唯一标识
- `time (string)` 打卡时间，格式 `yyyy-MM-ddTHH:mm:ss`

---

### `attendance.leaveRequest`

#### 功能描述

医生提交请假申请。请假时必须进行以下检查：

- 若医生已有未销假的请假记录，则返回已有未销假失败
- 若请假开始时间或结束时间格式不正确，则返回时间格式错误失败
- 若请假开始时间不小于结束时间，则返回时间区间错误失败

#### 请求格式

```json
{
  "endpoint": "attendance.leaveRequest",
  "credential": "doctor-auth-token",
  "data": {
    "startTime": "2025-09-02T09:00:00",
    "endTime": "2025-09-05T17:00:00"
  }
}
```

#### 请求字段

- `startTime (string)` 请假开始时间，格式 `yyyy-MM-ddTHH:mm:ss`
- `endTime (string)` 请假结束时间，格式 `yyyy-MM-ddTHH:mm:ss`

#### 响应格式

```json
{
  "success": true,
  "message": "请假申请成功",
  "data": {
    "leaveId": "L123456"
  }
}
```

#### 响应字段

- `leaveId (string)` 请假记录唯一标识

---

### `attendance.leaveCancel`

#### 功能描述

医生销假。销假时必须进行以下检查：

- 若请假 ID 不存在，则返回请假不存在失败
- 若医生凭证与请假 ID 不匹配，则返回无权限销假失败
- 若请假记录已销假，则返回重复销假失败

#### 请求格式

```json
{
  "endpoint": "attendance.leaveCancel",
  "credential": "doctor-auth-token",
  "data": {
    "leaveId": "L123456"
  }
}
```

#### 请求字段

- `leaveId (string)` 请假记录唯一标识

#### 响应格式

```json
{
  "success": true,
  "message": "销假成功",
  "data": {}
}
```

#### 响应字段

- 无额外字段

---

## 医患沟通模块

### `chat.createTopic`

#### 功能描述

创建一个新的医患沟通话题。创建时必须进行以下检查：

- 初始用户列表人数必须大于等于 2，否则返回人数不足失败  
- 初始用户列表中必须有且仅有一位患者，否则返回患者人数错误失败  

#### 请求格式

```json
{
  "endpoint": "chat.createTopic",
  "credential": "doctor-auth-token",
  "data": {
    "participants": ["doctor-uuid", "patient-uuid"]
  }
}
```

#### 请求字段

- `participants (array[string])` 初始用户 ID 列表

#### 响应格式

```json
{
  "success": true,
  "message": "话题创建成功",
  "data": {
    "topicId": "T123456"
  }
}
```

#### 响应字段

- `topicId (string)` 话题唯一标识

---

### `chat.listTopicsByUser`

#### 功能描述

用户查询自己关联的所有话题，按时间顺序返回。查询时必须进行以下检查：

- 凭证必须为有效的用户凭证

#### 请求格式

```json
{
  "endpoint": "chat.listTopicsByUser",
  "credential": "user-auth-token",
  "data": {}
}
```

#### 请求字段

- 无

#### 响应格式

```json
{
  "success": true,
  "message": "查询成功",
  "data": {
    "topics": [
      {
        "topicId": "T123456",
        "lastMessageTime": "2025-09-01T10:00:00"
      }
    ]
  }
}
```

#### 响应字段

- `topics (array)` 用户关联的话题列表

  - `topicId (string)` 话题唯一标识
  - `lastMessageTime (string)` 最近消息时间，格式 `yyyy-MM-ddTHH:mm:ss`

---

### `chat.sendMessage`

#### 功能描述

用户在话题中发送消息。
发送时必须进行以下检查：

- 若用户不在话题参与者列表中，则返回无权限发送失败
- 若消息内容为空或格式不正确，则返回消息格式错误失败

#### 请求格式

```json
{
  "endpoint": "chat.sendMessage",
  "credential": "user-auth-token",
  "data": {
    "topicId": "T123456",
    "content": "您好，请问我挂号的时间能改吗？"
  }
}
```

#### 请求字段

- `topicId (string)` 话题唯一标识
- `content (string)` 消息内容

#### 响应格式

```json
{
  "success": true,
  "message": "消息发送成功",
  "data": {
    "messageId": "M987654",
    "time": "2025-09-01T10:05:00"
  }
}
```

#### 响应字段

- `messageId (string)` 消息唯一标识
- `time (string)` 消息发送时间，格式 `yyyy-MM-ddTHH:mm:ss`

---

### `chat.fetchMessages`

#### 功能描述

用户拉取话题中的消息。
拉取时必须进行以下检查：

- 若用户不在话题参与者列表中，则返回无权限拉取失败
- 若请求条数范围无效（如负数），则返回参数错误失败

#### 请求格式

```json
{
  "endpoint": "chat.fetchMessages",
  "credential": "user-auth-token",
  "data": {
    "topicId": "T123456",
    "start": 10,
    "limit": 1
  }
}
```

#### 请求字段

- `topicId (string)` 话题唯一标识
- `start (number)` 拉取消息的起始偏移
- `limit (number)` 拉取消息的最大条数

#### 响应格式

```json
{
  "success": true,
  "message": "拉取成功",
  "data": {
    "messages": [
      {
        "messageId": "M987654",
        "senderId": "doctor-uuid",
        "content": "您好，您可以改预约时间。",
        "time": "2025-09-01T10:10:00"
      }
    ]
  }
}
```

#### 响应字段

- `messages (array)` 消息列表

  - `messageId (string)` 消息唯一标识
  - `senderId (string)` 发送者唯一标识
  - `content (string)` 消息内容
  - `time (string)` 消息时间，格式 `yyyy-MM-ddTHH:mm:ss`
