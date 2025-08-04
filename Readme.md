# 环境
SDK：NCS 3.0.2 硬件： 2 个 nRF54L15 DK。 需要：nrfutil

# 烧录

## 2.4G 

通过 UICR 写入特定值，区分 TX/RX

一个 DK 的 NRF_UICR->OTP[0] 写入 0xABABA，表示作为 TX。

可使用 rx_flash.bat/tx_flash.bat 。

# 说明

|BUTTON|功能||
|---|---|---|
|0|切换 2.4G 模式||
|1|切换 BLE 模式||
|2|鼠标左右移动||
|3|鼠标上下移动||

> 切换模式使用复位的方式