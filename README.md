# 华为麒麟 970 内核源代码
源代码来源：[华为开源中心](https://consumer.huawei.com/en/opensource/)  
gcc 10.3 编译器下载：[下载页面](https://developer.arm.com/downloads/-/gnu-a)
## 修改说明：
1. 根据 [官方教程](https://kernelsu.org/zh_CN/guide/how-to-integrate-for-non-gki.html "参见手动修改内核源码部分") 集成了 KernelSU
2. 根据 [Coconutat 前辈的教程](https://github.com/Coconutat/HuaweiP10-GSI-And-Modify-Or-Support-KernelSU-Tutorial/wiki/7.KernelSU%E9%80%82%E9%85%8DEMUI9%E6%88%969.1.0%E7%B3%BB%E7%BB%9F%E7%9A%84%E5%86%85%E6%A0%B8) 以及个人经验修改了内核配置文件，
作用包括：去除华为内核 Root 检测模块、去除 dm-verify、允许打包过程中修改 SELinux 状态、更换和加入其他调度器等
3. 换用 arm 提供的 gcc 10.3 工具链作为默认编译器，但是需要在 Makefile 中加入编译选项 -w 忽略编译器警告
4. kindle4jerry 大佬公开的源码的其他修改，如加入 WireGuard 等
5. 尝试使用 Github Action 自动化编译内核（修改自 [Coconutat 仓库的文件](https://github.com/Coconutat/android_kernel_huawei_vtr_emui9_KernelSU/tree/Github_Action_Mode/.github/workflows)）
