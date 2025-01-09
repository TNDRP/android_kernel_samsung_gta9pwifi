/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __LINUX_GPIO_AFC_H__
#define __LINUX_GPIO_AFC_H__

#include <linux/kernel.h>
#include <linux/module.h>

#define AFC_COMM_CNT 3
//+P240228-03997,liwei19.wt,modify,2024/03/13,slove that low battery charge mode with pd TA will reboot
#define AFC_RETRY_MAX_EARLY 20
#define AFC_RETRY_MAX_LATER 3
//-P240228-03997,liwei19.wt,modify,2024/03/13,slove that low battery charge mode with pd TA will reboot
#define VBUS_RETRY_MAX 5
#define UI 160
#define WAIT_SPING_COUNT 5
#define RECV_SPING_RETRY 5
#define SPING_MIN_UI 10
#define SPING_MAX_UI 20
#define HV_DISABLE 1
#define HV_ENABLE 0

enum {
	CHECK_AFC	= 0,
	SET_VOLTAGE 	= 1,
};

enum {
	AFC_INIT,
	NOT_AFC,
	AFC_FAIL,
	AFC_DISABLE,
	NON_AFC_MAX
};

enum {
	SPING_ERR_1	= 1,
	SPING_ERR_2,
	SPING_ERR_3,
	SPING_ERR_4,
};

/* AFC detected */
enum {
	AFC_5V = NON_AFC_MAX,
	AFC_9V,
	AFC_12V,
};

enum {
	SET_5V	= 5,
	SET_9V	= 9,
};

//+P240228-03997,liwei19.wt,modify,2024/03/13,slove that low battery charge mode with pd TA will reboot
#ifdef CONFIG_QGKI_BUILD
enum wt_probe_status {
  WT_PROBE_STATUS_START = 0,
  WT_PROBE_STATUS_TIMEOUT,
  WT_PROBE_STATUS_UNKNOW,
};
#endif
//-P240228-03997,liwei19.wt,modify,2024/03/13,slove that low battery charge mode with pd TA will reboot

struct afc_dev {
	struct platform_device *pdev;
	struct device *dev;
	
	struct class afc_class;
	struct device afc_device;
	
	struct pinctrl *pinctrl;
	struct pinctrl_state *pin_active;
	struct pinctrl_state *pin_suspend;
	//P86801AA2-3236, liwei.wt, modify, 20240401, get vbus from pmic iio
	//struct work_struct afc_set_voltage_work;
	struct delayed_work afc_set_voltage_work;
	struct iio_dev *indio_dev;
	struct iio_chan_spec *iio_chan;
	struct iio_channel *int_iio_chans;
	struct iio_channel	**gq_ext_iio_chans;
	struct iio_channel	**wtchg_ext_iio_chans;
	//P86801AA2-3236, liwei.wt, add, 20240401, get vbus from pmic iio
	struct iio_channel	**pmic_ext_iio_chans;

	int irq;
	int afc_switch_gpio;
	int afc_data_gpio;
	unsigned int vol;
	unsigned int purpose;
	unsigned int afc_cnt;
	unsigned int afc_error;
	bool afc_disable;
	bool pin_state; /* 1: active, 2: suspend */
	bool afc_used;
	int afc_type;

	spinlock_t afc_spin_lock;

//+ReqP86801AA1-3595, liyiying.wt, add, 20230801, Configure SEC_BAT_CURRENT_EVENT_HV_DISABLE
	struct device *switch_device;
//-ReqP86801AA1-3595, liyiying.wt, add, 20230801, Configure SEC_BAT_CURRENT_EVENT_HV_DISABLE

};

//+P240228-03997,liwei19.wt,modify,2024/03/13,slove that low battery charge mode with pd TA will reboot
#ifdef CONFIG_QGKI_BUILD
extern int wt_chg_probe_status;
#endif
//-P240228-03997,liwei19.wt,modify,2024/03/13,slove that low battery charge mode with pd TA will reboot

MODULE_LICENSE("GPL v2");

#endif