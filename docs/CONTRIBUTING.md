# Contributing

## Fork & Clone 仓库

1. Fork 仓库：

   - 访问 [https://github.com/bit-cs-practicing/MedicalIntelligence](https://github.com/bit-cs-practicing/MedicalIntelligence.git)。
   - 点击右上角的 Fork 按钮，将仓库复制到您的 GitHub 账户中。

2. Clone 仓库：

   - 在您的 GitHub 账户中打开您刚才 Fork 的仓库。
   - 点击绿色的 Code 按钮，复制仓库的 URL（HTTPS 或 SSH）。
   - 在本地使用以下命令克隆仓库：

   ```bash
   git clone https://github.com/your-username/MedicalIntelligence.git
   ```

   将 `your-username` 替换为您的 GitHub 用户名。

## 配置开发环境

1. 安装 Qt 和 Qt Creator：

   - 本项目使用 Qt 5.12.8 版本，请确保已安装 [Qt 5.12.8](https://www.qt.io/download)。
   - 安装 [Qt Creator](https://www.qt.io/qt-creator) 来作为 IDE 开发工具。

2. 安装 CMake：

   - 该项目使用 CMake 3.10.0+ 进行构建。请确保您安装了 CMake 3.10.0 或更高版本。
   - 您可以从 [CMake 官网](https://cmake.org/download/) 下载并安装合适的版本。

3. 配置 Qt Creator：

   - 打开 Qt Creator，并确保您已正确设置了 Qt 5.12.8 和 CMake 3.10.0+ 环境。
   - 在 Qt Creator 中，选择 工具 -> 选项 -> 构建和运行，配置 Qt 版本和 CMake 的路径。

4. 安装依赖项：

   - 如果项目使用了外部库或依赖，请按照项目文档中提供的说明安装这些依赖项。
   - 确保您能够成功构建项目，验证环境配置是否成功。

## 同步更新代码

在开始工作之前，确保您的本地仓库是最新的。通过以下步骤同步您的仓库：

1. 设置上游仓库：
   如果您还没有设置上游仓库（`upstream`），请运行以下命令来添加它：

   ```bash
   git remote add upstream https://github.com/bit-cs-practicing/MedicalIntelligence.git
   ```

2. 直接将 `master` 分支跟踪 `upstream/master`：
   为了方便以后直接同步代码更新，设置您的本地 `master` 分支跟踪远程 `upstream/master`：

   ```bash
   git checkout master
   git branch --set-upstream-to=upstream/master master
   ```

3. 同步最新的更改：
   获取并合并 `upstream/master` 上的更改：

   ```bash
   git pull
   ```

## 创建新分支

1. 创建新的分支：
   为了更好地管理您的更改，创建一个新的分支并开始开发。分支名称应采用以下格式：

   ```plain
   <github-username>/<description>
   ```

   例如，`starryreverie/add-login-feature` 或 `janedoe/fix-crash-on-startup`。

   使用以下命令创建新的分支并切换到该分支：

   ```bash
   git switch -C starryreverie/add-login-feature
   ```

2. 进行更改：
   在新分支上进行代码更改，并确保更改不会破坏现有功能。

## 提交 Pull Request

1. 提交更改：
   在完成更改后，使用以下命令将更改提交到本地分支：

   ```bash
   git add .
   git commit -m "描述你的更改"
   ```

2. 推送到您的 GitHub 仓库：
   将您的更改推送到您的 GitHub 仓库：

   ```bash
   git push origin starryreverie/add-login-feature
   ```

3. 创建 Pull Request：

   - 访问您 GitHub 上的仓库页面。
   - 点击 Compare & Pull Request 按钮。
   - 选择将您的分支合并到 `upstream/master`。
   - 在描述中详细说明您的更改。

4. PR 审核：

   - 一旦您提交了 Pull Request，项目维护者将对其进行评审。如果需要修改，他们会要求您进行更改。
   - 一旦您的 PR 被接受，它将被合并到 `master` 分支。

## 注意事项

- 请遵循项目的编码规范和[代码风格](./CODING_STYLE.md)，确保您的更改与现有代码一致。
- 确保提交的信息简洁而有意义，描述清楚所做的更改及其原因。
