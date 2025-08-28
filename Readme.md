# 环境
SDK：NCS 3.0.2 硬件： 2 个 nRF54L15 DK。 需要：nrfutil
串口日志波特率：1000000

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

## 蓝牙设备切换

处于蓝牙模式下：
按 BUTTON1 切换蓝牙设备

## 配置
关键的 conf 如下：
CONFIG_BT_ID_MAX=3

使用固定的随机静态地址：
CONFIG_BT_PRIVACY=n

一次只连接一个设备：
CONFIG_BT_MAX_CONN=1
CONFIG_BT_HIDS_MAX_CLIENT_COUNT=1

## 实现原理
使用不同的 MAC 地址，实现绑定不同的设备。这样子，就不会出现只使用一个MAC地址，被不同的主机抢着连接的情况。


### 设置 MAC 地址：
static void mac_init(void)

里面设置了三个 MAC ：mac0、mac1、mac2

### 切换 MAC
调用 usr_ble_id_set，触发 id_change_handler，在 id_change_handler 中关闭广播或者断开连接后开启广播。

在 advertising_continue 中，对 adv_param 进行复制不同的 id （和 mac_init 中的对应），启用不同的 MAC。

NCS 3.x.x 之后，开关广播、扫描、连接等操作，需要使用 work 或者线程等异步操作，不能像以前的版本那么随意调用

### 绑定后的定向广播

```
static void advertising_start(void)
{
#if CONFIG_BT_DIRECTED_ADVERTISING
	k_msgq_purge(&bonds_queue);
	bt_foreach_bond(current_id, bond_find, NULL);
#endif

	k_work_submit(&adv_work);
}
```

根据 current_id ，从对应的绑定信息中获取主机的 MAC ，进行定向广播。
