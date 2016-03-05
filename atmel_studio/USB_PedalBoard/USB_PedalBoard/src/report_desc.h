// Z:\home\alex\Virtual_Win7\test\footswitch_board.h

#ifndef REPORT_DESC_H
#define  REPORT_DESC_H

const uint8_t report_desc[] = {
	0x05, 0x09,                    // USAGE_PAGE (Button)
	0x19, 0x01,                    // USAGE_MINIMUM (Button 1)
	0x29, 0x0a,                    // USAGE_MAXIMUM (Button 10)
	0x15, 0x00,                    // LOGICAL_MINIMUM (0)
	0x25, 0x01,                    // LOGICAL_MAXIMUM (1)
	0x95, 0x0a,                    // REPORT_COUNT (10)
	0x75, 0x01,                    // REPORT_SIZE (1)
	0x81, 0x02,                    // INPUT (Data,Var,Abs)
	0x95, 0x01,                    // REPORT_COUNT (1)
	0x75, 0x06,                    // REPORT_SIZE (6)
	0x81, 0x03,                    // INPUT (Cnst,Var,Abs)

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x01,                    //   REPORT_ID (1)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x02,                    //   REPORT_ID (2)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x03,                    //   REPORT_ID (3)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x04,                    //   REPORT_ID (4)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x05,                    //   REPORT_ID (5)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x06,                    //   REPORT_ID (6)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x07,                    //   REPORT_ID (7)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x08,                    //   REPORT_ID (8)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x09,                    //   REPORT_ID (9)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION

	0x05, 0x08,                    // USAGE_PAGE (LEDs)
	0x09, 0x4b,                    // USAGE (Generic Indicator)
	0xa1, 0x01,                    //   COLLECTION (Application)
	0x85, 0x0a,                    //   REPORT_ID (10)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x09, 0x47,                    //   USAGE (Usage Indicator Color)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0xff, 0x00,  //   LOGICAL_MAXIMUM (16777215)
	0x75, 0x18,                    //   REPORT_SIZE (24)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0xc0                           //  END_COLLECTION
};

#define LEN_REPORT_DESC (sizeof(report_desc))

#endif