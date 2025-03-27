# 工程说明

工程分为 3 个 Target (可通过右键菜单 `Switch Target` 进行切换), 分别是 **Debug**, **Release**, **static_lib**，其中：

- **Debug**: 可以生成具有调试信息的可执行文件，要使用 STM8-Debug 插件进行调试，请切换到此目标

- **Release**：生成 hex 文件，用于最终的成品

- **static_lib**：将标准库生成为 **不含调试信息的** 链接库，被 **Debug目标** 所使用
