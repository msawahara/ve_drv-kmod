// SPDX-License-Identifier: GPL-2.0
/*
 * PCI Bus Services, see include/linux/pci.h for further explanation.
 *
 * Copyright 1993 -- 1997 Drew Eckhardt, Frederic Potter,
 * David Mosberger-Tang
 *
 * Copyright 1997 -- 2000 Martin Mares <mj@ucw.cz>
 */
/* Changes by NEC Corporation for the VE port, 2025 */

/* This file extracts and modifies parts of the Linux kernel source's
 * drivers/pci/pci.c for the VE port.
 */

#include <linux/types.h>
#include <linux/pci.h>
#include "vepci.h"

/* Copied from drivers/pci/pci.c */
static struct pci_cap_saved_state *_pci_find_saved_cap(struct pci_dev *pci_dev,
		u16 cap, bool extended)
{
	struct pci_cap_saved_state *tmp;

	hlist_for_each_entry(tmp, &pci_dev->saved_cap_space, next) {
		if (tmp->cap.cap_extended == extended && tmp->cap.cap_nr == cap)
			return tmp;
	}
	return NULL;
}

/* Copied from drivers/pci/pci.c */
struct pci_cap_saved_state *pci_find_saved_cap(struct pci_dev *dev, char cap)
{
	return _pci_find_saved_cap(dev, cap, false);
}

/**
 * Save LNKCTL2 to reserve current state
 * This is modified version of pci_save_pcie_state() in drivers/pci/pci.c
 */
int pci_save_state_lnkctl2_only(struct pci_dev *dev)
{
	int i = 0;
	struct pci_cap_saved_state *save_state;
	u16 *cap;

	if (!pci_is_pcie(dev))
		return 0;

	save_state = pci_find_saved_cap(dev, PCI_CAP_ID_EXP);
	if (!save_state) {
		dev_err(&dev->dev, "buffer not found in %s\n", __func__);
		return -ENOMEM;
	}

	cap = (u16 *)&save_state->cap.data[0];
	/* PCI_EXP_DEVCTL */
	i++;
	/* PCI_EXP_LNKCTL */
	i++;
	/* PCI_EXP_SLTCTL */
	i++;
	/* PCI_EXP_RTCTL */
	i++;
	/* PCI_EXP_DEVCTL2 */
	i++;
	/* PCI_EXP_LNKCTL2 */
	pcie_capability_read_word(dev, PCI_EXP_LNKCTL2, &cap[i++]);
	/* PCI_EXP_SLTCTL2 */
	i++;

	return 0;
}