#include <sys/errno.h>
#include <sys/conf.h>
#include <sys/cmn_err.h>
#include <sys/modctl.h>
#include <sys/sunddi.h>
#include <sys/stat.h>
#include "foobar.h"

static int foobar_attach(dev_info_t *dip, ddi_attach_cmd_t cmd);

static int foobar_detach(dev_info_t *dip, ddi_detach_cmd_t cmd);

static struct cb_ops foobar_cb_ops = {
	nodev,          /* no open */
	nodev,          /* no close */
	nodev,          /* no strategy (only for block drivers) */
	nodev,          /* no print */
	nodev,          /* no dump (only for block drivers) */
	nodev,          /* no read */
	nodev,          /* no write */
	nodev,          /* no ioctl */
	nodev,          /* no devmap */
	nodev,          /* no mmap */
	nodev,          /* no segmap */
	nochpoll,       /* no chpoll entry point */
	ddi_prop_op,    /* Use system-supplied prop_op entry point */
	NULL,
	D_NEW | D_MP
};

static struct dev_ops foobar_ops = {
	DEVO_REV,
	0,/* reference count: always 0 initially */
	nulldev,                  /* No getinfo entry point */
	nulldev,                  /* DEPRECATED: identify entry point */
	nulldev,                  /* no probe entry point */
	foobar_attach,
	foobar_detach,
	nodev,                    /* no reset entry point */
	&foobar_cb_ops,           /* Reference the cb_ops defined above */
	(struct bus_ops *)NULL    /* Not a nexus driver, so no bus_ops */
};

extern struct mod_ops mod_driverops;

static struct modldrv Modldrv = {
	&mod_driverops,    /* Use system-supplied mod_driverops */
	"foobar driver v" FOOBAR_VERSION, /* Module Name/Version */
	&foobar_ops,
};

static struct modlinkage Modlinkage = {
	MODREV_1,
	&Modldrv,
	NULL
};

/*
 * This bit of static data is used by the DDI to
 * keep track of the per-instance driver "soft state"
 */
static void *soft_statep;
	int
_init(void)
{
	/*
	 * Initialize the soft state APIs so we can
	 * allocate soft state in foobar_attach()
	 */
	cmn_err(CE_WARN,"_init start , hello world!! , version1");
	if (ddi_soft_state_init(&soft_statep,
				sizeof (struct foobar_state), 1)
			!= DDI_SUCCESS)
		return (DDI_FAILURE);
	
	if (mod_install(&Modlinkage) != 0) {
		ddi_soft_state_fini(&soft_statep);
		return (-1);
	}
	cmn_err(CE_WARN , "_init end!!");
	return (0);
}

	int
_info(struct modinfo *modinfop)
{
	return (mod_info(&Modlinkage, modinfop));
}

	int
_fini(void)
{
	cmn_err(CE_WARN , "_fini start!!");
	ddi_soft_state_fini(&soft_statep);
	return (mod_remove(&Modlinkage));
}

	static int
foobar_attach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	cmn_err(CE_WARN , "_attach!!");
	int instance;
	struct foobar_state *softp;
	/* Use the instance number as the minor number */
	instance = ddi_get_instance(dip);

	if (ddi_soft_state_zalloc(soft_statep, instance)
			== DDI_FAILURE)
		return (DDI_FAILURE);
	
	softp = ddi_get_soft_state(soft_statep, instance);
	ASSERT(softp != NULL);

	if (ddi_create_minor_node(dip, FOOBAR_MINOR_NAME,
				S_IFCHR, instance, DDI_PSEUDO, 0) 
			!= DDI_SUCCESS) {
		cmn_err(CE_WARN, "Minor creation failed!");
		return (DDI_FAILURE);
	}
	softp->init_state |= FOOBAR_INIT_MINOR;
	softp->dip = dip;
	mutex_init(&softp->mutex, NULL, MUTEX_DRIVER, 0);
	softp->buffer = (char *)kmem_alloc(FOOBAR_BUFLEN,
			KM_SLEEP);
	ddi_report_dev(dip);    /* Announce we've attached! */
	cmn_err(CE_WARN , "_attach end!!");
	return (DDI_SUCCESS);
}

	static int
foobar_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int instance;
	struct foobar_state *softp;

	if (cmd != DDI_DETACH)
		return (DDI_FAILURE);

	/* Use the instance number as the minor number */
	instance = ddi_get_instance(dip);

	softp = ddi_get_soft_state(soft_statep, instance);

	ASSERT(softp != NULL);
	if (softp->init_state & FOOBAR_INIT_MINOR) {
		/* Remove minor nodes associated with dip */
		ddi_remove_minor_node(dip, NULL);
	}
	ASSERT(softp->buffer != NULL);
	kmem_free(softp->buffer, FOOBAR_BUFLEN);

	ddi_soft_state_free(soft_statep, instance);

	return (DDI_SUCCESS);
}
