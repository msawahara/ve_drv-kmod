/* SPDX-License-Identifier: GPL-2.0 */
/*
 *      pci.h
 *
 *      PCI defines and function prototypes
 *      Copyright 1994, Drew Eckhardt
 *      Copyright 1997--1999 Martin Mares <mj@ucw.cz>
 *
 *      PCI Express ASPM defines and function prototypes
 *      Copyright (c) 2007 Intel Corp.
 *              Zhang Yanmin (yanmin.zhang@intel.com)
 *              Shaohua Li (shaohua.li@intel.com)
 *
 *      For more information, please consult the following manuals (look at
 *      http://www.pcisig.com/ for how to get them):
 *
 *      PCI BIOS Specification
 *      PCI Local Bus Specification
 *      PCI to PCI Bridge Specification
 *      PCI Express Specification
 *      PCI System Design Guide
 */
/* Changes by NEC Corporation for the VE port, 2025 */

/* This file extracts and modifies parts of the Linux kernel source's
 * drivers/pci/pci.h for the VE port.
 */

#ifndef VEDRIVER_VEPCI_H
#define VEDRIVER_VEPCI_H
#include <linux/pci.h>
#include <linux/version.h>
#if (KERNEL_VERSION(5, 0, 0) <= LINUX_VERSION_CODE)
#include <linux/types.h>
#include <linux/list.h>

struct pci_cap_saved_data {
	u16 cap_nr;
	bool cap_extended;
	unsigned int size;
	u32 data[0];
};

struct pci_cap_saved_state {
	struct hlist_node next;
	struct pci_cap_saved_data cap;
};
#endif

struct pci_cap_saved_state *pci_find_saved_cap(struct pci_dev *dev, char cap);
int pci_save_state_lnkctl2_only(struct pci_dev *dev);

#endif