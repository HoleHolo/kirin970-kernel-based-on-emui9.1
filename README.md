# 华为麒麟 970 内核源代码
源代码来源：[华为开源中心](https://consumer.huawei.com/en/opensource/)  
gcc 10.3 编译器下载：[下载页面](https://developer.arm.com/downloads/-/gnu-a)
## 修改说明：
1. 根据 [官方教程](https://kernelsu.org/zh_CN/guide/how-to-integrate-for-non-gki.html "参见手动修改内核源码部分") 集成了 KernelSU
2. 根据 [Coconutat 前辈的教程](https://github.com/Coconutat/HuaweiP10-GSI-And-Modify-Or-Support-KernelSU-Tutorial/wiki/7.KernelSU%E9%80%82%E9%85%8DEMUI9%E6%88%969.1.0%E7%B3%BB%E7%BB%9F%E7%9A%84%E5%86%85%E6%A0%B8) 以及个人经验修改了内核配置文件，
作用包括：去除华为内核 Root 检测模块、去除 dm-verify、允许打包过程中修改 SELinux 状态、更换和加入其他调度器等
3. 换用 arm 提供的 gcc 10.3 工具链作为默认编译器，但是需要在 Makefile 中加入编译选项 -w 忽略编译器警告
4. kindle4jerry 大佬公开的源码的其他修改，如加入 WireGuard 等
5. 使用 Github Action 每天晚上 7 点自动化编译内核（修改自 [Coconutat 仓库的文件](https://github.com/Coconutat/android_kernel_huawei_vtr_emui9_KernelSU/tree/Github_Action_Mode/.github/workflows)）
## 常见问题：
- **KernelSU 怎么用？**
这一点请参见 KernelSU 网站上的介绍，主要流程就是：刷入内核 -> 安装管理器。 现 KernelSU 已支持更低的安卓版本，可以在官方系统上使用。 
- **内核适用于哪个版本？**  
请降级到 9.1.0.312，版本不对应时由于与 HAL 层的兼容问题手机无法连接加密的 Wi-Fi。
如果您不想降级，请考虑使用 Magisk 或尝试在扩容分区后刷入旧版本 vendor 镜像。
- **编译好的内核成品在哪下载？**  
此页面上有最新的发行版可供使用，你可以下载你所需要的版本。  
如果你可以登录 Github，并且热爱尝鲜，那么你可以在 Github 的 Actions 选项卡找到最近一次编译工作流然后下载压缩包。  
当然，如果你嫌麻烦，也可以在 [蓝奏云网盘](https://lanzoui.com/b00wzyfmj?password=7yir) （密码：7yir）下载，但是上传可能会不够及时。
- **怎样区分 permissive 和 enforcing 这两个版本呢？**  
请自行搜索。简单来说 permissive 对系统的限制更少，enforcing 更适合注重安全性的用户。
